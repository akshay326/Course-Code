#include<iostream>
#include<algorithm>

using namespace std;

struct Process {
    int PID;
    int burst_time;
};

bool comparison(Process a, Process b) {
    return (a.burst_time < b.burst_time);
}

void find_waiting_time(Process proc[], int n, int weight_time[]) {
    // waiting time for first process is 0
    weight_time[0] = 0;

    // calculating waiting time
    for (int i = 1; i < n; i++)
        weight_time[i] = proc[i - 1].burst_time + weight_time[i - 1];
}

void find_waiting_time(const Process proc[],int n, int weight_time[], int quantum) {
    int remaining_time[n];
    for (int i = 0; i < n; i++)
        remaining_time[i] = proc[i].burst_time;

    int current_time = 0;

    bool done;
    do{
        done = true;
        for (int i = 0; i < n; i++)
            if (remaining_time[i] > 0) {
                done = false; // There is a pending process

                if (remaining_time[i] > quantum) {
                    current_time += quantum;
                    remaining_time[i] -= quantum;
                    printf("\nt=%d: Process=%d Time Remaining=%d",current_time,i+1,remaining_time[i]);
                }
                else { // Process Will finish now
                    current_time = current_time + remaining_time[i];
                    weight_time[i] = current_time - proc[i].burst_time;
                    printf("\nt=%d: Process=%d will finish in %d sec",current_time,i+1,remaining_time[i]);
                    remaining_time[i] = 0;
                }
            }

    }while (!done);
}

void find_turn_around_time(Process proc[], int n,const int weight_time[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].burst_time + weight_time[i];
}

void find_avg_time(Process proc[], int n, int quantum = -1) {
    int weight_time[n], tat[n], total_wt = 0, total_tat = 0;

    // Function to find waiting time of all processes
    if (quantum <= 0)
        find_waiting_time(proc, n, weight_time);
    else // Round Robin Method
        find_waiting_time(proc, n, weight_time, quantum);

    find_turn_around_time(proc, n, weight_time, tat);

    // Display processes along with all details
    cout << "\nProcesses " << " Burst time "
         << " Waiting time " << " Turn around time\n";

    // Calculate total waiting time and total turn
    // around time
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + weight_time[i];
        total_tat = total_tat + tat[i];
        cout << " " << proc[i].PID << "\t\t"
             << proc[i].burst_time << "\t " << weight_time[i]
             << "\t\t " << tat[i] << endl;
    }

    cout << "Average waiting time = "
         << (float) total_wt / (float) n;
    cout << "\nAverage turn around time = "
         << (float) total_tat / (float) n;
}

int main() {
    Process proc[] = {{1, 6},
                      {2, 8},
                      {3, 7},
                      {4, 3}};

//    Process proc[] = {{1, 10},
//                      {2, 5},
//                      {3, 8}};

    int n = sizeof proc / sizeof proc[0];

//    // FIRST CUM FIRST SERVED
//    find_avg_time(proc, n);

    // ROUND ROBIN
    find_avg_time(proc, n,3);

//    // SHORTEST JOB FIRST.
//    sort(proc, proc + n, comparison);
//    find_avg_time(proc, n);
    
    return 0;
}