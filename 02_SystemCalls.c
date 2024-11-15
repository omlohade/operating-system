// 1
// 2
// 3
// 4
// 5
// 6
// 7

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

void fork_exit_wait();
void file_operations();
void create_link();
void create_pipe();
void create_fifo();
void get_process_ids();

int main() {
    int choice;
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Fork, Exit, Wait\n");
        printf("2. File Operations (Open, Read, Write, Close)\n");
        printf("3. Create Link and Unlink\n");
        printf("4. Pipe\n");
        printf("5. FIFO\n");
        printf("6. Get Process IDs (getpid, getppid)\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                fork_exit_wait();
                break;
            case 2:
                file_operations();
                break;
            case 3:
                create_link();
                break;
            case 4:
                create_pipe();
                break;
            case 5:
                create_fifo();
                break;
            case 6:
                get_process_ids();
                break;
            case 7:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
    return 0;
}

void fork_exit_wait() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        printf("In Child Process:\n");
        printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid());
        exit(0);
    } else {
        wait(NULL);
        printf("In Parent Process:\n");
        printf("Parent PID: %d\n", getpid());
    }
}

void file_operations() {
    int fd;
    char buffer[100];
    const char *filename = "/tmp/example.txt";
    
    // Open, Write, Close
    fd = open(filename, O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("Open failed");
        return;
    }
    write(fd, "Sample text written to file.\n", 29);
    close(fd);
    
    // Open, Read, Close
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Open failed");
        return;
    }
    read(fd, buffer, sizeof(buffer) - 1);
    printf("Read from file: %s\n", buffer);
    close(fd);
}

void create_link() {
    const char *filename = "/tmp/example.txt";
    const char *linkname = "/tmp/example_link.txt";
    
    if (link(filename, linkname) == 0) {
        printf("Link created: %s\n", linkname);
    } else {
        perror("Link creation failed");
    }
    
    if (unlink(linkname) == 0) {
        printf("Link removed: %s\n", linkname);
    } else {
        perror("Unlink failed");
    }
}

void create_pipe() {
    int pipe_fd[2];
    pid_t pid;
    char buffer[100];
    char message[] = "Message through pipe.\n";
    
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        return;
    }
    
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        close(pipe_fd[0]);
        write(pipe_fd[1], message, strlen(message) + 1);
        close(pipe_fd[1]);
        exit(0);
    } else {
        close(pipe_fd[1]);
        read(pipe_fd[0], buffer, sizeof(buffer));
        printf("Received from pipe: %s\n", buffer);
        close(pipe_fd[0]);
        wait(NULL);
    }
}

void create_fifo() {
    const char *fifo_path = "/tmp/my_fifo";
    char buffer[100];
    char message[] = "Message through FIFO.\n";
    int fd;
    
    if (mkfifo(fifo_path, 0666) == -1) {
        perror("FIFO creation failed");
        return;
    }
    printf("FIFO created at %s\n", fifo_path);
    
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        fd = open(fifo_path, O_WRONLY);
        write(fd, message, strlen(message) + 1);
        close(fd);
        exit(0);
    } else {
        fd = open(fifo_path, O_RDONLY);
        read(fd, buffer, sizeof(buffer));
        printf("Received from FIFO: %s\n", buffer);
        close(fd);
        wait(NULL);
        unlink(fifo_path);
        printf("FIFO removed\n");
    }
}

void get_process_ids() {
    printf("Current PID: %d\n", getpid());
    printf("Parent PID: %d\n", getppid());
}



// Part 1: Code Logic (Theory Part)
// The code you provided demonstrates various system calls in a menu-driven application format, allowing users to select different OS-level operations. Each option corresponds to a different system call:

// Fork, Exit, Wait:

// System calls used: fork(), exit(), wait().
// Purpose: Demonstrates process creation, termination, and synchronization. The fork() call creates a new process (child), exit() terminates it, and wait() makes the parent process wait for the child’s completion.
// File Operations:

// System calls used: open(), write(), read(), close().
// Purpose: Demonstrates basic file manipulation by opening, reading, writing, and closing a file, showing how files are handled at a system level.
// Link Creation and Unlink:

// System calls used: link(), unlink().
// Purpose: Demonstrates creating and removing hard links, showing how files can have multiple names pointing to the same data.
// Pipe:

// System call used: pipe().
// Purpose: Shows inter-process communication (IPC) via pipes, enabling data to be sent from one process to another.
// FIFO:

// System calls used: mkfifo(), unlink().
// Purpose: Uses named pipes (FIFO) for communication, illustrating a form of IPC where multiple processes can read and write.
// Process IDs:

// System calls used: getpid(), getppid().
// Purpose: Displays current and parent process IDs, giving insight into process hierarchy.
// Part 2: Line-by-Line Explanation
// main() Function
// Line: int choice;

// Declares a variable to store the user's menu choice.
// Loop Start: while (1) {

// Infinite loop to repeatedly display the menu until the user exits.
// Display Menu: printf("\nMenu:\n"); to scanf("%d", &choice);

// Prompts the user to choose an operation by entering a number.
// Switch Case: switch (choice) {

// Based on the user's choice, calls a specific function for each menu option.
// fork_exit_wait() Function
// Line: pid_t pid = fork();

// fork() creates a new process. The returned pid helps determine if it’s a parent or child process.
// Condition: if (pid < 0) {

// Checks for a fork() failure (negative pid) and exits with an error.
// Child Process: else if (pid == 0) {

