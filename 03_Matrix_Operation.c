#include <stdio.h>
#include <pthread.h>

#define N 3
int A[N][N],B[N][N],C[N][N];

void* add_matrix(void* args) {
	int thread_id = *(int*)args;

	for(int i=thread_id; i<N; i=i+2) {
		for(int j=0; j<N; j++) {
			C[i][j] = A[i][j]+B[i][j];
		}
	}

	return NULL;
}


void* sub_matrix(void* args) {
	int thread_id = *(int*)args;

	for(int i=thread_id; i<N; i=i+2) {
		for(int j=0; j<N; j++) {
			C[i][j] = A[i][j]-B[i][j];
		}
	}

	return NULL;
}


void* mul_matrix(void* args) {
	int thread_id = *(int*)args;

	for(int i=thread_id; i<N; i=i+2) {
		for(int j=0; j<N; j++) {
			C[i][j] = A[i][j]*B[i][j];
		}
	}

	return NULL;
}

void printMatrix(int C[N][N]) {
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			printf("%d ",C[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main()
{
	// Setting the values of the array.
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			A[i][j] = i+j;
			B[i][j] = i-j;
		}
	}

	// Print array A
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			printf("%d ",A[i][j]);
		}
		printf("\n");
	}

	printf("\n");

	// Print array B
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			printf("%d ",B[i][j]);
		}
		printf("\n");
	}
	
	printf("\n");

	pthread_t threads[2]; // We have used the same threads for all the operations.
	int thread_id[2] = {0,1};

    // Addition
	for(int i=0; i<N; i++) {
		pthread_create(&threads[i],NULL,add_matrix,&thread_id[i]);
	}

	for(int i=0; i<N; i++) {
		pthread_join(threads[i],NULL);
	}
	
	printf("Matrix Addition: \n");
	printMatrix(C);

    //Subtraction
	for(int i=0; i<N; i++) {
		pthread_create(&threads[i],NULL,sub_matrix,&thread_id[i]);
	}

	for(int i=0; i<N; i++) {
		pthread_join(threads[i],NULL);
	}
	printf("Matrix Substraction: \n");
	printMatrix(C);

    // Multiplication
    
	for(int i=0; i<N; i++) {
		pthread_create(&threads[i],NULL,mul_matrix,&thread_id[i]);
	}

	for(int i=0; i<N; i++) {
		pthread_join(threads[i],NULL);
	}
	printf("Matrix Multiplication: \n");
	printMatrix(C);




	return 0;
}




// This C program performs matrix operations (addition, subtraction, and multiplication) on two matrices A and B and stores the results in a matrix C using multithreading. Each matrix operation is handled by separate functions that utilize threads to parallelize the computations.

// Key Points
// Matrix Initialization:

// Matrices A and B are populated with values based on their indices.
// A[i][j] = i + j and B[i][j] = i - j.
// Multithreading:

// Threads are created to perform operations on parts of the matrices.
// For each operation (addition, subtraction, multiplication), two threads are used, each processing every other row based on the thread's ID (0 or 1).
// Operations Functions:

// Addition: add_matrix adds corresponding elements from A and B and stores the result in C.
// Subtraction: sub_matrix subtracts elements in B from A and stores the result in C.
// Multiplication: mul_matrix performs element-wise multiplication between A and B and stores the result in C.
// Matrix Printing:

// The printMatrix function displays the matrix C.
// Main Function:

