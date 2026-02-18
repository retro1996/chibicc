#include "test.h"
#include <pthread.h>
#include <sched.h>

typedef struct {
  pthread_mutex_t lock;
  pthread_cond_t cond;
  int stop;
  int pending;
  int processed;
  int wakeups;
} logger_state_t;

static void *logger_thread(void *arg) {
  logger_state_t *s = arg;

  pthread_mutex_lock(&s->lock);
  for (;;) {
    while (s->pending == 0 && !s->stop) {
      s->wakeups++;
      pthread_cond_wait(&s->cond, &s->lock);
    }

    if (s->stop && s->pending == 0)
      break;

    if (s->pending > 0) {
      s->pending--;
      s->processed++;
    }
  }
  pthread_mutex_unlock(&s->lock);
  return 0;
}

int main(void) {
  logger_state_t s;
  pthread_t tid;
  int rc;
  int jobs = 20000;

  s.stop = 0;
  s.pending = 0;
  s.processed = 0;
  s.wakeups = 0;

  rc = pthread_mutex_init(&s.lock, 0);
  ASSERT(0, rc);
  rc = pthread_cond_init(&s.cond, 0);
  ASSERT(0, rc);

  rc = pthread_create(&tid, 0, logger_thread, &s);
  ASSERT(0, rc);

  // Generate a lot of wakeups/work to stress mutex+cond codegen paths.
  for (int i = 0; i < jobs; i++) {
    pthread_mutex_lock(&s.lock);
    s.pending++;
    pthread_cond_signal(&s.cond);
    pthread_mutex_unlock(&s.lock);
  }

  // Wait until all jobs are consumed.
  for (;;) {
    int done;
    pthread_mutex_lock(&s.lock);
    done = (s.processed == jobs);
    pthread_mutex_unlock(&s.lock);
    if (done)
      break;
    sched_yield();
  }

  // Memcached-like shutdown: set stop flag under lock, signal, then join.
  pthread_mutex_lock(&s.lock);
  s.stop = 1;
  pthread_cond_signal(&s.cond);
  pthread_mutex_unlock(&s.lock);

  rc = pthread_join(tid, 0);
  ASSERT(0, rc);

  ASSERT(jobs, s.processed);
  ASSERT(0, s.pending);
  ASSERT(1, s.wakeups > 0);

  pthread_cond_destroy(&s.cond);
  pthread_mutex_destroy(&s.lock);
  return 0;
}
