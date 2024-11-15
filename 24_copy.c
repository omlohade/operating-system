#include <stdio.h>
#include <stdlib.h>


void copyFileCharacterByCharacter(const char *sourceFile, const char *destFile) {
    FILE *src = fopen(sourceFile, "r");
    FILE *dest = fopen(destFile, "w");
    if (src == NULL || dest == NULL) {
        perror("Error opening file");
        exit(1);
    }
    char ch;
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }
    printf("File copied character by character successfully.\n");
    fclose(src);
    fclose(dest);
}


void copyFileLineByLine(const char *sourceFile, const char *destFile) {
    FILE *src = fopen(sourceFile, "r");
    FILE *dest = fopen(destFile, "w");
    if (src == NULL || dest == NULL) {
        perror("Error opening file");
        exit(1);
    }
    char line[1024];
    while (fgets(line, sizeof(line), src) != NULL) {
        fputs(line, dest);
    }
    printf("File copied line by line successfully.\n");
    fclose(src);
    fclose(dest);
}


int main() {
    char sourceFile[100];
    char destFileChar[100];
    char destFileLine[100];


    printf("Enter the name of the source file: ");
    scanf("%s", sourceFile);


    printf("Enter the name of the destination file for character-by-character copy: ");
    scanf("%s", destFileChar);


    printf("Enter the name of the destination file for line-by-line copy: ");
    scanf("%s", destFileLine);
    printf("\nCopying file character by character...\n");
    copyFileCharacterByCharacter(sourceFile, destFileChar);
    printf("\nCopying file line by line...\n");
    copyFileLineByLine(sourceFile, destFileLine);
    return 0;
}




















// 1. Concept, Uses, and Purpose
// Concept: This program demonstrates two ways of copying data from one file to another in C: character-by-character and line-by-line. It shows how to use standard file handling functions (fopen, fgetc, fputc, fgets, and fputs) to work with files in different ways.

// Uses: File handling operations like these are fundamental for creating backups, transferring data, and manipulating files in systems programming. Character-by-character copying can be useful for finer control when processing data, while line-by-line copying is more efficient for larger text-based data.

// Purpose: The code demonstrates a practical application of file handling in C by implementing two different methods of copying data, allowing users to see the differences in handling data at varying levels of granularity.

// 2. Logic and Algorithm
// Character-by-Character Copy:

// Open the source and destination files.
// Check if files opened successfully. If not, print an error and exit.
// Read each character from the source file until the end of the file (EOF) is reached.
// Write each character read to the destination file.
// Close both files.
// Line-by-Line Copy:

// Open the source and destination files.
// Check if files opened successfully. If not, print an error and exit.
// Read each line from the source file into a buffer until the end of the file.
// Write each line to the destination file.
// Close both files.
// Both methods start by reading the source file and writing to a specified destination file. Error handling is implemented to ensure the files open correctly, and success messages indicate completion.

// 3. Line-by-Line Code Explanation
// c
// Copy code
// #include <stdio.h>
// #include <stdlib.h>

// // Function to copy file character by character
// void copyFileCharacterByCharacter(const char *sourceFile, const char *destFile) {
//     FILE *src = fopen(sourceFile, "r");    // Open source file in read mode
//     FILE *dest = fopen(destFile, "w");     // Open destination file in write mode
//     if (src == NULL || dest == NULL) {     // Check if either file failed to open
//         perror("Error opening file");      // Print error if file fails to open
//         exit(1);                           // Exit the program with an error code
//     }
//     char ch;                               // Variable to store each character
//     while ((ch = fgetc(src)) != EOF) {     // Read character by character until EOF
//         fputc(ch, dest);                   // Write each character to the destination file
//     }
//     printf("File copied character by character successfully.\n");
//     fclose(src);                           // Close the source file
//     fclose(dest);                          // Close the destination file
// }

// // Function to copy file line by line
// void copyFileLineByLine(const char *sourceFile, const char *destFile) {
//     FILE *src = fopen(sourceFile, "r");    // Open source file in read mode
//     FILE *dest = fopen(destFile, "w");     // Open destination file in write mode
//     if (src == NULL || dest == NULL) {     // Check if either file failed to open
//         perror("Error opening file");      // Print error if file fails to open
//         exit(1);                           // Exit the program with an error code
//     }
//     char line[1024];                       // Buffer to store each line
//     while (fgets(line, sizeof(line), src) != NULL) {  // Read each line into buffer
//         fputs(line, dest);                 // Write each line to the destination file
//     }
//     printf("File copied line by line successfully.\n");
//     fclose(src);                           // Close the source file
//     fclose(dest);                          // Close the destination file
// }

// // Main function to handle user input and call copy functions
// int main() {
//     char sourceFile[100];                  // Variable to store source file name
//     char destFileChar[100];                // Variable to store destination file name for character copy
//     char destFileLine[100];                // Variable to store destination file name for line copy

//     printf("Enter the name of the source file: ");
//     scanf("%s", sourceFile);               // Get source file name from user

//     printf("Enter the name of the destination file for character-by-character copy: ");
//     scanf("%s", destFileChar);             // Get destination file name for character copy

//     printf("Enter the name of the destination file for line-by-line copy: ");
//     scanf("%s", destFileLine);             // Get destination file name for line copy

//     printf("\nCopying file character by character...\n");
//     copyFileCharacterByCharacter(sourceFile, destFileChar);   // Call function to copy character-by-character

