import java.util.*;

public class SJFPreemptive {
    public static void main(String[] args) {
        // taking no.of processes , arrival time and burst time from user
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter number of processes : ");
        int processes = sc.nextInt();

        int [] arrivalTimes = new int[processes];
        int [] burstTimes = new int[processes];
        int [] remainingTimes = new int[processes];
        for(int i = 0; i < processes; i++){
            System.out.println("Enter arrival time for process P"+i+" : ");
            arrivalTimes[i] = sc.nextInt();
            System.out.println("Enter burst time for process P"+i+" : ");
            burstTimes[i] = sc.nextInt();
            remainingTimes[i] = burstTimes[i];
        }

        // find min arrival time
        int minArrivalTime = Integer.MAX_VALUE;
        for(int arrivalTime : arrivalTimes){
            minArrivalTime = Math.min(minArrivalTime,arrivalTime);
        }

        Queue<Integer> readyQueue = new LinkedList<>(); // declare ready queue
        Set<Integer> executed = new HashSet<>(); // to keep track of executed processes

        // put the process which arrived at very beginning to the queue. (initialize ready queue with first arrival process)
        for(int j = 0; j < processes; j++){
            if(arrivalTimes[j] == minArrivalTime){
                readyQueue.offer(j);
            }
        }


        int time = minArrivalTime; // to keep track of time
        int [] finishTimes = new int[processes];
        int [] turnaroundTimes = new int[processes];
        int [] waitingTimes = new int[processes];

        while (!readyQueue.isEmpty()){
            int process = findMinRemainingTimeProcess(readyQueue,remainingTimes,arrivalTimes,executed); // select the process

            time += 1; // execute it for time quantum 1
            remainingTimes[process] -=1; // reduce processes remaining time by 1

            // check whether process is executed completely
            if(remainingTimes[process] <= 0) {
                finishTimes[process] = time; // set finish time for that process
                readyQueue.remove(process);// remove that process from RQ and add to executed
                executed.add(process); // add that to executed
            }
            // Update ready queue. (in that time (1), if any new process arrives add that to the ready queue)
            for(int i = 0; i < processes; i++){
                if(!executed.contains(i) && !readyQueue.contains(i) && arrivalTimes[i] <= time){
                    readyQueue.add(i);
                }
            }
        }

        // Now calculate turnaround and waiting

        for(int i = 0; i < processes; i++){
            turnaroundTimes[i] = finishTimes[i] - arrivalTimes[i];
            waitingTimes[i] = turnaroundTimes[i] - burstTimes[i];
        }

         // Print the results
        System.out.println("Process \t Arrival Time \t Burst Time \t Finish Time \t Turnaround Time \t Waiting Time");
        for (int i = 0; i < processes; i++) {
            System.out.printf("P%d\t\t %d\t\t %d\t\t %d\t\t\t %d\t\t %d\n",
                    i, arrivalTimes[i], burstTimes[i], finishTimes[i], turnaroundTimes[i], waitingTimes[i]);
        }

    }

    private static int findMinRemainingTimeProcess(Queue<Integer> readyQueue, int [] remainingTimes,int [] arrivalTimes,Set<Integer>executed){
        // Find min remaining time
        int minRemTime = Integer.MAX_VALUE;
        for (int process : readyQueue) {
            if (!executed.contains(process) && remainingTimes[process] < minRemTime) {
                minRemTime = remainingTimes[process];
            }
        }

        // add process with remaining time equals minRemTime to the list
        List<Integer> processesWithSameRemTime = new ArrayList<>();
        for(int process : readyQueue){
            if(!executed.contains(process) && remainingTimes[process] == minRemTime){
                processesWithSameRemTime.add(process);
            }
        }
        // if there is only 1 process with min remaining time then just return that process
        if(processesWithSameRemTime.size() == 1){
            return processesWithSameRemTime.get(0);
        }

        // since there are more than 1 processes with same minimum remaining time , now compare them according to
        // their arrival time.
        int minArriTime = Integer.MAX_VALUE;
        int processId = -1;
        for(int process : processesWithSameRemTime){
            if(!executed.contains(process) && arrivalTimes[process] < minArriTime){
                minArriTime = arrivalTimes[process];
                processId = process;
            }
        }
        return processId;
    }
}

/*
input : 4 0 5 1 3 2 4 4 1
output :
Process 		 Arrival Time 		 Burst Time 		 Finish Time 		 Turnaround Time 		 Waiting Time
P0					0					5					9					9						4
P1					1					3					4					3						0
P2					2					4					13					11						7
P3					4					1					5					1						0



 */




















//  The Java code you provided implements Shortest Job First (SJF) scheduling in a preemptive manner, often referred to as Shortest Remaining Time First (SRTF). In this scheduling algorithm, at each moment, the process with the shortest remaining burst time is chosen to execute. If a new process arrives with a shorter burst time, the currently running process is preempted.

