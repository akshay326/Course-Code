#include<cstdio>
#include<cstdlib>
#include<pthread.h>

#define MAX_THREAD_COUNT 16
#define N 128
#define ITERATIONS 10

// Matrices
int currentRow = 0;
short **InMat1, **InMat2, **ResMat;

pthread_t *threads;

void *doMyWork(int Id);

int main(int argc, char *argv[]) {
    clock_t tStart;
    int i, j;

    // Create and Populate the Matrices
    InMat1 = (short**) malloc(sizeof(short) * N);
    InMat2 = (short**) malloc(sizeof(short) * N);
    ResMat = (short**) malloc(sizeof(short) * N);

    for (i = 0; i < N; i++) {

        InMat1[i] = (short *) malloc(sizeof(short) * N);
        InMat2[i] = (short *) malloc(sizeof(short) * N);
        ResMat[i] = (short *) malloc(sizeof(short) * N);

        for (j = 0; j < N; j++) {
            InMat1[i][j] = 1;
            InMat2[i][j] = 1;
            ResMat[i][j] = 0;
        }
    }

    //Get the default thread attributes
    pthread_attr_t attr{};
    pthread_attr_init(&attr);

    // TO print stats
//    double time_taken[ITERATIONS][MAX_THREAD_COUNT];

//    for (auto &x : time_taken)
    for (int threadCount = 1; threadCount <= MAX_THREAD_COUNT; ++threadCount) {

        printf("\nThread Count: %d.",threadCount);

        // Init for a round
        tStart = clock();
        threads = (pthread_t *) malloc(sizeof(pthread_t) * threadCount);
        currentRow = 0;

        for (i = 0; i < threadCount; i++) {
            pthread_create(&threads[i], &attr, (void *(*)(void *)) doMyWork, (void *) (i + 1));
//            printf("\n Thread %d created.", i + 1);
        }

        for (i = 0; i < threadCount; i++) {
//            printf("\n About to join Thread %d.", i + 1);
            pthread_join(threads[i], nullptr);
//            printf("\n Thread %d Joined.", i + 1);
        }

        printf("\nTime taken: %.4f ms\n", (double) (clock() - tStart) * 1000 / CLOCKS_PER_SEC);

//            x[threadCount-1] = (double) (clock() - tStart) * 1000 / CLOCKS_PER_SEC;
    }

//    // FOR Caculating Average
//    double sum=0;
//    for (int threadCount = 0; threadCount < MAX_THREAD_COUNT; ++threadCount) {
//        sum=0;
//        for (auto &x : time_taken)
//            sum += x[threadCount];
//
//        printf("\nAvg Time: %lf",sum/ITERATIONS);
//    }
}

void *doMyWork(int Id) {
    int i, j, myRow;

    while (true) {
//        printf("\n %d: Locking....", Id);

//        pthread_mutex_lock(&mutex_Row);

        if (currentRow >= N) {

//            pthread_mutex_unlock(&mutex_Row);

//            printf("\n %d: Unlocking...\n I am Thread No.: %d. I have no work to do.", Id, Id);
            if (Id == 0)
                break;

            pthread_exit(nullptr);
        }

        myRow = currentRow;

        currentRow++;

//        printf("\n I am Thread No.: %d. I have work to do.", Id);

//        pthread_mutex_unlock(&mutex_Row);

//        printf("\n %d: unlocking.... Operating on Row: %d.\n", Id, myRow);


        for (j = 0; j < N; j++)
            for (i = 0; i < N; i++)
                ResMat[myRow][j] += InMat1[myRow][i] * InMat2[i][j];
    }
}