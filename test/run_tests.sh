#!/bin/bash
set -eu

if [ "$#" -lt 1 ]; then
  echo "usage: $0 <exe> [exe...]" >&2
  exit 2
fi

if [ -n "${TEST_JOBS:-}" ]; then
  jobs="$TEST_JOBS"
else
  jobs="$(nproc 2>/dev/null || echo 4)"
fi

# Optional per-test timeout in seconds (0 disables timeout).
timeout_secs="${TEST_TIMEOUT:-0}"

tmpdir="$(mktemp -d /tmp/chibicc-run-XXXXXX)"
trap 'rm -rf "$tmpdir"' EXIT INT TERM HUP

failfile="$tmpdir/fails"
touch "$failfile"

run_one() {
  exe="$1"
  mkdir -p "$tmpdir"
  touch "$failfile"
  log="$tmpdir/$(echo "$exe" | tr '/ ' '__').log"
  echo "$exe"

  status=0
  if [ "$timeout_secs" -gt 0 ] && command -v timeout >/dev/null 2>&1; then
    timeout "${timeout_secs}s" "$exe" >"$log" 2>&1 || status=$?
  else
    "$exe" >"$log" 2>&1 || status=$?
  fi

  if [ "$status" -ne 0 ]; then
    mkdir -p "$tmpdir"
    touch "$failfile"
    if [ "$status" -eq 124 ] || [ "$status" -eq 137 ]; then
      echo "[TIMEOUT ${timeout_secs}s] $exe" >> "$log"
    fi
    echo "$exe" >> "$failfile"
    return 1
  fi
  return 0
}

export -f run_one
export tmpdir failfile timeout_secs

# Let all tests run and summarize failures ourselves below.
# With "set -e", xargs would otherwise stop the script before summary printing.
if ! printf '%s\n' "$@" | xargs -P"$jobs" -I{} bash -c 'run_one "$1"' _ {}; then
  :
fi

if [ -s "$failfile" ]; then
  mapfile -t failed_exes < <(sort -u "$failfile")
  echo "FAILED TESTS (${#failed_exes[@]}):" >&2
  printf '  %s\n' "${failed_exes[@]}" >&2
  echo >&2

  while IFS= read -r exe; do
    log="$tmpdir/$(echo "$exe" | tr '/ ' '__').log"
    echo "FAILED: $exe" >&2
    [ -f "$log" ] && cat "$log" >&2
    echo >&2
    done < <(printf '%s\n' "${failed_exes[@]}")
  exit 1
fi
