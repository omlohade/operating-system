import java.util.*;

public class RoundRobin {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the number of processes: ");
        int processes = sc.nextInt();

        System.out.print("Enter the time quantum: ");
        int timeQuantum = sc.nextInt();

        int[] arrivalTimes = new int[processes];
        int[] burstTimes = new int[processes];
        int[] remainingTimes = new int[processes];
        int[] finishTimes = new int[processes];
        int[] turnaroundTimes = new int[processes];
        int[] waitingTimes = new int[processes];

        for (int i = 0; i < processes; i++) {
            System.out.println("Enter arrival time for process P" + i + ": ");
            arrivalTimes[i] = sc.nextInt();
            System.out.println("Enter burst time for process P" + i + ": ");
            burstTimes[i] = sc.nextInt();
            remainingTimes[i] = burstTimes[i]; // Initialize remaining times with burst times
        }

        Queue<Integer> readyQueue = new LinkedList<>();
        int time = 0; // Keeps track of the current time
        int completed = 0;

        // Initially, add processes that have arrived at time 0
        for (int i = 0; i < processes; i++) {
            if (arrivalTimes[i] <= time) {
                readyQueue.offer(i);
            }
        }

        while (completed < processes) {
            if (readyQueue.isEmpty()) {
                time++; // Increment time if no process is ready
                for (int i = 0; i < processes; i++) {
                    if (arrivalTimes[i] == time && !readyQueue.contains(i)) {
                        readyQueue.offer(i);
                    }
                }
                continue;
            }

            int process = readyQueue.poll();

            // Process the current process for a time quantum or until it finishes
            int execTime = Math.min(timeQuantum, remainingTimes[process]);
            time += execTime;
            remainingTimes[process] -= execTime;

            // If the process finishes execution
            if (remainingTimes[process] == 0) {
                finishTimes[process] = time;
                turnaroundTimes[process] = finishTimes[process] - arrivalTimes[process];
                waitingTimes[process] = turnaroundTimes[process] - burstTimes[process];
                completed++;
            }

            // Add any new processes that have arrived by the current time
            for (int i = 0; i < processes; i++) {
                if (arrivalTimes[i] <= time && remainingTimes[i] > 0 && !readyQueue.contains(i) && i != process) {
                    readyQueue.offer(i);
                }
            }

            // If the process is not finished, add it back to the queue
            if (remainingTimes[process] > 0) {
                readyQueue.offer(process);
            }
        }

        // Print the results
        System.out.println("Process \t Arrival Time \t Burst Time \t Finish Time \t Turnaround Time \t Waiting Time");
        for (int i = 0; i < processes; i++) {
            System.out.printf("P%d\t\t %d\t\t %d\t\t %d\t\t\t %d\t\t %d\n",
                    i, arrivalTimes[i], burstTimes[i], finishTimes[i], turnaroundTimes[i], waitingTimes[i]);
        }
    }
}
/*
input : 4 2 0 5 1 4 2 2 4 1
output :
Process 	 Arrival Time 	 Burst Time 	 Finish Time 	 Turnaround Time 	 Waiting Time
P0				 0				 5				 12					 12				 7
P1				 1				 4				 11					 10				 6
P2				 2				 2				 6					 4				 2
P3				 4				 1				 9					 5				 4
 */













//  This code implements the Round Robin (RR) Scheduling algorithm, which is a preemptive scheduling algorithm. In Round Robin scheduling, each process is assigned a fixed time quantum (slice of time) to execute. If a process does not finish within its time quantum, it is preempted and placed back into the ready queue for further execution. The algorithm continues this cycle until all processes are completed.

// Key Components of the Code:
// Input:

// The user provides the number of processes and the time quantum.
// For each process, the user provides the arrival time and burst time (CPU time required to finish execution).
// Arrays:

// arrivalTimes[]: Stores the arrival time of each process.
// burstTimes[]: Stores the burst time of each process.
// remainingTimes[]: Tracks the remaining time (initially equal to burst time).
// finishTimes[]: Stores the finish time for each process (calculated during execution).
// turnaroundTimes[]: Stores the turnaround time for each process (calculated as Finish Time - Arrival Time).
// waitingTimes[]: Stores the waiting time for each process (calculated as Turnaround Time - Burst Time).
// Queue:

// A Queue<Integer> readyQueue is used to manage the processes that are ready to execute. The processes are added to this queue as they arrive or are preempted.
// Execution Logic:

// The current time is tracked by time, and the number of completed processes is tracked by completed.
// Processes are added to the ready queue if their arrival time has been reached.
// Each time, the process at the front of the ready queue is processed for a time quantum or until it finishes (whichever is smaller).
// If a process finishes execution, its finish time, turnaround time, and waiting time are calculated and stored.
// If a process is not finished after its time quantum, it is placed back in the queue to continue execution.
// Output:

// After all processes are completed, the program prints a table with the Process ID, Arrival Time, Burst Time, Finish Time, Turnaround Time, and Waiting Time for each process.
// Detailed Code Explanation:
// java
// Copy code
// import java.util.*;