// Initializes matrices A and B.
// Uses two threads to perform addition, subtraction, and multiplication, printing the result of each operation.
// Line-by-Line Explanation
// c
// Copy code
// #include <stdio.h>
// #include <pthread.h>
// #define N 3
// int A[N][N], B[N][N], C[N][N];
// Includes libraries for input/output and threading. Defines matrix size N=3 and initializes matrices A, B, and C.
// add_matrix, sub_matrix, and mul_matrix Functions
// c
// Copy code
// void* add_matrix(void* args) {
//     int thread_id = *(int*)args;
//     for(int i=thread_id; i<N; i=i+2) {
//         for(int j=0; j<N; j++) {
//             C[i][j] = A[i][j] + B[i][j];
//         }
//     }
//     return NULL;
// }
// Each function receives a thread_id and processes rows based on this ID (e.g., thread 0 processes even rows, and thread 1 processes odd rows). In each function:
// add_matrix computes element-wise addition.
// sub_matrix computes element-wise subtraction.
// mul_matrix computes element-wise multiplication.
// printMatrix Function
// c
// Copy code
// void printMatrix(int C[N][N]) {
//     for(int i=0; i<N; i++) {
//         for(int j=0; j<N; j++) {
//             printf("%d ", C[i][j]);
//         }
//         printf("\n");
//     }
//     printf("\n");
// }
// Loops through each element of matrix C and prints it in a matrix format.
// Main Function
// c
// Copy code
// int main() {
//     // Setting values for A and B
//     for(int i=0; i<N; i++) {
//         for(int j=0; j<N; j++) {
//             A[i][j] = i + j;
//             B[i][j] = i - j;
//         }
//     }
//     // Print matrices A and B
// Initializes matrices A and B with values based on their indices, then prints them.
// c
// Copy code
//     pthread_t threads[2];
//     int thread_id[2] = {0, 1};
// Defines two threads and thread IDs to control their processing rows based on ID.
// c
// Copy code
//     // Addition
//     for(int i=0; i<N; i++) {
//         pthread_create(&threads[i], NULL, add_matrix, &thread_id[i]);
//     }
//     for(int i=0; i<N; i++) {
//         pthread_join(threads[i], NULL);
//     }
//     printf("Matrix Addition: \n");
//     printMatrix(C);
// Creates threads for addition, waits for their completion using pthread_join, and prints the result matrix.
// c
// Copy code
//     // Subtraction
//     for(int i=0; i<N; i++) {
//         pthread_create(&threads[i], NULL, sub_matrix, &thread_id[i]);
//     }
//     for(int i=0; i<N; i++) {
//         pthread_join(threads[i], NULL);
//     }
//     printf("Matrix Subtraction: \n");
//     printMatrix(C);
// Creates threads for subtraction, waits for their completion, and prints the result matrix.
// c
// Copy code
//     // Multiplication
//     for(int i=0; i<N; i++) {
//         pthread_create(&threads[i], NULL, mul_matrix, &thread_id[i]);
//     }
//     for(int i=0; i<N; i++) {
//         pthread_join(threads[i], NULL);
//     }
//     printf("Matrix Multiplication: \n");
//     printMatrix(C);

//     return 0;
// }
// Creates threads for multiplication, waits for their completion, and prints the result matrix.
// Possible Questions and Answers
// Q: How does the pthread_create function work in this program?

// A: pthread_create initializes a new thread that runs the specified matrix operation function (add_matrix, sub_matrix, or mul_matrix), passing the thread ID as an argument.
// Q: Why is pthread_join used after creating threads?

// A: pthread_join ensures that the main thread waits for the completion of the spawned threads before proceeding, so the result matrix is printed only after all threads finish their computation.
// Q: What is the significance of thread_id[i] in this code?

// A: thread_id[i] determines the starting row for each thread, allowing alternate rows to be processed by each thread in the matrix functions.
// Q: What would happen if we didn’t use pthread_join?

// A: Without pthread_join, the main function could complete and print the results before all threads finish their operations, leading to incomplete or incorrect output.
// Q: Why is void* used as the return type for the matrix functions?

// A: The return type void* is required for compatibility with pthread_create and does not return any actual data as the operations directly modify the global matrix C.





// You said:
// how is code taking input for matrix from user or predifiened and if pridefined can we take input from user if yes give updated code 

// what is difference between threads and fork 

// what does this mean
// Creates threads for addition, waits for their completion using pthread_join, and prints the result matrix

// wait for completion means which completion

// 2/2

// ChatGPT said:
// ChatGPT
// Memory updated
// 1. How the Code Takes Matrix Input and Modification for User Input
// In the code provided, the matrices 
// 𝐴
// A and 
// 𝐵
// B are predefined with values set in a loop based on index calculations:

// c
// Copy code
// A[i][j] = i + j;
// B[i][j] = i - j;
// To allow users to input values for matrices 
// 𝐴
// A and 
// 𝐵
// B, we can modify the code to use scanf within a loop to read each matrix element. Here’s the updated code to accept user input for the matrices:

// c
// Copy code
// #include <stdio.h>
// #include <pthread.h>

// #define N 3
// int A[N][N], B[N][N], C[N][N];