// Key Steps in the Code:
// 1. Input Collection:
// The number of processes is taken from the user.
// For each process, the arrival time and burst time are entered.
// An array remainingTimes[] is used to keep track of the remaining burst times of each process.
// 2. Initialization:
// The minArrivalTime variable stores the earliest arrival time.
// The readyQueue holds the processes that have arrived and are ready for execution.
// The executed set keeps track of the processes that have been executed.
// 3. Process Execution Loop:
// The time starts at the minArrivalTime and simulates the passage of time.
// The findMinRemainingTimeProcess() function is used to select the process with the shortest remaining burst time from the ready queue.
// Each process is executed for one time unit (time quantum of 1).
// After each execution step, the remaining burst time is reduced by 1.
// If a process completes (remaining burst time becomes 0), it is marked as finished, and its finish time is recorded.
// After executing a process, the ready queue is updated with any new processes that have arrived.
// 4. Calculating Turnaround and Waiting Times:
// Turnaround time is the difference between the finish time and arrival time.
// Waiting time is calculated as the turnaround time minus the burst time.
// 5. Output:
// The program prints a table showing the process ID, arrival time, burst time, finish time, turnaround time, and waiting time for each process.
// Code Walkthrough:
// Input: The program starts by prompting the user for the number of processes and their respective arrival and burst times.
// Execution Simulation: It then enters a loop that simulates the CPU processing these tasks, selecting the one with the shortest remaining burst time at each unit of time.
// Time Quantum: The program executes each process for a single time unit (1).
// Ready Queue Updates: Every time a process executes, the system checks if any new process has arrived at the current time and adds them to the ready queue.
// Completion: The program outputs a detailed table showing the scheduling results after all processes have finished.
// Example Run:
// Input:

// mathematica
// Copy code
// Enter number of processes: 4
// Enter arrival time for process P0: 0
// Enter burst time for process P0: 5
// Enter arrival time for process P1: 1
// Enter burst time for process P1: 3
// Enter arrival time for process P2: 2
// Enter burst time for process P2: 4
// Enter arrival time for process P3: 4
// Enter burst time for process P3: 1
// Output:

// css
// Copy code
// Process        Arrival Time    Burst Time    Finish Time    Turnaround Time    Waiting Time
// P0             0               5             9              9                  4
// P1             1               3             4              3                  0
// P2             2               4             13             11                 7
// P3             4               1             5              1                  0
// Detailed Explanation of Example:
// Time 0: P0 arrives, and no other process is ready yet.
// P0 starts executing for 1 unit of time.
// Time 1: P1 arrives.
// Since P1 has a shorter burst time (3 vs. 4 for P0), it preempts P0.
// P1 starts executing for 1 unit of time.
// Time 2: P2 arrives.
// P1 continues execution as it still has the shortest remaining time (2 units remaining).
// Time 3: P3 arrives.
// P1 completes execution (remaining time = 0).
// P0 resumes execution (since it now has the shortest remaining time).
// Time 4: P0, P2, and P3 are all ready.
// P0 continues, then P2 preempts P0 because it has the next shortest remaining burst time.
// The process continues until all processes are completed.
// Possible External Examiner Questions:
// Explain the difference between preemptive and non-preemptive SJF.

// In preemptive SJF (SRTF), the process with the shortest remaining burst time is selected at every time unit, even if a process is already executing. In non-preemptive SJF, once a process starts, it runs to completion before another process can start.
// What is the role of the remainingTimes[] array in this program?

// The remainingTimes[] array keeps track of the remaining burst time for each process as it executes, allowing the system to preempt a process if another process arrives with a shorter remaining time.
// Why do we need the findMinRemainingTimeProcess() function?

// The function finds the process with the minimum remaining time in the ready queue, which is crucial for implementing the preemptive nature of the SJF algorithm.
// How does the program handle multiple processes with the same remaining burst time?

// If multiple processes have the same remaining burst time, the program resolves the tie by selecting the process that arrived first (earliest arrival time).
// What would happen if the arrival time of all processes was the same?

// If all processes arrive at the same time, the program will select the process with the shortest burst time to execute first, and continue this until all processes are executed.
// Explain the time complexity of this code.

// The program loops through the ready queue and selects the process with the minimum remaining time in each cycle. The complexity of finding the process with the minimum remaining time in the ready queue is O(n). Since this happens for every process, the overall time complexity is O(n^2).
// Possible Improvements:
// Priority Queue: Using a priority queue (or min-heap) for the ready queue would allow the selection of the process with the shortest remaining time in O(log n) time, improving the overall time complexity to O(n log n).

// Edge Cases: Consider handling cases where multiple processes arrive at the exact same time or have the same burst time more efficiently.

// Input Validation: Add checks to ensure that burst times and arrival times are non-negative and valid.

// This implementation efficiently demonstrates the preemptive SJF scheduling algorithm, offering a clear simulation of how processes are scheduled based on their burst times, while preemptively choosing the shortest burst time at every time unit.