// public class RoundRobin {
//     public static void main(String[] args) {
//         Scanner sc = new Scanner(System.in);

//         // Taking input for number of processes and time quantum
//         System.out.print("Enter the number of processes: ");
//         int processes = sc.nextInt();

//         System.out.print("Enter the time quantum: ");
//         int timeQuantum = sc.nextInt();

//         // Initializing arrays for arrival times, burst times, remaining times, etc.
//         int[] arrivalTimes = new int[processes];
//         int[] burstTimes = new int[processes];
//         int[] remainingTimes = new int[processes];
//         int[] finishTimes = new int[processes];
//         int[] turnaroundTimes = new int[processes];
//         int[] waitingTimes = new int[processes];

//         // Input arrival times and burst times for each process
//         for (int i = 0; i < processes; i++) {
//             System.out.println("Enter arrival time for process P" + i + ": ");
//             arrivalTimes[i] = sc.nextInt();
//             System.out.println("Enter burst time for process P" + i + ": ");
//             burstTimes[i] = sc.nextInt();
//             remainingTimes[i] = burstTimes[i]; // Initialize remaining times with burst times
//         }

//         Queue<Integer> readyQueue = new LinkedList<>();
//         int time = 0; // Current time
//         int completed = 0; // Completed processes counter

//         // Initially, add processes that have arrived at time 0
//         for (int i = 0; i < processes; i++) {
//             if (arrivalTimes[i] <= time) {
//                 readyQueue.offer(i);
//             }
//         }

//         // Main loop to process all the processes
//         while (completed < processes) {
//             if (readyQueue.isEmpty()) {
//                 time++; // Increment time if no process is ready
//                 // Add new processes that have arrived at the current time
//                 for (int i = 0; i < processes; i++) {
//                     if (arrivalTimes[i] == time && !readyQueue.contains(i)) {
//                         readyQueue.offer(i);
//                     }
//                 }
//                 continue;
//             }

//             int process = readyQueue.poll();

//             // Execute the current process for a time quantum or until it finishes
//             int execTime = Math.min(timeQuantum, remainingTimes[process]);
//             time += execTime;
//             remainingTimes[process] -= execTime;

//             // If the process finishes execution
//             if (remainingTimes[process] == 0) {
//                 finishTimes[process] = time;
//                 turnaroundTimes[process] = finishTimes[process] - arrivalTimes[process];
//                 waitingTimes[process] = turnaroundTimes[process] - burstTimes[process];
//                 completed++;
//             }

//             // Add any new processes that have arrived by the current time
//             for (int i = 0; i < processes; i++) {
//                 if (arrivalTimes[i] <= time && remainingTimes[i] > 0 && !readyQueue.contains(i) && i != process) {
//                     readyQueue.offer(i);
//                 }
//             }

//             // If the process is not finished, add it back to the queue
//             if (remainingTimes[process] > 0) {
//                 readyQueue.offer(process);
//             }
//         }

//         // Print the results in a table format
//         System.out.println("Process \t Arrival Time \t Burst Time \t Finish Time \t Turnaround Time \t Waiting Time");
//         for (int i = 0; i < processes; i++) {
//             System.out.printf("P%d\t\t %d\t\t %d\t\t %d\t\t\t %d\t\t %d\n",
//                     i, arrivalTimes[i], burstTimes[i], finishTimes[i], turnaroundTimes[i], waitingTimes[i]);
//         }
//     }
// }
// Explanation of the Sample Input and Output:
// Input:
// mathematica
// Copy code
// Enter the number of processes: 4
// Enter the time quantum: 2
// Enter arrival time for process P0: 
// 0
// Enter burst time for process P0: 
// 5
// Enter arrival time for process P1: 
// 1
// Enter burst time for process P1: 
// 4
// Enter arrival time for process P2: 
// 2
// Enter burst time for process P2: 
// 2
// Enter arrival time for process P3: 
// 4
// Enter burst time for process P3: 
// 1
// Output:
// css
// Copy code
// Process 	 Arrival Time 	 Burst Time 	 Finish Time 	 Turnaround Time 	 Waiting Time
// P0				 0				 5				 12					 12				 7
// P1				 1				 4				 11					 10				 6
// P2				 2				 2				 6					 4				 2
// P3				 4				 1				 9					 5				 4
// Key Values:
// Finish Time: The time at which a process finishes execution.
// Turnaround Time: Finish Time - Arrival Time.
// Waiting Time: Turnaround Time - Burst Time.
// Notes:
// The Round Robin algorithm is particularly effective for time-sharing systems, as it ensures all processes get a fair amount of CPU time.
// The time quantum (also known as the time slice) is crucial because it determines how much CPU time each process can use before it is preempted and placed back into the ready queue.
// The implementation handles the scenario where no processes are in the ready queue (i.e., when all processes are either executing or waiting for CPU time). In such cases, the time is incremented until new processes arrive.