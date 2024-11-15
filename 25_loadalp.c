#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_INSTRUCTIONS 100
#define MAX_LINE_LENGTH 50


void load_alp_to_memory(const char *file_path) {
    char main_memory[MAX_INSTRUCTIONS][MAX_LINE_LENGTH];
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Error: Input file not found.\n");
        return;
    }


    int address = 0;
    while (fgets(main_memory[address], MAX_LINE_LENGTH, file) != NULL && address < MAX_INSTRUCTIONS) {
        main_memory[address][strcspn(main_memory[address], "\n")] = '\0'; // Remove newline character
        address++;
    }
    fclose(file);


    printf("ALP Program loaded into main memory:\n");
    for (int i = 0; i < address; i++) {
        printf("Address %d: %s\n", i, main_memory[i]);
    }
}


int main() {
    load_alp_to_memory("alp_program.txt");
    return 0;
}
































// Here’s a detailed explanation for the provided code following the 4-step approach:

// 1. Concept, Uses, and Why We Use It
// Concept: This program simulates loading an assembly-like language program (ALP) into memory. It reads each line of the ALP from a file and stores it in a 2D array representing main memory. The program then prints the contents of this simulated memory, showing the instructions loaded at different memory addresses.

// Uses:

// This type of program could be used in emulators for simulating how a CPU would load and execute a program from memory.
// It’s often useful in learning and simulating memory management and the storage of instructions during the execution of a program.
// Why We Use It:

// To understand how data (or instructions) are loaded into memory and stored at specific addresses.
// It demonstrates the concept of loading and storing instructions dynamically using memory (in this case, an array).
// 2. Logic and Algorithm
// Logic:

// The program reads a file containing instructions (ALP) line by line and stores these lines in a simulated memory array (main_memory). Each instruction corresponds to a specific memory address.
// It removes the newline character from each line to ensure the instructions are correctly formatted when stored.
// Once the file is read, the program prints out the contents of the memory with corresponding addresses.
// Algorithm:

// Open the file containing the ALP using fopen.
// Check if the file is successfully opened. If not, print an error and exit.
// Read the ALP line by line using fgets and store each line in the main_memory array.
// Ensure that the newline character at the end of each line is removed.
// After loading the program into memory, print the memory addresses and their corresponding instructions.
// 3. Line-by-Line Code Explanation
// c
// Copy code
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// stdio.h: Provides functions for input and output operations.
// stdlib.h: Provides functions for memory allocation, process control, and other utilities.
// string.h: Provides functions to manipulate strings, like strcspn.
// c
// Copy code
// #define MAX_INSTRUCTIONS 100
// #define MAX_LINE_LENGTH 50
// These are macro definitions:
// MAX_INSTRUCTIONS limits the number of instructions the program can store in memory.
// MAX_LINE_LENGTH defines the maximum length of each instruction.
// c
// Copy code
// void load_alp_to_memory(const char *file_path) {
// This defines the function load_alp_to_memory which will take the file path of the ALP as an argument and load it into memory.
// c
// Copy code
//     char main_memory[MAX_INSTRUCTIONS][MAX_LINE_LENGTH];
// Declares a 2D array main_memory that will simulate the main memory, capable of holding MAX_INSTRUCTIONS instructions, each up to MAX_LINE_LENGTH characters long.
// c
// Copy code
//     FILE *file = fopen(file_path, "r");
// Opens the file specified by file_path in read mode ("r").
// c
// Copy code
//     if (file == NULL) {
//         printf("Error: Input file not found.\n");
//         return;
//     }
// Checks if the file is successfully opened. If file is NULL, it means the file could not be found, so an error message is printed, and the function returns early.
// c
// Copy code
//     int address = 0;
//     while (fgets(main_memory[address], MAX_LINE_LENGTH, file) != NULL && address < MAX_INSTRUCTIONS) {
// Declares address to track the current memory location. The while loop reads one line from the file at a time into main_memory[address], stopping when the end of the file (fgets returns NULL) or the memory limit is reached.
// c
// Copy code
//         main_memory[address][strcspn(main_memory[address], "\n")] = '\0'; // Remove newline character
//         address++;
//     }
// This line removes the newline character from the end of each line read by fgets. strcspn finds the position of the newline character, and the assignment replaces it with the null terminator \0 to properly end the string.
// address++ increments the address to store the next instruction in the next memory location.
// c
// Copy code
//     fclose(file);
// Closes the file after reading all the instructions.
// c
// Copy code
//     printf("ALP Program loaded into main memory:\n");
//     for (int i = 0; i < address; i++) {
//         printf("Address %d: %s\n", i, main_memory[i]);
//     }
// After loading the instructions into memory, the program prints each instruction along with its corresponding memory address (using a loop to iterate over the main_memory array).
// c
// Copy code
// }
// Ends the function load_alp_to_memory.
// c
// Copy code
// int main() {
//     load_alp_to_memory("alp_program.txt");
//     return 0;
// }
// The main function calls load_alp_to_memory with the file "alp_program.txt". This file should contain the ALP instructions to be loaded into memory.
// The program ends with return 0, indicating successful execution.
// 4. Possible Questions and Answers
// Q1: What is the purpose of the strcspn function in this program?

// Answer: The strcspn function is used to find the index of the first occurrence of a specified character (in this case, the newline \n) in a string. It's used here to remove the newline character from each instruction after reading it with fgets.
// Q2: What would happen if fgets tries to read more than MAX_LINE_LENGTH characters?

// Answer: If the line in the file exceeds MAX_LINE_LENGTH, fgets will stop reading at the MAX_LINE_LENGTH-th character, leaving the rest of the line in the file. This could result in truncation of data, and the remaining characters would not be read in the current call to fgets.
// Q3: How does the program handle a situation where the file has more than MAX_INSTRUCTIONS?

// Answer: The program reads up to MAX_INSTRUCTIONS lines, stopping once it reaches this limit. Any additional lines in the file will be ignored, and the program will not process them.
// Q4: Why is the memory array main_memory defined with fixed sizes, and what could be a potential issue with this?

// Answer: main_memory is defined with fixed sizes (MAX_INSTRUCTIONS and MAX_LINE_LENGTH) to limit memory usage and ensure the program can run on machines with limited resources. A potential issue is that if the program tries to load a file with more instructions or longer lines than allowed, it will either truncate data or fail to load the file entirely.
// Q5: How can you modify the program to handle a larger number of instructions dynamically?

// Answer: One way to handle a larger number of instructions would be to dynamically allocate memory for the main_memory array using malloc or calloc, allowing the array to grow based on the actual number of instructions in the file.
// Q6: What does the program print if the file is empty or has no valid instructions?

// Answer: If the file is empty or contains no valid instructions, the program will still print "ALP Program loaded into main memory:", but there will be no instructions printed because the loop will not execute due to no data being read.