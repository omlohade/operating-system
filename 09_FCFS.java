import java.util.*;

public class FCFS {
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

        // Array to store indices of processes sorted by arrival time
        Integer[] indices = new Integer[processes];
        for (int i = 0; i < processes; i++) indices[i] = i;

        // Sort indices by arrival time to ensure FCFS order
        Arrays.sort(indices, Comparator.comparingInt(i -> arrivalTimes[i]));

        int[] finishTimes = new int[processes];
        int[] turnaroundTimes = new int[processes];
        int[] waitingTimes = new int[processes];

        int time = 0;
        for (int i = 0; i < processes; i++) {
            int process = indices[i];

            // If the process arrives after the current time, jump to its arrival time
            if (time < arrivalTimes[process]) {
                time = arrivalTimes[process];
            }

            // Calculate finish time
            time += burstTimes[process];
            finishTimes[process] = time;

            // Calculate turnaround time and waiting time
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
}
/*
input : 4 0 2 1 2 5 3 6 4
Process 	 Arrival Time 	 Burst Time 	 Finish Time 	 Turnaround Time 	 Waiting Time
P0				 0				 2				 2					 2				 0
P1				 1				 2				 4					 3				 1
P2				 5				 3				 8					 3				 0
P3				 6				 4				 12					 6				 2
 */




















 
//  The code you've shared implements the First-Come, First-Served (FCFS) scheduling algorithm for CPU scheduling in Java. In this algorithm, the processes are executed in the order of their arrival times. The code calculates the finish time, turnaround time, and waiting time for each process based on the arrival and burst times provided by the user.

//  Here's a step-by-step breakdown and potential examiner questions based on the code:
 
//  1. Code Explanation:
//  Input:
//  The program first takes the number of processes as input.
//  For each process, the program takes the arrival time and burst time.
//  Key Variables:
//  arrivalTimes[]: Array holding the arrival times of all processes.
//  burstTimes[]: Array holding the burst times (execution times) of the processes.
//  finishTimes[]: Array to store the finish times of the processes.
//  turnaroundTimes[]: Array to store the turnaround times of the processes.
//  waitingTimes[]: Array to store the waiting times of the processes.
//  indices[]: An array used to store the indices of processes, sorted by arrival time to ensure FCFS execution order.
//  Sorting:
//  The processes are sorted by arrival time using Arrays.sort(indices, Comparator.comparingInt(i -> arrivalTimes[i]));. This ensures that processes are executed in the order in which they arrive.
//  Process Execution:
//  The program simulates the execution of the processes. It tracks the current time and processes are executed in the order of their arrival times.
//  Finish Time: The finish time for each process is calculated as the sum of the burst time starting from the current time.
//  Turnaround Time: Calculated as the difference between the finish time and arrival time.
//  Waiting Time: Calculated as the difference between the turnaround time and burst time.
//  Output:
//  The program prints the process ID, arrival time, burst time, finish time, turnaround time, and waiting time in a tabular format.
//  2. Code Walkthrough:
//  Input Collection:
 
//  The program first collects the number of processes, then it loops through each process to collect the arrival and burst times.
//  Sorting the Processes:
 
//  The processes are sorted by their arrival time using a custom comparator. This ensures that we follow the FCFS scheduling rule (processes that arrive first are executed first).
//  Process Execution Simulation:
 
//  The program keeps track of the current time (time), and as it processes each task, it updates this time by adding the burst time of the current process.
//  For each process:
//  The finish time is calculated.
//  The turnaround time is calculated as the difference between finish time and arrival time.
//  The waiting time is calculated as the turnaround time minus burst time.
//  Output the Results:
 
//  After processing all the processes, the results are printed in a formatted table, showing the required times for each process.
//  3. Example Run:
//  Given the input:
 
//  mathematica
//  Copy code
//  Enter number of processes: 4
//  Enter arrival time for process P0: 0
//  Enter burst time for process P0: 2
//  Enter arrival time for process P1: 1
//  Enter burst time for process P1: 2
//  Enter arrival time for process P2: 5
//  Enter burst time for process P2: 3
//  Enter arrival time for process P3: 6
//  Enter burst time for process P3: 4
//  The output will be:
 
//  css
//  Copy code
//  Process 	 Arrival Time 	 Burst Time 	 Finish Time 	 Turnaround Time 	 Waiting Time
//  P0				 0				 2				 2					 2				 0
//  P1				 1				 2				 4					 3				 1
//  P2				 5				 3				 8					 3				 0
//  P3				 6				 4				 12					 6				 2
//  4. Potential External Examiner Questions:
//  Explain the FCFS scheduling algorithm and how the code implements it.
 
//  FCFS processes jobs in the order they arrive. The code implements this by sorting the processes by their arrival time and then processing each one in sequence.
//  What is the time complexity of sorting the processes in this code?
 
//  The sorting step (Arrays.sort) has a time complexity of O(n log n), where n is the number of processes.
//  What would happen if the processes were not sorted by arrival time?
 
//  If the processes were not sorted by arrival time, the FCFS scheduling order would not be followed, leading to incorrect results for the finish time, turnaround time, and waiting time.
//  How is the waiting time for each process calculated in this program?
 
//  Waiting time is calculated as the turnaround time minus the burst time (waitingTimes[process] = turnaroundTimes[process] - burstTimes[process]).
//  What are the limitations of the FCFS algorithm?
 
//  FCFS can lead to convoy effect, where shorter processes have to wait for longer processes to finish, causing long waiting times for shorter jobs. It also doesn't handle priorities or preemption.
//  How would you modify this code to implement another scheduling algorithm, such as Shortest Job Next (SJN)?
 
//  To implement SJN, you would need to sort processes by their burst times (instead of arrival times) and handle them based on the shortest burst time first, while considering their arrival time.
//  What is the role of the time variable in the code?
 
//  The time variable keeps track of the current time in the system. It is updated as each process is executed and helps calculate the finish, turnaround, and waiting times.
//  5. Suggestions for Improvement:
//  Add Validation: Ensure that the input times (arrival and burst) are valid (e.g., non-negative).
//  Handle Edge Cases: Consider edge cases like multiple processes having the same arrival time.
//  Efficiency Improvements: For larger numbers of processes, optimizing the sorting and computation of times might become necessary.
//  This code correctly implements FCFS scheduling but is limited in handling larger sets of processes or more complex scheduling scenarios.

 