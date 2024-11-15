#include <stdio.h>
#include <string.h>


#define MAX_INSTRUCTIONS 100
#define MAX_LINE_LENGTH 50


void check_operand_errors(char main_memory[][MAX_LINE_LENGTH], int instruction_count) {
    for (int i = 0; i < instruction_count; i++) {
        int operand_count = 0;
        char *token = strtok(main_memory[i], " ,");
        // Count tokens after the opcode as operands
        while (token != NULL) {
            operand_count++;
            token = strtok(NULL, " ,");
        }
       
        if (operand_count < 3) { // Opcode + 2 operands
            printf("Operand error at address %d: Missing operand(s) in instruction '%s'\n", i, main_memory[i]);
        }
    }
}


int main() {
    char main_memory[MAX_INSTRUCTIONS][MAX_LINE_LENGTH] = {
        "LOAD R1, 100",
        "STORE R2", // Missing operand for testing
        "ADD R1, R2",
        "SUB R3" // Missing operand for testing
    };
    int instruction_count = 4;
    check_operand_errors(main_memory, instruction_count);
    return 0;
}





























// 1. Concept, Uses, and Why We Use It
// Concept:
// This program is designed to check for operand errors in a series of ALP (Assembly-like Programming) instructions. The program verifies if each instruction contains at least two operands, which are required after the opcode. It counts the number of operands in each instruction and flags errors if any instruction is missing operands.

// Uses:

// This type of program is useful in emulators or assemblers where an assembly-like language program is validated before execution.
// It helps in teaching or debugging low-level programming by ensuring that instructions are properly formed with the required operands.
// Why We Use It:

// To ensure that the instructions in the ALP are valid with respect to their operands. Missing operands in instructions can lead to runtime errors or incorrect program behavior, so it is crucial to catch these errors before execution.
// The program simplifies debugging by identifying and reporting missing operands early, making it easier for developers to fix issues in the ALP.
// 2. Logic and Algorithm
// Logic:

// The program iterates over each instruction stored in main_memory, and for each instruction, it checks if it contains enough operands.
// The instruction is split into tokens using strtok. The tokens are delimited by spaces and commas.
// The program counts how many tokens appear after the opcode (which is the first token) and checks if the count is at least two. If not, it prints an error message indicating the missing operand(s).
// Algorithm:

// Define the main_memory array to store ALP instructions.
// Iterate over each instruction in main_memory.
// For each instruction:
// Tokenize the string using strtok, which breaks the instruction into individual parts (opcode and operands).
// Count the number of tokens. If the number of tokens after the opcode is less than 3 (opcode + 2 operands), print an error message.
// The program stops after checking all instructions.
// 3. Line-by-Line Code Explanation
// c
// Copy code
// #include <stdio.h>
// #include <string.h>
// stdio.h: Provides standard input and output functions like printf and scanf, which are used for printing messages and reading input.
// string.h: Provides functions for manipulating strings, such as strtok, which is used to split a string into tokens based on delimiters.
// c
// Copy code
// #define MAX_INSTRUCTIONS 100
// #define MAX_LINE_LENGTH 50
// MAX_INSTRUCTIONS: Defines the maximum number of instructions that can be stored in memory.
// MAX_LINE_LENGTH: Defines the maximum length of a single instruction string.
// c
// Copy code
// void check_operand_errors(char main_memory[][MAX_LINE_LENGTH], int instruction_count) {
// check_operand_errors: This function is responsible for checking the operand errors. It takes two arguments:
// main_memory: A 2D array containing the ALP instructions.
// instruction_count: The total number of instructions to check.
// c
// Copy code
//     for (int i = 0; i < instruction_count; i++) {
// A for loop that iterates over each instruction in main_memory. The variable i represents the current instruction's address.
// c
// Copy code
//         int operand_count = 0;
//         char *token = strtok(main_memory[i], " ,");
// operand_count: A variable to keep track of how many operands are present in the current instruction.
// strtok(main_memory[i], " ,"): The strtok function is used to split the current instruction (main_memory[i]) into tokens. The instruction is split based on spaces and commas, which are the delimiters for operands and the opcode.
// c
// Copy code
//         while (token != NULL) {
//             operand_count++;
//             token = strtok(NULL, " ,");
//         }
// The while loop continues tokenizing the instruction until there are no more tokens (i.e., until token becomes NULL).
// operand_count++: For each token found, the operand count is incremented.
// token = strtok(NULL, " ,"): This continues extracting the next token from the instruction until there are no more tokens.
// c
// Copy code
//         if (operand_count < 3) { // Opcode + 2 operands
//             printf("Operand error at address %d: Missing operand(s) in instruction '%s'\n", i, main_memory[i]);
//         }
// After counting the tokens, the program checks if the operand_count is less than 3 (because each instruction must have at least one opcode and two operands).
// If there are fewer than 3 tokens, it indicates a missing operand(s), and the program prints an error message with the instruction's address and the instruction itself.
// c
// Copy code
//     }
// }
// The closing brace for the for loop, which processes all instructions.
// c
// Copy code
// int main() {
//     char main_memory[MAX_INSTRUCTIONS][MAX_LINE_LENGTH] = {
//         "LOAD R1, 100",
//         "STORE R2", // Missing operand for testing
//         "ADD R1, R2",
//         "SUB R3" // Missing operand for testing
//     };
//     int instruction_count = 4;
//     check_operand_errors(main_memory, instruction_count);
//     return 0;
// }
// In main(), the main_memory array is initialized with some example instructions. Two of these instructions ("STORE R2" and "SUB R3") have missing operands for testing purposes.
// instruction_count is set to 4, which is the number of instructions in main_memory.
// The check_operand_errors function is called to check for operand errors in the instructions.
// 4. Possible Questions and Answers
// Q1: What is the role of the strtok function in this program?

// Answer: The strtok function is used to split the instruction string into tokens (parts) based on delimiters such as spaces and commas. This allows us to separate the opcode from the operands and count the operands.
// Q2: How does the program determine if an instruction has missing operands?

// Answer: The program counts the number of tokens in each instruction. If the number of tokens is less than 3 (i.e., the opcode plus at least two operands), the program reports an error indicating that operands are missing.
// Q3: What happens if there are extra operands in an instruction?

// Answer: The program currently does not handle extra operands explicitly. It only checks if there are fewer than 3 tokens. If there are more than two operands, the program will not flag an error, and it will process the instruction as valid.
// Q4: How can this program be improved to handle instructions with more than two operands?

// Answer: The program could be extended to check for a specific number of operands based on the opcode. For example, certain opcodes might require a different number of operands (e.g., ADD might need two registers, while LOAD might need a register and a value). This could involve parsing the instruction and checking the number of operands based on the opcode.
// Q5: Why do we check for operand_count < 3 instead of a different number?

// Answer: We check for operand_count < 3 because, in this program, we assume that each valid instruction should have one opcode and at least two operands (e.g., "LOAD R1, 100" has 3 tokens: "LOAD", "R1", "100"). The assumption is that a valid instruction should not have fewer than three tokens.
// Q6: What other kinds of errors could be detected in ALP instructions?

// Answer: In addition to missing operands, other errors could include:
// Invalid opcodes (e.g., using an undefined opcode).
// Invalid syntax, such as improper use of commas or spaces.
// Incorrect number of operands based on the opcode (e.g., a STORE operation requiring a register and a memory address).

