#include<cstdio>
#include<cstdlib>
#include<pthread.h>

#define N 50

long fib(int x) {
    if (x == 1 || x == 2)
        return 1;
    else
        return fib(x - 1) + fib(x - 2);
}

void *thread(void *arg) {
    int x = (*(int *) arg);
    printf("\n%d: %ld", x, fib(x));
}

int main() {

    pthread_t threads[N + 1];
    clock_t tStart;

    // Get POSIX Thread Attribute Set
    pthread_attr_t attr{};
    pthread_attr_init(&attr);

    for (int i = 1; i <= N; i++) {
        tStart = clock();

        pthread_create(&threads[i], &attr, thread, (void *) &i);
        pthread_join(threads[i], nullptr);

        printf("\nTime taken: %.4f m sec\n", (double) (clock() - tStart) * 1000 / CLOCKS_PER_SEC);
    }

    return 0;
}