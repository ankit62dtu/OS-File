#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int id, arrival_time, burst_time, completion_time, turnaround_time, waiting_time;
};

void fcfs(vector<Process>& processes, int n) {
    int time = 0, count = 0;
    vector<int> completion_time(n), turnaround_time(n), waiting_time(n);

    while (count < n) {
        if (processes[count].arrival_time <= time) {
            time += processes[count].burst_time;
            completion_time[count] = time;
            count++;
        } else {
            time++;
        }
    }

    for (int i = 0; i < n; i++) {
        turnaround_time[i] = completion_time[i] - processes[i].arrival_time;
        waiting_time[i] = turnaround_time[i] - processes[i].burst_time;
        processes[i].completion_time = completion_time[i];
        processes[i].turnaround_time = turnaround_time[i];
        processes[i].waiting_time = waiting_time[i];
    }

    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" << processes[i].completion_time << "\t\t" << processes[i].turnaround_time << "\t\t" << processes[i].waiting_time << endl;
    }

    float avg_waiting_time = 0, avg_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
    }

    cout << "Average Waiting Time: " << avg_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time / n << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter details for process " << i + 1 << endl;
        cout << "Arrival time: ";
        cin >> processes[i].arrival_time;
        cout << "Burst time: ";
        cin >> processes[i].burst_time;
        processes[i].id = i + 1;
        processes[i].completion_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
    }

    fcfs(processes, n);

    return 0;
}
