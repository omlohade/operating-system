import java.util.*;

public class SJFNonPreemptive {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter number of processes: ");
        int processes = sc.nextInt();

        int[] arrivalTimes = new int[processes];
        int[] burstTimes = new int[processes];

        for (int i = 0; i < processes; i++) {
            System.out.println("Enter arrival time for process P" + i + ": ");
            arrivalTimes[i] = sc.nextInt();
            System.out.println("Enter burst time for process P" + i + ": ");
            burstTimes[i] = sc.nextInt();
        }

        int time = 0;
        int[] finishTimes = new int[processes];
        int[] turnaroundTimes = new int[processes];
        int[] waitingTimes = new int[processes];
        Set<Integer> executed = new HashSet<>();

        // Process until all processes are executed
        while (executed.size() < processes) {
            // Add all available processes to the ready queue
            Queue<Integer> readyQueue = new LinkedList<>();
            for (int i = 0; i < processes; i++) {
                if (!executed.contains(i) && arrivalTimes[i] <= time) {
                    readyQueue.add(i);
                }
            }

            if (readyQueue.isEmpty()) {
                time++; // Increment time if no process is ready
                continue;
            }

            // Find the process with the minimum burst time in the ready queue
            int process = findMinBurstTimeProcess(readyQueue, burstTimes, arrivalTimes);

            // Process execution
            time += burstTimes[process];
            finishTimes[process] = time;
            executed.add(process);

            // Calculate turnaround and waiting times
            turnaroundTimes[process] = finishTimes[process] - arrivalTimes[process];
            waitingTimes[process] = turnaroundTimes[process] - burstTimes[process];
        }

         // Print the results
        System.out.println("Process \t Arrival Time \t Burst Time \t Finish Time \t Turnaround Time \t Waiting Time");
        for (int i = 0; i < processes; i++) {
            System.out.printf("P%d\t\t %d\t\t %d\t\t %d\t\t\t %d\t\t %d\n",
                    i, arrivalTimes[i], burstTimes[i], finishTimes[i], turnaroundTimes[i], waitingTimes[i]);
        }
    }

    private static int findMinBurstTimeProcess(Queue<Integer> readyQueue, int[] burstTimes, int[] arrivalTimes) {
        // Select the process with the minimum burst time
        int minBurstTime = Integer.MAX_VALUE;
        int minProcess = -1;

        for (int process : readyQueue) {
            if (burstTimes[process] < minBurstTime || (burstTimes[process] == minBurstTime && arrivalTimes[process] < arrivalTimes[minProcess])) {
                minBurstTime = burstTimes[process];
                minProcess = process;
            }
        }

        return minProcess;
    }
}
/*
input : 4 1 3 2 4 1 2 4 4
Process 	 Arrival Time 	 Burst Time 	 Finish Time 	 Turnaround Time 	 Waiting Time
P0				 1				 3				 6					 5				 2
P1				 2				 4				 10					 8				 4
P2				 1				 2				 3					 2				 0
P3				 4				 4				 14					 10				 6

 */








 













//  The code you've shared implements Shortest Job First (SJF) scheduling in a non-preemptive manner. In SJF, the process with the shortest burst time is selected for execution next. In this version, the process that arrives first and has the shortest burst time is chosen to execute, and it does not preempt other processes.

// Here’s a step-by-step breakdown of how the code works and possible examiner questions based on the problem:

// 1. Code Explanation:
// Input:
// The program first takes the number of processes as input.
// Then, for each process, it collects the arrival time and burst time.
// Key Variables:
// arrivalTimes[]: Array holding the arrival times of the processes.
// burstTimes[]: Array holding the burst times (execution times) of the processes.
// finishTimes[]: Array storing the finish times of the processes.
// turnaroundTimes[]: Array storing the turnaround times (finish time - arrival time).
// waitingTimes[]: Array storing the waiting times (turnaround time - burst time).
// executed: A set used to keep track of the processes that have already been executed.
// time: Keeps track of the current time in the simulation.
// Process Execution:
// Main Loop: The program loops until all processes have been executed.
// Ready Queue:
// At each step, the program checks which processes have arrived and are ready to execute (those with arrival time ≤ current time).
// These processes are added to a readyQueue.
// Find the Process with the Shortest Burst Time:
// Among the processes in the readyQueue, the one with the minimum burst time is selected.
// If two processes have the same burst time, the one with the earlier arrival time is selected (this is handled in the findMinBurstTimeProcess method).
// Execution:
// The selected process is executed, updating the time by adding the burst time.
// After execution, the finish time, turnaround time, and waiting time are calculated for the process.
// The process is marked as executed and removed from the ready queue.
// Print the Results: After all processes have been executed, the program prints the result in a table format showing the process ID, arrival time, burst time, finish time, turnaround time, and waiting time.
// 2. Code Walkthrough:
// Input Collection:

// The program first collects the number of processes, and then for each process, it takes the arrival and burst times.
// Execution Simulation:

// The time variable simulates the passage of time in the CPU.
// At each cycle, the ready queue is populated with processes that have arrived by the current time.
// The process with the shortest burst time is selected and executed. The burst time is decremented from the remaining processes, and time is updated.
// Find the Process with the Shortest Burst Time:

// The findMinBurstTimeProcess() method ensures that the process with the smallest burst time in the ready queue is selected. In case of ties (multiple processes with the same burst time), it selects the one with the smallest arrival time.
// Output:

// After all processes have been executed, the results are displayed in a table with the process ID, arrival time, burst time, finish time, turnaround time, and waiting time.
// 3. Example Run:
// Given the input:

// mathematica
// Copy code
// Enter number of processes: 4
// Enter arrival time for process P0: 1
// Enter burst time for process P0: 3
// Enter arrival time for process P1: 2
// Enter burst time for process P1: 4
// Enter arrival time for process P2: 1
// Enter burst time for process P2: 2
// Enter arrival time for process P3: 4
// Enter burst time for process P3: 4
// The output will be:

// css
// Copy code
// Process 	 Arrival Time 	 Burst Time 	 Finish Time 	 Turnaround Time 	 Waiting Time
// P0				 1				 3				 6					 5				 2
// P1				 2				 4				 10					 8				 4
// P2				 1				 2				 3					 2				 0
// P3				 4				 4				 14					 10				 6
// 4. Potential External Examiner Questions:
// Explain the SJF Non-Preemptive scheduling algorithm and how the code implements it.

// In SJF Non-Preemptive, the CPU always selects the process with the shortest burst time that is ready to execute. The code selects the process with the smallest burst time from the ready queue, executes it, and updates the time accordingly.
// What is the difference between preemptive and non-preemptive SJF?

// Preemptive SJF allows a running process to be preempted if a new process arrives with a shorter burst time. Non-preemptive SJF does not interrupt the current process once it starts execution.
// Why do we need to sort processes by arrival time before selecting the shortest burst time in this code?

// Sorting by arrival time ensures that processes are only selected when they arrive and are ready to execute, respecting the non-preemptive nature of SJF.
// How do we handle ties in burst time for two or more processes in this code?

// If two processes have the same burst time, the code resolves the tie by selecting the process with the earliest arrival time. This is done inside the findMinBurstTimeProcess method.
// How is the waiting time for each process calculated in this program?

// Waiting time is calculated as the difference between the turnaround time and burst time (waitingTimes[process] = turnaroundTimes[process] - burstTimes[process]).
// What would happen if the ready queue is empty during the execution of the program?

// If the ready queue is empty, the time is incremented by 1 (simulating the passage of time) and the program checks again for processes that have arrived.
// Explain the time complexity of this code.

// The time complexity is dominated by the while loop, which processes each process exactly once. For each process, finding the minimum burst time from the ready queue takes O(n), resulting in a time complexity of O(n^2), where n is the number of processes.
// What improvements would you suggest for this implementation in terms of performance or usability?

// To improve performance, especially for large inputs, we could use a priority queue (min-heap) instead of a LinkedList to efficiently select the process with the shortest burst time in O(log n) time, reducing the overall time complexity.
// 5. Suggestions for Improvement:
// Priority Queue: Using a priority queue (or min-heap) would make selecting the process with the minimum burst time more efficient, reducing the time complexity from O(n^2) to O(n log n).

// Input Validation: Ensure that input values for arrival time and burst time are valid (e.g., non-negative integers).

// Edge Cases: Handle edge cases such as:

// Multiple processes arriving at the same time.
// Processes with burst time 0.
// User Experience: The program could be enhanced by displaying more detailed information for users, like when the system is idle due to no processes being ready.

// This code efficiently simulates the SJF Non-Preemptive scheduling algorithm and provides the required times for each process