// 3
// 1
// 10

#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>

int Data = 10;
int ReadCount=0;



pthread_mutex_t mutexEnter;
pthread_mutex_t mutexDb;



void* readDb(void* args)
{
    int id = *(int *)args;
    pthread_mutex_lock(&mutexEnter);
    ReadCount=ReadCount+1;
    if(ReadCount==1)
    {
        pthread_mutex_lock(&mutexDb);
    }
    pthread_mutex_unlock(&mutexEnter);
    
    pthread_mutex_lock(&mutexEnter);
    printf("\nReader %d Entering in Critical Region",id);
    ReadCount=ReadCount-1;
    if(ReadCount==0)
    {
        pthread_mutex_unlock(&mutexDb);
    }
    printf("\nReader %d reading data %d",id,Data);
    printf("\nReader %d Exiting Critical Region",id);
    pthread_mutex_unlock(&mutexEnter);
    
}

void* writeDb(void* args)
{
    int id = *(int *)args;
    int newData;
    pthread_mutex_lock(&mutexDb);
    printf("\nWriter %d Entering in Critical Region",id);
    printf("\nEnter data which you wants to update : ");
    scanf("%d",&newData);
    Data = newData;
    printf("\nWriter %d update the data to %d",id,Data);
    printf("\nWriter %d Exiting Critical Region",id);
    pthread_mutex_unlock(&mutexDb);
}




int main()
{
    // Producer Count
    int readC = 0;
    int writeC = 0;
    printf("\nEnter the number of Readers : ");
    scanf("%d",&readC);
    printf("\nEnter the number of Writers : ");
    scanf("%d",&writeC);
    int read = 0;
    int writer = 0;
    

    
    // creating threads
    pthread_t Reader[readC],Writer[writeC];
    int readId[readC];
    int writeId[writeC];
    
    // initialising semaphores
    pthread_mutex_init(&mutexEnter,NULL);
    pthread_mutex_init(&mutexDb,NULL);
    
    
    for(read;read<readC;read++)
    {
        readId[read] = read+1;
        pthread_create(&Reader[read],NULL,readDb,&readId[read]);
    }
    for(writer;writer<writeC;writer++)
    {
        writeId[writer] = writer+1;
        pthread_create(&Writer[writer],NULL,writeDb,&writeId[writer]);
        
    }
    // for(read;read<readC;read++)
    // {
    //     readId[read] = read+1;
    //     pthread_create(&Reader[read],NULL,readDb,&readId[read]);
    // }
    // for(writer;writer<writeC;writer++)
    // {
    //     writeId[writer] = writer+1;
    //     pthread_create(&Writer[writer],NULL,writeDb,&writeId[writer]);
        
    // }
    
    for(int i=0;i<readC;i++)
    {
        pthread_join(Reader[i], NULL);
    }
    for(int i=0;i<writeC;i++)
    {
        pthread_join(Writer[i], NULL);
    }
    
    return 0;
    
    
}




























// 1. Detailed Explanation of Code Logic and Line-by-Line Breakdown
// Variables and Mutex Initialization
// Global Variables:

// Data: Represents the shared data that readers read and writers modify.
// ReadCount: Keeps track of the number of active readers.
// Mutexes:

// mutexEnter: Controls access to ReadCount, ensuring only one reader modifies it at a time.
// mutexDb: Ensures exclusive access to Data, allowing either a writer or multiple readers to access the data without interference.
// Reader Function (readDb)
// Lock mutexEnter to increment ReadCount safely.
// If ReadCount is 1, this is the first reader, so it locks mutexDb to block any writers.
// Unlock mutexEnter after incrementing ReadCount.
// The reader accesses Data, printing that it is reading Data.
// Decrement ReadCount to track that the reader is done reading.
// If ReadCount is 0 after decrementing, this is the last reader, so it unlocks mutexDb, allowing writers to access Data.
// Writer Function (writeDb)
// Lock mutexDb to gain exclusive access to Data.
// Prompt the user for a new value, then update Data with this new value.
// **Unlock mutexDb** after updating, allowing readers or other writers to access Data`.
// Main Function
// Prompt for the number of readers and writers, and initialize Data.
// Create threads for each reader and writer, passing unique IDs for identification.
// Wait for all threads to finish execution using pthread_join.
// Destroy mutexes to clean up resources after execution.
// 2. Potential Questions and Answers from an External Examiner
// Explain the purpose of mutexEnter and mutexDb.

