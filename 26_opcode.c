#include <stdio.h>
#include <string.h>


#define MAX_INSTRUCTIONS 100
#define MAX_LINE_LENGTH 50


const char *valid_opcodes[] = {"LOAD", "STORE", "ADD", "SUB", "JMP", "HALT"};
#define NUM_OPCODES (sizeof(valid_opcodes) / sizeof(valid_opcodes[0]))


int is_valid_opcode(const char *opcode) {
    for (int i = 0; i < NUM_OPCODES; i++) {
        if (strcmp(opcode, valid_opcodes[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


void check_opcode_errors(char main_memory[][MAX_LINE_LENGTH], int instruction_count) {
    for (int i = 0; i < instruction_count; i++) {
        char opcode[MAX_LINE_LENGTH];
        sscanf(main_memory[i], "%s", opcode);  // Extract the first word as opcode
        if (!is_valid_opcode(opcode)) {
            printf("Opcode error at address %d: Invalid opcode '%s'\n", i, opcode);
        }
    }
}


int main() {
    char main_memory[MAX_INSTRUCTIONS][MAX_LINE_LENGTH] = {
        "LOAD R1, 100",
        "STOREE R2, 200", // Invalid opcode for testing
        "ADD R1, R2",
        "INVALID_OP R3, 300" // Invalid opcode for testing
    };
    int instruction_count = 4;
    check_opcode_errors(main_memory, instruction_count);
    return 0;
}












// Here’s the detailed explanation of the provided code following the 4-step approach:

// 1. Concept, Uses, and Why We Use It
// Concept: This program is designed to check the validity of opcodes in a simulated assembly-like language program (ALP). It reads a set of instructions stored in a memory array and checks whether each instruction uses a valid opcode. The program detects invalid opcodes and reports errors.

// Uses:

// This type of validation is common in emulators and assemblers, where a program written in a low-level language is checked for syntactical errors, particularly ensuring that all opcodes are recognized and valid.
// It can be used in learning environments to simulate instruction execution and error detection in assembly-like programming.
// Why We Use It:

// To ensure that the ALP is syntactically correct before execution.
// To detect programming mistakes in assembly or machine code programs by validating the usage of opcodes.
// It simplifies debugging by catching errors related to invalid opcodes before they cause runtime issues.
// 2. Logic and Algorithm
// Logic:

// The program stores a set of ALP instructions in a 2D array (main_memory) where each instruction is a string.
// The program iterates through each instruction, extracts the opcode (the first word in the instruction), and checks whether it is one of the predefined valid opcodes (using the is_valid_opcode function).
// If an invalid opcode is found, it prints an error message indicating the address and the invalid opcode.
// Algorithm:

// Define a list of valid opcodes (valid_opcodes[]) to compare against.
// Loop through each instruction in the memory array (main_memory[]).
// For each instruction, extract the opcode (the first word) using sscanf.
// Compare the extracted opcode with the list of valid opcodes.
// If the opcode is not valid, print an error message with the instruction address and the invalid opcode.
// 3. Line-by-Line Code Explanation
// c
// Copy code
// #include <stdio.h>
// #include <string.h>
// stdio.h: This header file provides input and output functions like printf, which is used to print messages to the console.
// string.h: Provides functions for string manipulation, like strcmp (used for comparing strings) and sscanf (used for parsing strings).
// c
// Copy code
// #define MAX_INSTRUCTIONS 100
// #define MAX_LINE_LENGTH 50
// MAX_INSTRUCTIONS defines the maximum number of instructions that can be stored in memory.
// MAX_LINE_LENGTH defines the maximum length of each instruction string.
// c
// Copy code
// const char *valid_opcodes[] = {"LOAD", "STORE", "ADD", "SUB", "JMP", "HALT"};
// #define NUM_OPCODES (sizeof(valid_opcodes) / sizeof(valid_opcodes[0]))
// valid_opcodes[]: An array containing the valid opcodes that are allowed in the ALP. Each opcode corresponds to a common operation in assembly-like programming.
// NUM_OPCODES: This calculates the number of valid opcodes by dividing the total size of the valid_opcodes array by the size of one opcode string.
// c
// Copy code
// int is_valid_opcode(const char *opcode) {
//     for (int i = 0; i < NUM_OPCODES; i++) {
//         if (strcmp(opcode, valid_opcodes[i]) == 0) {
//             return 1; // Opcode found, valid
//         }
//     }
//     return 0; // Opcode not found, invalid
// }
// is_valid_opcode(): This function takes an opcode string and compares it against the list of valid opcodes.
// It loops through the valid_opcodes[] array and compares each opcode with the input opcode using strcmp.
// If a match is found, the function returns 1 (valid). If no match is found after looping through the list, it returns 0 (invalid).
// c
// Copy code
// void check_opcode_errors(char main_memory[][MAX_LINE_LENGTH], int instruction_count) {
// check_opcode_errors(): This function takes the main_memory array (which contains the ALP instructions) and the number of instructions (instruction_count) as arguments.
// It will check each instruction to see if it contains a valid opcode.
// c
// Copy code
//     for (int i = 0; i < instruction_count; i++) {
//         char opcode[MAX_LINE_LENGTH];
//         sscanf(main_memory[i], "%s", opcode);  // Extract the first word as opcode
// This for loop iterates over each instruction in memory.
// The sscanf function reads the first word from each instruction (which is assumed to be the opcode) and stores it in the opcode string.
// c
// Copy code
//         if (!is_valid_opcode(opcode)) {
//             printf("Opcode error at address %d: Invalid opcode '%s'\n", i, opcode);
//         }
//     }
// }
// This checks if the extracted opcode is valid by calling the is_valid_opcode function.
// If the opcode is invalid (i.e., is_valid_opcode returns 0), it prints an error message with the instruction address (i) and the invalid opcode.
// c
// Copy code
// int main() {
//     char main_memory[MAX_INSTRUCTIONS][MAX_LINE_LENGTH] = {
//         "LOAD R1, 100",
//         "STOREE R2, 200", // Invalid opcode for testing
//         "ADD R1, R2",
//         "INVALID_OP R3, 300" // Invalid opcode for testing
//     };
// The main() function starts by defining an array main_memory which holds some example instructions.
// There are two invalid opcodes ("STOREE" and "INVALID_OP") included for testing error detection.
// c
// Copy code
//     int instruction_count = 4;
//     check_opcode_errors(main_memory, instruction_count);
//     return 0;
// }
// The instruction_count is set to 4, which is the number of instructions in main_memory.
// It then calls check_opcode_errors to check the instructions for invalid opcodes.
// The program returns 0 to indicate successful completion.
// 4. Possible Questions and Answers
// Q1: How does the is_valid_opcode function work?

// Answer: The is_valid_opcode function compares the input opcode against a predefined list of valid opcodes. It uses the strcmp function to perform the comparison and returns 1 if the opcode is valid, or 0 if it is invalid.
// Q2: Why is sscanf used to extract the opcode from the instruction string?

// Answer: sscanf is used because it allows us to parse the instruction string and extract the first word (the opcode). The %s format specifier reads the first sequence of non-whitespace characters until a space or newline, which corresponds to the opcode in the ALP.
// Q3: What happens if an invalid opcode is found?

// Answer: If an invalid opcode is found, the program prints an error message indicating the instruction's address and the invalid opcode. This helps in debugging and correcting errors in the ALP.
// Q4: How does the program handle multiple invalid opcodes in the ALP?

// Answer: The program will check each instruction in main_memory and print an error message for each invalid opcode it encounters. It will report errors for all invalid opcodes, not just the first one.
// Q5: What would happen if the main_memory array contained more than MAX_INSTRUCTIONS entries?

// Answer: If the main_memory array contains more than MAX_INSTRUCTIONS entries, the program would not be able to store them because the array is statically sized. To handle larger programs, dynamic memory allocation or a more flexible structure would be needed.
// Q6: What improvements could be made to this program for better error handling?

// Answer: The program could be improved by:
// Returning an error code or stopping execution after finding the first invalid opcode, if needed.
// Using dynamic memory allocation to handle an arbitrary number of instructions.
// Allowing the program to handle case-insensitive opcodes (e.g., "load" and "LOAD").
// Providing more detailed error messages, including line numbers or the complete instruction for better clarity.