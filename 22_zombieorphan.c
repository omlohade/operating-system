#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


void createZombieProcess() {
    pid_t pid = fork();


    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }


    if (pid > 0) {  // Parent process
        printf("Parent process: Zombie process created. PID = %d\n", pid);
        sleep(10);  
    } 
    else {  // Child process
        printf("Child process exiting to become zombie.\n");
        exit(0);  
    }
}
void createOrphanProcess() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }


    if (pid > 0) {  // Parent process
        printf("Parent process exiting to create orphan process.\n");
        exit(0);  
    } 
    else {  // Child process
        sleep(5);  
        printf("Child process (orphan) continuing after parent termination. PID = %d\n", getpid());
    }
}
void sumEvenOdd(int arr[], int size) {
    pid_t pid = fork();


    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pid > 0) {  // Parent process
        int evenSum = 0;
        for (int i = 0; i < size; i++) {
            if (arr[i] % 2 == 0) {
                evenSum += arr[i];
            }
        }
        printf("Parent process: Sum of even numbers = %d\n", evenSum);
        wait(NULL);  
    } 
    else {  // Child process
        int oddSum = 0;
        for (int i = 0; i < size; i++) {
            if (arr[i] % 2 != 0) {
                oddSum += arr[i];
            }
        }
        printf("Child process: Sum of odd numbers = %d\n", oddSum);
        exit(0);
    }
}
int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("Calculating sum of even and odd numbers:\n");
    sumEvenOdd(arr, size);


    printf("\nCreating a zombie process:\n");
    createZombieProcess();
    sleep(5);  


    printf("\nCreating an orphan process:\n");
    createOrphanProcess();
    return 0;
}




// Overview
// This program demonstrates three key concepts of process management in operating systems:

// Zombie Processes: A process that has completed execution but still occupies a process table entry because its parent hasn’t read its exit status.
// Orphan Processes: A child process whose parent has terminated.
// Inter-Process Communication (IPC) Using Fork: Parent and child processes collaborate to compute the sum of even and odd numbers from an array.
// Code Breakdown
// Header Files
// c
// Copy code
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>
// stdio.h: Provides input/output functions (printf).
// stdlib.h: Contains memory management and process control functions (exit).
// unistd.h: Provides the fork, sleep, and getpid functions.
// sys/wait.h: Used for the wait function to manage child processes.
// 1. Zombie Process Creation
// c
// Copy code
// void createZombieProcess() {
//     pid_t pid = fork();
// Fork: Creates a new child process. pid holds:
// > 0: Parent process.
// 0: Child process.
// < 0: Fork failed.
// c
// Copy code
//     if (pid < 0) {
//         perror("Fork failed");
//         exit(1);
//     }
// If fork fails, an error message is displayed, and the program exits.
// c
// Copy code
//     if (pid > 0) {  // Parent process
//         printf("Parent process: Zombie process created. PID = %d\n", pid);
//         sleep(10);  
//     } 
// Parent Process: Prints the PID of the zombie process and delays for 10 seconds to ensure the child becomes a zombie (child exits before parent reads its status).
// c
// Copy code
//     else {  // Child process
//         printf("Child process exiting to become zombie.\n");
//         exit(0);  
//     }
// Child Process: Exits immediately, creating a zombie. The parent hasn’t yet called wait, so the child’s entry remains in the process table.
// 2. Orphan Process Creation
// c
// Copy code
// void createOrphanProcess() {
//     pid_t pid = fork();
// Forks a new child process.
// c
// Copy code
//     if (pid < 0) {
//         perror("Fork failed");
//         exit(1);
//     }
// Handles fork failure.
// c
// Copy code
//     if (pid > 0) {  // Parent process
//         printf("Parent process exiting to create orphan process.\n");
//         exit(0);  
//     } 
// Parent Process: Exits immediately, leaving the child process as an orphan.
// c
// Copy code
//     else {  // Child process
//         sleep(5);  
//         printf("Child process (orphan) continuing after parent termination. PID = %d\n", getpid());
//     }
// Child Process:
// Becomes an orphan when the parent exits.
// Is adopted by the init (or systemd) process.
// Sleeps for 5 seconds to ensure the parent exits first, then continues execution.
// 3. Sum of Even and Odd Numbers Using Fork
// c
// Copy code
// void sumEvenOdd(int arr[], int size) {
//     pid_t pid = fork();
// Forks a new child process.
// c
// Copy code
//     if (pid < 0) {
//         perror("Fork failed");
//         exit(1);
//     }
// Handles fork failure.
// c
// Copy code
//     if (pid > 0) {  // Parent process
//         int evenSum = 0;
//         for (int i = 0; i < size; i++) {
//             if (arr[i] % 2 == 0) {
//                 evenSum += arr[i];
//             }
//         }
//         printf("Parent process: Sum of even numbers = %d\n", evenSum);
//         wait(NULL);  
//     } 
// Parent Process:
// Calculates the sum of even numbers.
// Waits for the child to complete using wait.
// c
// Copy code
//     else {  // Child process
//         int oddSum = 0;
//         for (int i = 0; i < size; i++) {
//             if (arr[i] % 2 != 0) {
//                 oddSum += arr[i];
//             }
//         }
//         printf("Child process: Sum of odd numbers = %d\n", oddSum);
//         exit(0);
//     }
// Child Process:
// Calculates the sum of odd numbers.
// Exits after displaying the result.
// 4. Main Function
// c
// Copy code
// int main() {
//     int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  
//     int size = sizeof(arr) / sizeof(arr[0]);
//     printf("Calculating sum of even and odd numbers:\n");
//     sumEvenOdd(arr, size);
// Initializes an array of integers and calculates the sum of even and odd numbers.
// c
// Copy code
//     printf("\nCreating a zombie process:\n");
//     createZombieProcess();
//     sleep(5);  
// Creates a zombie process and waits for 5 seconds to observe its behavior.
// c
// Copy code
//     printf("\nCreating an orphan process:\n");
//     createOrphanProcess();
//     return 0;
// }
// Creates an orphan process.
// Sample Execution
// Output:
// arduino
// Copy code
// Calculating sum of even and odd numbers:
// Parent process: Sum of even numbers = 30
// Child process: Sum of odd numbers = 25

// Creating a zombie process:
// Child process exiting to become zombie.
// Parent process: Zombie process created. PID = 12345

// Creating an orphan process:
// Parent process exiting to create orphan process.
// Child process (orphan) continuing after parent termination. PID = 12346
// Key Concepts Demonstrated
// Zombie Process:

// Parent process sleeps to delay calling wait, leaving the child process as a zombie.
// Orphan Process:

// Parent process exits immediately, leaving the child process as an orphan.
// Fork and IPC:

// Demonstrates collaboration between parent and child processes to compute even and odd sums.
// Possible Questions
// Conceptual:
// What is a zombie process?

// A process that has completed execution but whose exit status hasn’t been read by its parent.
// How is an orphan process handled in Linux?

// It is adopted by the init (or systemd) process.
// What happens if the parent never calls wait?

// Zombie processes accumulate, potentially exhausting system resources.
// Code-Specific:
// What is the purpose of wait in the parent process?

// To clean up the terminated child process and prevent zombie processes.
// Why does the child process in createOrphanProcess sleep for 5 seconds?

// To ensure it executes after the parent process has exited.
// How is the array size calculated in main?

// By dividing the total size of the array by the size of one element.
// Let me know if you need further clarification or modifications!
