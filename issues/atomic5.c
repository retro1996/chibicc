int main() {
    int x = 0, y;

    __atomic_load_n(&x, 0);
    __atomic_store_n(&x, 0);
    __atomic_exchange_n(&x, 1, 0);

    __atomic_compare_exchange_n(&x, &y, 1, 0, 0, 0);

    __atomic_fetch_add(&x, 1, 0);
    __atomic_fetch_sub(&x, 1, 0);
    __atomic_fetch_or(&x, 1, 0);
    __atomic_fetch_and(&x, 1, 0);

    __sync_bool_compare_and_swap(&x, 0, 1);
    __sync_add_and_fetch(&x, 1);

    return 0;
}