// mutexEnter controls access to ReadCount to keep reader count updates consistent.
// mutexDb ensures only one writer or multiple readers access Data simultaneously.
// Why do we use ReadCount in this code?

// ReadCount helps allow multiple readers access to Data simultaneously while blocking writers.
// What does pthread_join do in this code?

// pthread_join ensures the main function waits for all reader and writer threads to complete.
// Why does readDb use pthread_mutex_lock twice for mutexEnter?

// The first lock increments ReadCount, potentially blocking writers if it’s the first reader. The second lock decrements ReadCount, releasing mutexDb if there are no active readers.
// Why does the writer prompt for input within the critical section?

// Because the writer should access and modify Data exclusively, and taking input within the lock prevents interference from other readers or writers.
// 3. Explanation of Key Phrases
// "All threads run concurrently in a multi-threaded environment."

// Multiple reader and writer threads execute simultaneously, benefiting from parallelism to save time compared to sequential execution.
// "The writer waits until all readers finish before entering the critical section."

// The writer cannot access Data if any reader is active. It waits for ReadCount to reach 0 before locking mutexDb.
// "Threads for each reader and writer are created based on the user-specified count."

// The code dynamically creates a specified number of reader and writer threads, each of which executes in parallel.






// You said:
// also explain about what is mutex and what its use why we use and how it helps in syncronozation
// ChatGPT said:
// ChatGPT
// What is a Mutex?
// A mutex (short for "mutual exclusion") is a synchronization primitive used in multi-threaded programs to ensure that only one thread can access a shared resource at a time. It is essentially a lock that a thread must acquire before accessing a critical section (a part of the code that accesses shared resources). Only one thread can hold the mutex lock at any given time, preventing other threads from entering the critical section until the mutex is released.

// Why Use Mutex?
// When multiple threads need to access shared resources, such as variables, data structures, or files, there’s a risk of race conditions—errors that occur when threads interfere with each other while accessing shared data. Mutexes prevent race conditions by ensuring only one thread can access the critical section, which modifies the shared resource, at a time.

// Without synchronization mechanisms like mutexes, parallel threads could corrupt data by:

// Interleaved Execution: If multiple threads read or write the same data concurrently without coordination, their operations could overlap, causing inconsistent or unexpected results.
// Race Conditions: If a thread reads or modifies data while another is modifying it, the outcome depends on which thread completes its task first, leading to unpredictable behavior.
// How Does Mutex Help in Synchronization?
// Mutexes achieve thread synchronization by providing a locking mechanism with two main operations:

// Locking (pthread_mutex_lock): When a thread wants to enter a critical section, it attempts to "lock" the mutex. If another thread holds the lock, the requesting thread waits (blocks) until the mutex is unlocked.
// Unlocking (pthread_mutex_unlock): After the thread finishes its task in the critical section, it "unlocks" the mutex, allowing other threads to access the critical section.
// Example of Mutex Usage in Synchronization
// Imagine a bank application where multiple threads represent clients trying to withdraw money from the same account. Without mutexes, two clients could withdraw simultaneously, potentially leading to an overdraft. By using a mutex:

// Lock before access: Each thread locks the mutex before checking the account balance and withdrawing funds.
// Critical Section: Only one thread accesses the balance and modifies it at a time.
// Unlock after access: After modifying the balance, the thread unlocks the mutex, allowing the next waiting client to proceed.
// In the context of the Reader-Writer Problem you posted:

// Mutex mutexDb: This mutex allows either all readers or one writer to access the shared data (Data). Writers must wait until all readers are done.
// Mutex mutexEnter: This mutex ensures readers increment and decrement ReadCount safely, preventing race conditions while tracking how many readers are active.
// Summary
// Mutexes are essential for synchronizing access to shared resources in multi-threaded programs.
// They help prevent race conditions by enforcing exclusive access to the critical section.
// Proper use of mutexes ensures data integrity and consistent program behavior in concurrent programming.
