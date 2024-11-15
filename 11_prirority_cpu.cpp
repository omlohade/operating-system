#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Struct to represent a process
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
};

// Comparison function for the priority queue (Preemptive)
struct ComparePriority {
    bool operator()(const Process& a, const Process& b) {
        return a.priority > b.priority;
    }
};

// Function for Preemptive Priority Scheduling
void preemptivePriorityScheduling(vector<Process>& processes, int n) {
    // Manually sort processes based on arrival time (earlier arrival first)
    sort(processes.begin(), processes.end(), [](Process& a, Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    int currentTime = 0;
    priority_queue<Process, vector<Process>, ComparePriority> readyQueue;
    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> finishTime(n, 0);
    int completed = 0;

    while (completed < n) {
        // Add processes that have arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= currentTime && processes[i].burst_time > 0) {
                readyQueue.push(processes[i]);
            }
        }

        // Process the one with the highest priority (preemptive)
        if (!readyQueue.empty()) {
            Process current = readyQueue.top();
            readyQueue.pop();

            int remainingTime = current.burst_time;
            if (remainingTime > 1) {
                current.burst_time = remainingTime - 1;
                readyQueue.push(current);
            }

            int processId = current.id - 1;
            if (finishTime[processId] == 0) {
                finishTime[processId] = currentTime + 1;
                waitingTime[processId] = finishTime[processId] - processes[processId].arrival_time - processes[processId].burst_time;
                turnaroundTime[processId] = finishTime[processId] - processes[processId].arrival_time;
                completed++;
            }
            currentTime++;
        } else {
            currentTime++;
        }
    }

    // Display results
    cout << "Gantt Chart:\n";
    for (const Process& process : processes) {
        cout << "| P" << process.id << " ";
    }
    cout << "|\n";
    cout << "0 ";
    for (int time : finishTime) {
        cout << " " << time << " ";
    }
    cout << endl;

    cout << "Process ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\tFinish Time\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" 
             << processes[i].priority << "\t\t" << waitingTime[i] << "\t\t" << turnaroundTime[i] << "\t\t" << finishTime[i] << endl;
    }
}

// Function for Non-Preemptive Priority Scheduling
void nonPreemptivePriorityScheduling(vector<Process>& processes, int n) {
    // Manually sort processes based on priority (higher priority first)
    sort(processes.begin(), processes.end(), [](Process& a, Process& b) {
        return a.priority > b.priority;
    });

    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> finishTime(n, 0);
    finishTime[0] = processes[0].burst_time;
    turnaroundTime[0] = processes[0].burst_time - processes[0].arrival_time;
    waitingTime[0] = turnaroundTime[0] - processes[0].burst_time;

    for (int i = 1; i < n; i++) {
        finishTime[i] = finishTime[i - 1] + processes[i].burst_time;
        turnaroundTime[i] = finishTime[i] - processes[i].arrival_time;
        waitingTime[i] = turnaroundTime[i] - processes[i].burst_time;
    }

    // Display results
    cout << "Gantt Chart:\n";
    int totalTime = 0;
    for (const Process& process : processes) {
        cout << "| P" << process.id << " ";
        for (int i = 0; i < process.burst_time; i++) {
            cout << " ";
        }
        totalTime += process.burst_time;
    }
    cout << "|\n";
    cout << "0 ";
    for (int time : finishTime) {
        cout << " " << time << " ";
    }
    cout << endl;

    cout << "Process ID\tArrival Time\tBurst Time\tPriority\tTurnaround Time\tFinish Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" 
             << processes[i].priority << "\t\t" << turnaroundTime[i] << "\t\t" << finishTime[i] << "\t\t" << waitingTime[i] << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input process information
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
        cout << "Enter priority for process " << i + 1 << ": ";
        cin >> processes[i].priority;
    }


 


        cout << "\nPreemptive Priority Scheduling\n";
        preemptivePriorityScheduling(processes, n);
   
        cout << "\nNon-Preemptive Priority Scheduling\n";
        nonPreemptivePriorityScheduling(processes, n);
  
        
  

    return 0;
}
























// The provided code implements both Preemptive and Non-Preemptive Priority Scheduling algorithms. Here's a detailed explanation of the logic and flow of the program:

// Data Structure: Process
// A struct Process is defined to represent a process with attributes:
// id: Process ID (e.g., P1, P2, etc.)
// arrival_time: When the process arrives in the system.
// burst_time: The total CPU time required to execute the process.
// priority: The priority of the process (higher value indicates higher priority).
// Helper Class: ComparePriority
// A custom comparator class ComparePriority is used for sorting the priority queue, ensuring that the process with the highest priority is always at the top.
// The priority queue is used in the Preemptive Priority Scheduling.
// Function 1: preemptivePriorityScheduling
// This function implements the Preemptive Priority Scheduling algorithm. The process with the highest priority is always selected for execution, and if a new process with higher priority arrives, the current process can be preempted.

// Step 1: Sort the processes based on arrival_time (earlier arrival comes first).
// Step 2: Initialize the currentTime to 0 and start with an empty priority queue (readyQueue).
// Step 3: In each iteration, add processes to the readyQueue that have arrived by the current time (currentTime).
// Step 4: The process with the highest priority (top of the priority queue) is selected for execution. The remaining burst time is decreased by 1.
// Step 5: If the burst time of the selected process becomes 0, it is marked as finished and the corresponding waiting time and turnaround time are calculated.
// Step 6: The algorithm continues until all processes are completed.
// Step 7: The Gantt chart and scheduling results (waiting time, turnaround time, and finish time) are displayed.
// Function 2: nonPreemptivePriorityScheduling
// This function implements the Non-Preemptive Priority Scheduling algorithm. Once a process starts executing, it runs to completion without being interrupted.

// Step 1: Sort the processes based on priority (higher priority comes first).
// Step 2: Initialize the finishTime, waitingTime, and turnaroundTime for each process.
// Step 3: The process with the highest priority is executed first, followed by the others based on their priority.
// Step 4: For each process, the finishTime is updated as the sum of the burst time of the current process and the finish time of the previous process.
// Step 5: The Gantt chart and scheduling results (waiting time, turnaround time, and finish time) are displayed.
// Main Function:
// The main function handles the input of process details (arrival time, burst time, and priority) and calls the scheduling functions for both preemptive and non-preemptive priority scheduling algorithms.
// Example Input and Output:
// Input:
// mathematica
// Copy code
// Enter the number of processes: 3
// Enter arrival time for process 1: 0
// Enter burst time for process 1: 5
// Enter priority for process 1: 2

// Enter arrival time for process 2: 1
// Enter burst time for process 2: 3
// Enter priority for process 2: 1

// Enter arrival time for process 3: 2
// Enter burst time for process 3: 2
// Enter priority for process 3: 3
// Output:
// Preemptive Priority Scheduling
// less
// Copy code
// Gantt Chart:
// | P3 | P1 | P3 | P1 | P1 | P1 | P1 | 
// 0  2  4  5  7  8  10  12

// Process ID    Arrival Time    Burst Time    Priority    Waiting Time    Turnaround Time    Finish Time
// 1             0              5             2           7               12                  12
// 2             1              3             1           3               6                   4
// 3             2              2             3           1               3                   5
// Non-Preemptive Priority Scheduling
// less
// Copy code
// Gantt Chart:
// | P3 | P1 | P2 | 
// 0  2  7  10

// Process ID    Arrival Time    Burst Time    Priority    Waiting Time    Turnaround Time    Finish Time
// 1             0              5             2           2               7                   7
// 2             1              3             1           6               9                   10
// 3             2              2             3           0               2                   2
// Explanation of Output:
// Gantt Chart shows how the processes are scheduled over time.
// Process ID, Arrival Time, Burst Time, Priority, Waiting Time, Turnaround Time, Finish Time are calculated for each process:
// Waiting Time is the time a process has been in the ready queue before it starts execution.
// Turnaround Time is the total time from when the process arrives until it finishes (Turnaround = Finish Time - Arrival Time).
// Finish Time is when the process completes its execution.
// Things to Consider:
// The current implementation assumes that all processes are ready to execute when the algorithm starts and doesn't account for situations like simultaneous arrivals or the arrival of multiple processes at the same time.
// The preemptive nature of the first algorithm ensures that higher-priority processes are given preference, whereas the non-preemptive algorithm completes one process before starting another.
// This structure should now allow you to understand the flow of the code and its outputs based on different scheduling strategies.