//     printf("\nCopying file line by line...\n");
//     copyFileLineByLine(sourceFile, destFileLine);             // Call function to copy line-by-line

//     return 0;                           // Exit the program successfully
// }
// 4. Potential External Examiner Questions and Answers
// What is the purpose of fgetc and fputc?

// fgetc reads a single character from a file, and fputc writes a single character to a file. They are useful for character-by-character file processing.
// How does fgets differ from fgetc?

// fgets reads an entire line of text into a buffer until a newline or end of file is reached, making it suitable for line-by-line file operations, while fgetc reads one character at a time.
// Why is perror used in the code?

// perror prints a system-generated error message based on the last error that occurred, helping in debugging file access issues.
// What happens if the source file doesn’t exist?

// If the source file doesn’t exist, the program will print an error message ("Error opening file") and terminate because of the exit(1); call.
// How would you modify this code to check if the file copy was successful?

// We can check the return value of each fgetc and fgets call. If any return value is unexpected (like a read failure), we could add additional error handling to report partial or unsuccessful copies.
// Is it possible to copy binary files with this program?

// This program is designed for text files because it uses line-based reading for one of the copy methods. To copy binary files, both source and destination files should be opened in binary mode ("rb" and "wb"), and line-based copying would be replaced with byte-based copying.


// Here’s the line-by-line code explanation for the file copying program you provided:

// c
// Copy code
// #include <stdio.h>
// #include <stdlib.h>
// These are the header files. stdio.h provides standard input/output functions, and stdlib.h provides functions for memory allocation, process control, and conversions.
// c
// Copy code
// void copyFileCharacterByCharacter(const char *sourceFile, const char *destFile) {
// Defines a function named copyFileCharacterByCharacter that takes two arguments, sourceFile and destFile, which are strings representing the names of the source and destination files.
// c
// Copy code
//     FILE *src = fopen(sourceFile, "r");
//     FILE *dest = fopen(destFile, "w");
// Opens the source file in read mode ("r") and the destination file in write mode ("w"). src and dest are file pointers that point to the source and destination files, respectively.
// c
// Copy code
//     if (src == NULL || dest == NULL) {
//         perror("Error opening file");
//         exit(1);
//     }
// Checks if either file failed to open (indicated by NULL). If so, perror prints an error message, and exit(1); terminates the program with an error code of 1.
// c
// Copy code
//     char ch;
//     while ((ch = fgetc(src)) != EOF) {
//         fputc(ch, dest);
//     }
// Declares a character variable ch. The while loop reads one character at a time from the source file using fgetc(src), which returns EOF when the end of the file is reached. Each character is then written to the destination file using fputc(ch, dest);.
// c
// Copy code
//     printf("File copied character by character successfully.\n");
//     fclose(src);
//     fclose(dest);
// }
// Prints a success message, then closes both the source and destination files using fclose.
// c
// Copy code
// void copyFileLineByLine(const char *sourceFile, const char *destFile) {
// Defines a function named copyFileLineByLine that takes sourceFile and destFile as arguments for the source and destination file names.
// c
// Copy code
//     FILE *src = fopen(sourceFile, "r");
//     FILE *dest = fopen(destFile, "w");
// Opens the source file in read mode and the destination file in write mode, as before.
// c
// Copy code
//     if (src == NULL || dest == NULL) {
//         perror("Error opening file");
//         exit(1);
//     }
// Checks if either file failed to open and exits with an error if necessary.
// c
// Copy code
//     char line[1024];
// Declares a character array line of size 1024 to store each line read from the file.
// c
// Copy code
//     while (fgets(line, sizeof(line), src) != NULL) {
//         fputs(line, dest);
//     }
// Uses fgets to read a line from src into the line array, up to 1024 characters or until a newline is found. fputs then writes this line to dest. The loop continues until fgets returns NULL, indicating the end of the file.
// c
// Copy code
//     printf("File copied line by line successfully.\n");
//     fclose(src);
//     fclose(dest);
// }
// Prints a success message and closes both files.
// c
// Copy code
// int main() {
//     char sourceFile[100];
//     char destFileChar[100];
//     char destFileLine[100];
// Declares three character arrays (sourceFile, destFileChar, destFileLine), each with a size of 100, to store the filenames for the source file and the two destination files.
// c
// Copy code
//     printf("Enter the name of the source file: ");
//     scanf("%s", sourceFile);
// Prompts the user to enter the name of the source file and stores it in sourceFile.
// c
// Copy code
//     printf("Enter the name of the destination file for character-by-character copy: ");
//     scanf("%s", destFileChar);
// Prompts the user for the name of the destination file for the character-by-character copy, storing the input in destFileChar.
// c
// Copy code
//     printf("Enter the name of the destination file for line-by-line copy: ");
//     scanf("%s", destFileLine);
// Prompts the user for the name of the destination file for the line-by-line copy, storing the input in destFileLine.
// c
// Copy code
//     printf("\nCopying file character by character...\n");
//     copyFileCharacterByCharacter(sourceFile, destFileChar);
// Prints a message indicating the start of the character-by-character copy. Calls the copyFileCharacterByCharacter function with sourceFile and destFileChar as arguments to perform this copy.
// c
// Copy code
//     printf("\nCopying file line by line...\n");
//     copyFileLineByLine(sourceFile, destFileLine);
// Prints a message indicating the start of the line-by-line copy. Calls the copyFileLineByLine function with sourceFile and destFileLine as arguments to perform this copy.
// c
// Copy code
//     return 0;
// }
// Returns 0 from main, indicating successful program completion.