// void* add_matrix(void* args) {
//     int thread_id = *(int*)args;
//     for (int i = thread_id; i < N; i = i + 2) {
//         for (int j = 0; j < N; j++) {
//             C[i][j] = A[i][j] + B[i][j];
//         }
//     }
//     return NULL;
// }

// void* sub_matrix(void* args) {
//     int thread_id = *(int*)args;
//     for (int i = thread_id; i < N; i = i + 2) {
//         for (int j = 0; j < N; j++) {
//             C[i][j] = A[i][j] - B[i][j];
//         }
//     }
//     return NULL;
// }

// void* mul_matrix(void* args) {
//     int thread_id = *(int*)args;
//     for (int i = thread_id; i < N; i = i + 2) {
//         for (int j = 0; j < N; j++) {
//             C[i][j] = A[i][j] * B[i][j];
//         }
//     }
//     return NULL;
// }

// void printMatrix(int C[N][N]) {
//     for (int i = 0; i < N; i++) {
//         for (int j = 0; j < N; j++) {
//             printf("%d ", C[i][j]);
//         }
//         printf("\n");
//     }
//     printf("\n");
// }

// int main() {
//     // Taking input for matrix A
//     printf("Enter elements for matrix A:\n");
//     for (int i = 0; i < N; i++) {
//         for (int j = 0; j < N; j++) {
//             scanf("%d", &A[i][j]);
//         }
//     }

//     // Taking input for matrix B
//     printf("Enter elements for matrix B:\n");
//     for (int i = 0; i < N; i++) {
//         for (int j = 0; j < N; j++) {
//             scanf("%d", &B[i][j]);
//         }
//     }

//     pthread_t threads[2];
//     int thread_id[2] = {0, 1};

//     // Matrix Addition
//     for (int i = 0; i < 2; i++) {
//         pthread_create(&threads[i], NULL, add_matrix, &thread_id[i]);
//     }
//     for (int i = 0; i < 2; i++) {
//         pthread_join(threads[i], NULL);
//     }
//     printf("Matrix Addition:\n");
//     printMatrix(C);

//     // Matrix Subtraction
//     for (int i = 0; i < 2; i++) {
//         pthread_create(&threads[i], NULL, sub_matrix, &thread_id[i]);
//     }
//     for (int i = 0; i < 2; i++) {
//         pthread_join(threads[i], NULL);
//     }
//     printf("Matrix Subtraction:\n");
//     printMatrix(C);

//     // Matrix Multiplication
//     for (int i = 0; i < 2; i++) {
//         pthread_create(&threads[i], NULL, mul_matrix, &thread_id[i]);
//     }
//     for (int i = 0; i < 2; i++) {
//         pthread_join(threads[i], NULL);
//     }
//     printf("Matrix Multiplication:\n");
//     printMatrix(C);

//     return 0;
// }
// 2. Difference Between Threads and Fork
// Threads share the same memory space within a process, allowing them to access the same global variables and arrays without the need for inter-process communication. They are lightweight and execute concurrently within the same process.
// Forks, on the other hand, create a new process that is a child of the original process, duplicating the entire memory space. This is more resource-intensive, as each process has its own memory space, and inter-process communication is required for data exchange.
// 3. Explanation of pthread_join and Waiting for Completion
// The statement, "Creates threads for addition, waits for their completion using pthread_join, and prints the result matrix," means that after each thread (for matrix addition, subtraction, or multiplication) is created, the program waits until each thread completes its task before proceeding. pthread_join is used to block the main program from moving forward until each thread finishes executing the function it’s assigned. Completion here refers to the threads finishing their matrix operations. This ensures that the result matrix is fully calculated before being printed.






// You said:
// do all threads run simultaneously if yes is it for saving time but you said that it waits for execution and then only procced than how it is time saving
// ChatGPT said:
// ChatGPT
// Yes, the threads in this code run concurrently, meaning they are scheduled to execute in overlapping time intervals. While they do not always run truly simultaneously (depending on the CPU core availability and scheduling), they often appear to do so because they share processing time efficiently across the CPU. Here's how it works in this code and why it can save time:

// Concurrent Execution: When threads are created, they can work on separate portions of the matrix at the same time. Here, each thread processes alternate rows of the matrix, distributing the workload. This allows each thread to execute without waiting for the other to complete its assigned rows.

// pthread_join Waiting Mechanism: pthread_join is only called after all threads are created, meaning the main program waits until each thread completes its work, but this does not affect the threads' individual execution times. Instead, it ensures that no further operations on the result matrix occur until all threads have completed their assigned tasks.

