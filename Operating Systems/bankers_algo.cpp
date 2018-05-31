#include<iostream>
using namespace std;

#define P 5
#define R 3

// Function to find the system is in safe state or not
void isSafe(const int avail[], int maxm[][R], int allot[][R]) {
    int need[P][R];

    // Calculate need matrix
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = maxm[i][j] - allot[i][j];

    // Mark all processes as unfinished
    bool finish[P] = {false};

    // To store safe sequence
    int safeSeq[P];

    // Make a copy of available resources
    int work[R];
    for (int i = 0; i < R; i++)
        work[i] = avail[i];

    // While all processes are not finished
    // or system is not in safe state.
    int count = 0;
    while (count < P) {
        // Find a process which is not finish and
        // whose needs can be satisfied with current
        // work[] resources.
        bool found = false;
        for (int p = 0; p < P; p++) {
            // First check if a process is finished,
            // if no, go for next condition
            if (finish[p] == 0) {
                // Check if for all resources of
                // current P need is less
                // than work
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;

                // If all needs of p were satisfied.
                if (j == R) {
                    // Add the allocated resources of
                    // current P to the available/work
                    // resources i.e.free the resources
                    for (int k = 0; k < R; k++)
                        work[k] += allot[p][k];

                    // Add this process to safe sequence.
                    safeSeq[count++] = p;

                    // Mark this p as finished
                    finish[p] = true;

                    found = true;
                }
            }
        }

        // If we could not find a next process in safe sequence.
        if (!found) {
            cout << "System is not in safe state";
            return ;
        }
    }

    cout << "System is in safe state.\nSafe sequence is: ";
    for (int i : safeSeq)
        cout << i << " ";
}

int main() {
    // Available instances of resources
    int avail[] = {3, 3, 2};

    // Maximum R that can be allocated
    // to processes
    int maxm[][R] = {{7, 5, 3},
                     {3, 2, 2},
                     {9, 0, 2},
                     {2, 2, 2},
                     {4, 3, 3}};

    // Resources allocated to processes
    int allot[][R] = {{0, 1, 0},
                      {2, 0, 0},
                      {3, 0, 2},
                      {2, 1, 1},
                      {0, 0, 2}};

    // Check system is in safe state or not
    isSafe(avail, maxm, allot);

    return 0;
}
