#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int max[MAX_PROCESSES][MAX_RESOURCES];        // Maximum resource needs of each process
int allocation[MAX_PROCESSES][MAX_RESOURCES];  // Currently allocated resources to each process
int need[MAX_PROCESSES][MAX_RESOURCES];        // Remaining resources needed by each process
int available[MAX_RESOURCES];                  // Available resources
int numProcesses, numResources;

// Function to calculate the Need matrix
void calculateNeed() {
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check if the system is in a safe state
bool isSafe(int safeSeq[]) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES];
    int count = 0;

    // Initialize Work and Finish
    for (int i = 0; i < numResources; i++)
        work[i] = available[i];

    for (int i = 0; i < numProcesses; i++)
        finish[i] = false;

    // Find a safe sequence
    while (count < numProcesses) {
        bool found = false;
        for (int p = 0; p < numProcesses; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < numResources; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == numResources) {
                    for (int k = 0; k < numResources; k++)
                        work[k] += allocation[p][k];
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < numProcesses; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
    return true;
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter the number of resources: ");
    scanf("%d", &numResources);

    // Input Maximum Resource Requirements as a matrix
    printf("Enter the Max matrix (%d x %d):\n", numProcesses, numResources);
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Allocation Resource Matrix as a matrix
    printf("Enter the Allocation matrix (%d x %d):\n", numProcesses, numResources);
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Available Resources as a single row
    printf("Enter the Available resources vector (%d):\n", numResources);
    for (int i = 0; i < numResources; i++) {
        scanf("%d", &available[i]);
    }

    // Calculate the Need matrix
    calculateNeed();

    // Print Need matrix
    printf("Need matrix:\n");
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Print Available Resources
    printf("Available Resources: ");
    for (int i = 0; i < numResources; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");

    int safeSeq[MAX_PROCESSES]; // Array to store safe sequence

    // Check for safe state
    isSafe(safeSeq);

    return 0;
}

/*
5
3
7
5
3
3
2
2
9
0
2
4
2
2
5
3
3
0
1
0
2
0
0
3
0
2
2
1
1
0
0
2
3
3
2
*/

/*
Input: 
Enter the number of processes: 5
Enter the number of resources: 3
Enter the Max matrix (5 x 3):
7
5
3
3
2
2
9
0
2
4
2
2
5
3
3
Enter the Allocation matrix (5 x 3):
0
1
0
2
0
0
3
0
2
2
1
1
0
0
2
Enter the Available resources vector (3):
3
3
2

Output:
Need matrix:
7 4 3 
1 2 2 
6 0 0 
2 1 1 
5 3 1 
Available Resources: 3 3 2 
System is in a safe state.
Safe sequence is: P1 P3 P4 P0 P2

*/




















// 1. Concept Explanation: Banker's Algorithm for Resource Allocation
// The Banker's Algorithm is a resource allocation and deadlock avoidance algorithm. It checks if a system is in a safe state by simulating the allocation of resources to processes in such a way that no deadlock occurs. A safe state is a state where there exists a sequence of processes that can execute to completion without causing any deadlock. This algorithm is widely used in operating systems to ensure that resources are allocated safely, preventing system deadlocks.

// Why We Use the Banker's Algorithm:
// Safety: To determine whether a system is in a safe state or not, i.e., whether resources can be allocated to processes without leading to a deadlock.
// Deadlock Avoidance: To ensure that resource allocation to processes doesn't lead to deadlock, the system checks whether a process can complete with the current available resources.
// Resource Management: It helps manage the resources in a system by ensuring that all processes get the required resources at different points without running into deadlock situations.
// 2. Explanation of Logic:
// The algorithm works by simulating the allocation of resources to processes and checking if the system will eventually enter a safe state. The key steps are:

// Need Matrix Calculation: Calculate the remaining resources (need) for each process. This is the difference between the maximum required resources and the already allocated resources.
// Safety Check (Is Safe): Check if there exists a safe sequence of processes such that each process can get the resources it needs without causing a deadlock. If we can find such a sequence, the system is in a safe state; otherwise, it is not.
// Steps of Banker's Algorithm:
// Calculate the Need matrix.
// Work and Finish Arrays: The Work array holds the currently available resources, and the Finish array is used to track which processes have finished.
// The algorithm tries to find a process that can complete with the available resources (i.e., its need can be met by the available resources).
// Once a process can finish, its allocated resources are returned to the system, updating the Work array.
// This is repeated until either all processes finish (safe state) or no process can proceed (unsafe state).
// 3. Code Explanation (Line by Line):
// c
// Copy code
// #include <stdio.h>
// #include <stdbool.h>

// #define MAX_PROCESSES 10
// #define MAX_RESOURCES 10
// Headers and constants: Includes standard libraries and defines constants for maximum number of processes and resources.
// c
// Copy code
// int max[MAX_PROCESSES][MAX_RESOURCES];        // Maximum resource needs of each process
// int allocation[MAX_PROCESSES][MAX_RESOURCES];  // Currently allocated resources to each process
// int need[MAX_PROCESSES][MAX_RESOURCES];        // Remaining resources needed by each process
// int available[MAX_RESOURCES];                  // Available resources
// int numProcesses, numResources;
// Global Variables: Arrays to hold the maximum resource needs (max), the resources allocated to each process (allocation), the resources still needed (need), and the currently available resources (available).
// numProcesses and numResources are the number of processes and resources input by the user.
// c
// Copy code
// void calculateNeed() {
//     for (int i = 0; i < numProcesses; i++) {
//         for (int j = 0; j < numResources; j++) {
//             need[i][j] = max[i][j] - allocation[i][j];
//         }
//     }
// }
// Calculate the Need Matrix: This function calculates the remaining resources required for each process by subtracting the allocated resources from the maximum required resources.
// c
// Copy code
// bool isSafe(int safeSeq[]) {
//     int work[MAX_RESOURCES];
//     bool finish[MAX_PROCESSES];
//     int count = 0;
// isSafe Function: Checks if the system is in a safe state.
// Initializes work to the available resources.
// Initializes finish to false for all processes, indicating that no process has finished yet.
// c
// Copy code
//     for (int i = 0; i < numResources; i++)
//         work[i] = available[i];

//     for (int i = 0; i < numProcesses; i++)
//         finish[i] = false;
// Initialization: Copies the available resources into work and sets finish for all processes to false.
// c
// Copy code
//     while (count < numProcesses) {
//         bool found = false;
//         for (int p = 0; p < numProcesses; p++) {
//             if (!finish[p]) {
//                 int j;
//                 for (j = 0; j < numResources; j++)
//                     if (need[p][j] > work[j])
//                         break;

//                 if (j == numResources) {
//                     for (int k = 0; k < numResources; k++)
//                         work[k] += allocation[p][k];
//                     safeSeq[count++] = p;
//                     finish[p] = true;
//                     found = true;
//                 }
//             }
//         }

//         if (!found) {
//             printf("System is not in a safe state.\n");
//             return false;
//         }
//     }
// Safety Check: This while loop attempts to find a safe sequence. It checks each process if its remaining needs can be met with the available resources (work). If a process can finish, its allocated resources are added back to work, and the process is marked as finished (finish[p] = true).
// c
// Copy code
//     printf("System is in a safe state.\nSafe sequence is: ");
//     for (int i = 0; i < numProcesses; i++)
//         printf("P%d ", safeSeq[i]);
//     printf("\n");
//     return true;
// }
// Final Output: If all processes finish, it prints the safe sequence. Otherwise, it prints that the system is not in a safe state.
// c
// Copy code
// int main() {
//     printf("Enter the number of processes: ");
//     scanf("%d", &numProcesses);
//     printf("Enter the number of resources: ");
//     scanf("%d", &numResources);
// Main Function Input: Prompts the user to enter the number of processes and resources.
// c
// Copy code
//     printf("Enter the Max matrix (%d x %d):\n", numProcesses, numResources);
//     for (int i = 0; i < numProcesses; i++) {
//         for (int j = 0; j < numResources; j++) {
//             scanf("%d", &max[i][j]);
//         }
//     }
// Input Maximum Resource Matrix: The user enters the max matrix, which holds the maximum resource needs for each process.
// c
// Copy code
//     printf("Enter the Allocation matrix (%d x %d):\n", numProcesses, numResources);
//     for (int i = 0; i < numProcesses; i++) {
//         for (int j = 0; j < numResources; j++) {
//             scanf("%d", &allocation[i][j]);
//         }
//     }
// Input Allocation Matrix: The user enters the allocation matrix, which indicates how many resources are currently allocated to each process.
// c
// Copy code
//     printf("Enter the Available resources vector (%d):\n", numResources);
//     for (int i = 0; i < numResources; i++) {
//         scanf("%d", &available[i]);
//     }
// Input Available Resources: The user inputs the available resources vector, which shows the currently available resources in the system.
// c
// Copy code
//     calculateNeed();
// Calculate Need: The calculateNeed function is called to populate the need matrix.
// c
// Copy code
//     printf("Need matrix:\n");
//     for (int i = 0; i < numProcesses; i++) {
//         for (int j = 0; j < numResources; j++) {
//             printf("%d ", need[i][j]);
//         }
//         printf("\n");
//     }
// Display Need Matrix: The program prints the need matrix, which shows how many more resources each process needs.
// c
// Copy code
//     printf("Available Resources: ");
//     for (int i = 0; i < numResources; i++) {
//         printf("%d ", available[i]);
//     }
//     printf("\n");
// Display Available Resources: The program prints the available resources.
// c
// Copy code
//     int safeSeq[MAX_PROCESSES]; // Array to store safe sequence
//     isSafe(safeSeq);
//     return 0;
// }
// Check Safe State and Output: The isSafe function is called to check if the system is in a safe state and print the safe sequence if possible.
// 4. Answering the Generated Questions from Examiner:
// What is the Banker's Algorithm, and how does it help in deadlock avoidance?

// Banker's Algorithm is a resource allocation and deadlock avoidance algorithm used in operating systems. It simulates resource allocation for processes and determines if a safe sequence of process executions exists that avoids deadlock. It checks if resources can be allocated in such a way that the system remains in a safe state after the allocation. If the system cannot guarantee that the allocation will lead to a safe state, the request is denied, thereby avoiding deadlock.
// Explain the Need matrix and how it is calculated.

// The Need matrix is a matrix used in the Banker's Algorithm that represents the remaining resource needs of each process. It is calculated by subtracting the Allocated matrix from the Maximum matrix for each process. In other words:
// Need[i][j]
// =
// Maximum[i][j]
// −
// Allocated[i][j]
// Need[i][j]=Maximum[i][j]−Allocated[i][j]
// The Need matrix tells how many more resources each process requires to finish its execution.
// What is the significance of the Work and Finish arrays in the Banker's Algorithm?

// The Work array represents the available resources at any point in time. Initially, it is set to the available resources. After each process finishes, the resources allocated to that process are added back to the Work array.
// The Finish array is used to keep track of which processes have completed execution. A process is marked as finished when it can obtain all the resources it needs and completes its execution, allowing the resources to be reclaimed.
// How does the Banker's Algorithm ensure that the system is in a safe state?

// The Banker's Algorithm ensures the system remains in a safe state by checking if there exists at least one process whose remaining need can be satisfied with the currently available resources. If such a process is found, it is allowed to execute, and its allocated resources are returned to the system. The algorithm continues this process until all processes are executed or no further processes can execute, confirming whether the system is in a safe state or not.
// What happens if no safe sequence is found? How does the algorithm detect an unsafe state?

// If no safe sequence is found, it indicates that the system is in an unsafe state. The algorithm detects this by attempting to find a process whose needs can be satisfied with the available resources. If, after checking all processes, no such process can be found, the system is declared unsafe, and deadlock may occur.
// Explain the difference between safe state and unsafe state.

// A safe state is one where there exists a sequence of process executions such that each process can eventually obtain all the resources it needs and finish execution without causing a deadlock. In contrast, an unsafe state is one where no such sequence exists, and there is a possibility of deadlock.
// How does the algorithm handle resource allocation for multiple processes?

// The Banker's Algorithm handles resource allocation for multiple processes by considering each process's maximum resource needs and its current allocations. It only grants a resource request if it guarantees that doing so will leave the system in a safe state, meaning all processes can eventually complete.
// Can this algorithm be applied to a system with dynamic processes or resources? Why or why not?

// The Banker's Algorithm assumes a static system where the number of processes and resources are fixed at the beginning. For systems with dynamic processes or resources (e.g., processes can arrive or resources can be added/removed during execution), the Banker's Algorithm cannot be directly applied, as it would need continuous re-evaluation of the state and the available resources, which makes it impractical for such dynamic environments.
// How would the algorithm behave if resources or processes are added after the initial state is checked?

// If resources or processes are added after the initial check, the Banker's Algorithm would need to be re-run to ensure the system remains in a safe state. If new processes arrive, the algorithm needs to reassess whether the current available resources can satisfy their maximum needs without causing deadlock.
// What are the limitations of the Banker's Algorithm in real-time systems or large-scale systems?

// The Banker's Algorithm has several limitations, especially in real-time or large-scale systems:
// Performance Overhead: The algorithm requires frequent checking of the system's state and recalculating resources, which can be computationally expensive.
// Static Resource Assumption: It assumes that the maximum resource needs and the number of processes are fixed, which is often not the case in real-time systems.
// Limited Scalability: As the number of processes and resource types grows, the algorithm's complexity increases exponentially, making it impractical for large-scale systems.
// Inflexibility in Dynamic Systems: It is not well-suited to systems with dynamic resources or processes, as it requires the system to remain static or periodically re-evaluate its state, which can introduce delays and inefficiencies.