// Time Savings Through Parallelism: Even though pthread_join waits, the primary time-saving comes from dividing the workload. In single-threaded code, each row would be processed sequentially. By using threads, two rows can be computed at the same time, reducing the total computation time by half in ideal conditions (assuming two cores or a dual-core CPU).

// Why Does Waiting Still Save Time?
// By creating threads, the code effectively reduces the overall workload time despite waiting for each thread to complete. Here’s a breakdown:

// Without threads, the program would complete matrix addition, subtraction, and multiplication row-by-row in sequence.
// With threads, two rows are processed in parallel, reducing the time required for each operation by half (assuming two threads are used and run on a multi-core CPU).
// In summary, the use of threads allows parts of the work to be done concurrently, speeding up the overall computation time. pthread_join does not diminish this benefit; it only synchronizes the end of the operation so that the result matrix is complete and correct before it is printed.






// You said:
// With threads, two rows are processed in parallel,

// means if 2 rows of matrix are processed differently then how will it do calculation because both will be different then
// ChatGPT said:
// ChatGPT
// You're right to notice that when using threads to process different rows of a matrix, there's a potential challenge in coordinating how each thread calculates its assigned portion without interfering with others. In this code, the parallelism works because each thread independently processes the same rows in both matrices 
// 𝐴
// A and 
// 𝐵
// B, and stores the results in matrix 
// 𝐶
// C without needing to rely on data from other rows. Here’s a breakdown of why this method is consistent and why it works:

// Understanding Row-wise Parallelism in Matrix Operations
// For matrix addition, subtraction, and element-wise multiplication (as in this code):

// Each element in the resulting matrix 
// 𝐶
// C is calculated only based on the corresponding elements in 
// 𝐴
// A and 
// 𝐵
// B.
// The rows processed by different threads don’t depend on each other. So, processing different rows separately in parallel will not lead to inconsistencies.
// In other words:

// Addition: 
// 𝐶
// [
// 𝑖
// ]
// [
// 𝑗
// ]
// =
// 𝐴
// [
// 𝑖
// ]
// [
// 𝑗
// ]
// +
// 𝐵
// [
// 𝑖
// ]
// [
// 𝑗
// ]
// C[i][j]=A[i][j]+B[i][j]
// Subtraction: 
// 𝐶
// [
// 𝑖
// ]
// [
// 𝑗
// ]
// =
// 𝐴
// [
// 𝑖
// ]
// [
// 𝑗
// ]
// −
// 𝐵
// [
// 𝑖
// ]
// [
// 𝑗
// ]
// C[i][j]=A[i][j]−B[i][j]
// Element-wise Multiplication: 
// 𝐶
// [
// 𝑖
// ]
// [
// 𝑗
// ]
// =
// 𝐴
// [
// 𝑖
// ]
// [
// 𝑗
// ]
// ×
// 𝐵
// [
// 𝑖
// ]
// [
// 𝑗
// ]
// C[i][j]=A[i][j]×B[i][j]
// Since each thread only needs data from its assigned rows in 
// 𝐴
// A and 
// 𝐵
// B to calculate the corresponding rows in 
// 𝐶
// C, there’s no overlap or dependency across threads. Each thread completes its work on assigned rows without affecting the work of the other thread.

// Why This Works Without Interference
// Data Independence: Each thread works on its own row, so it does not alter or depend on rows assigned to other threads.
// Thread Safety: There’s no shared data between threads, aside from each writing results to non-overlapping rows in 
// 𝐶
// C. This means each thread’s write operations are isolated, preventing conflicts.
// Illustration of the Parallel Execution
// If we have two threads:

// Thread 0 processes rows 0, 2.
// Thread 1 processes row 1.
// Each thread completes its calculations for its assigned rows and writes directly to those rows in 
// 𝐶
// C without affecting any other rows.

// Why This Technique Saves Time
// This approach divides the workload among the threads, which can reduce the computation time, especially in a large matrix:

// Instead of waiting to complete row 0 before starting on row 1 and so forth, threads can process multiple rows simultaneously.
// With a multi-core processor, the threads can indeed execute simultaneously, maximizing CPU usage and improving performance.
// In summary, the code design ensures that each thread independently calculates and writes only to the rows it is responsible for, allowing parallel execution to speed up the process without risking inconsistencies.