// If pid is 0, this is the child process, which prints its PID and parent PID before terminating.
// Parent Process: else { wait(NULL);

// The parent waits for the child to finish and then prints its PID.
// file_operations() Function
// Opening File: fd = open(filename, O_CREAT | O_WRONLY, 0644);

// Opens or creates a file in write-only mode (O_WRONLY) with permissions 0644. If fd is negative, the operation failed.
// Writing to File: write(fd, "Sample text...");

// Writes data to the file using the file descriptor (fd).
// Reading File: fd = open(filename, O_RDONLY);

// Opens the file in read-only mode and reads its content into buffer.
// create_link() Function
// Link Creation: link(filename, linkname);

// link() creates a new hard link to the file.
// Unlinking: unlink(linkname);

// Removes the link but not the original file.
// create_pipe() Function
// Pipe Setup: pipe(pipe_fd);

// pipe_fd array has two file descriptors: pipe_fd[0] for reading, pipe_fd[1] for writing.
// Child Process: Writes to the pipe and then exits.

// Parent Process: Reads from the pipe and displays the message.

// create_fifo() Function
// FIFO Creation: mkfifo(fifo_path, 0666);

// mkfifo() creates a named pipe (FIFO) with read/write permissions.
// Child Process: Writes to the FIFO and exits.

// Parent Process: Reads from the FIFO and displays the message.


// 1. Fork, Exit, and Wait Concepts
// Q: What is a child process, and how does it differ from the parent process?

// A: A child process is created when the fork() system call is used. It is a duplicate of the parent process, sharing the same code, data, and open files initially, but with a unique process ID (PID). The child process runs independently and can execute concurrently with the parent.
// Q: What is exit() and how is it used in a program?

// A: The exit() system call terminates the current process, releasing resources it used and returning a status code. In a child process, exit() is often used to indicate completion, so the parent process can be notified, usually with wait().
// Q: How does wait() work in this code?

// A: In the parent process, wait() suspends execution until a child process completes. This is essential to ensure that resources are freed and helps synchronize parent-child process actions.
// 2. File Operations
// Q: What is the purpose of open, read, write, and close system calls?

// A: These system calls are used for file manipulation:
// open(): Opens a file and returns a file descriptor.
// write(): Writes data to a file through its file descriptor.
// read(): Reads data from a file.
// close(): Closes the file descriptor, releasing the resource.
// Q: Explain file permissions like 0644 in Unix systems.

// A: The file permission 0644 is an octal representation of access rights:
// 0 (no special permissions),
// 6 (read and write permissions for the owner),
// 4 (read-only for the group),
// 4 (read-only for others). This means the owner can read and write, while the group and others can only read.
// Q: What happens if open() fails?

// A: If open() fails, it returns -1, and an error message is printed, as the program checks for a negative return to ensure the file was opened successfully.
// 3. Link and Unlink
// Q: What are hard and symbolic links, and how do they differ?

// A: Hard links create another name for the same file data, pointing directly to the data on the disk. They share the same inode, meaning if one link is removed, others remain intact. Symbolic links (soft links), on the other hand, act as shortcuts or references to another file, not sharing the inode. If the original file is deleted, the symbolic link becomes invalid.
// Q: How does the file system handle links?

// A: When a hard link is created, the system increases the link count for the file's inode. For symbolic links, it creates a separate file that contains a reference path to the target file.
// Q: What is the purpose of unlink() in this code?

// A: unlink() removes the link name, reducing the file's link count. If it was the last link, the data is deleted from disk.
// 4. Pipe
// Q: Explain how a pipe works for inter-process communication.

// A: A pipe is a unidirectional communication channel that connects the output of one process to the input of another. It allows one process to write data into the pipe, which the other process can then read. Pipes are often used in parent-child processes due to their simplicity.
// Q: Can you explain why fork() is used with pipe()?

// A: fork() is used to create a child process that shares the pipe with the parent. After fork(), the child can write to the pipe while the parent reads from it, allowing data transfer between the two processes.
// Q: What does close() do in the context of pipes?

// A: close() releases the file descriptor associated with the pipe's read or write end. It's essential to close unused ends of a pipe in each process to avoid deadlocks or unexpected behavior.
// 5. FIFO
// Q: What is a named pipe (FIFO) and how does it differ from an unnamed pipe?

// A: A named pipe (FIFO) has a file path in the filesystem and can be accessed by multiple unrelated processes. Unlike unnamed pipes, which only exist during the lifetime of a process and its children, FIFOs persist in the filesystem until explicitly removed.
// Q: Why do we need named pipes in some cases?

// A: Named pipes are useful for communication between processes that don’t have a parent-child relationship, allowing broader inter-process communication.
// Q: What does unlink(fifo_path); do?

// A: unlink() removes the FIFO file from the filesystem, cleaning up after the FIFO communication is complete. This prevents file clutter.
// 6. Process IDs
// Q: What is getpid() used for, and why is getppid() important in process management?

// A: getpid() retrieves the unique process ID of the current process, which can be useful for debugging, logging, or referencing a specific process. getppid() gets the parent process ID, which is important for tracking process relationships, especially in managing child-parent dependencies.
// Q: How does an operating system assign process IDs?

// A: The OS assigns a unique process ID sequentially or from an available pool whenever a new process is created. The ID remains the same throughout the process's lifecycle, ensuring uniqueness and consistency.
// Q: What’s the difference between getpid() and getppid()?

// A: getpid() returns the ID of the current process, while getppid() returns the ID of the parent process, establishing the hierarchical relationship between processes.