#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

int Data = 10;
int ReadCount = 0;

sem_t enter, db;

void *readDb(void *args)
{
    int id = *(int *)args;
    sem_wait(&enter);
    ReadCount = ReadCount + 1;
    if (ReadCount == 1)
    {
        sem_wait(&db);
    }
    sem_post(&enter);
    printf("\nReader %d Entering in Critical Region", id);
    printf("\nReader %d reading data %d", id, Data);
    printf("\nReader %d Exiting from Critical Region", id);
    sem_wait(&enter);
    ReadCount = ReadCount - 1;
    if (ReadCount == 0)
    {
        sem_post(&db);
    }
    sem_post(&enter);
}

void *writeDb(void *args)
{
    int id = *(int *)args;
    int newData;
    sem_wait(&db);
    printf("\nWriter %d Entering in Critical Region", id);
    printf("\nEnter data which you wants to update : ");
    scanf("%d", &newData);
    Data = newData;
    printf("\nWriter %d update the data to %d", id, Data);
    printf("\nWriter %d Exiting from Critical Region", id);
    sem_post(&db);
}

int main()
{
    // Producer Count
    int readC = 0;
    int writeC = 0;
    printf("\nEnter the number of Readers : ");
    scanf("%d", &readC);
    printf("\nEnter the number of Writers : ");
    scanf("%d", &writeC);
    int read = 0;
    int writer = 0;

    // creating threads
    pthread_t Reader[readC], Writer[writeC];
    int readId[readC];
    int writeId[writeC];

    // initialising semaphores
    sem_init(&enter, 0, 1);
    sem_init(&db, 0, 1);

    for (read; read < readC; read++)
    {
        readId[read] = read + 1;
        pthread_create(&Reader[read], NULL, readDb, &readId[read]);
    }
    for (writer; writer < writeC; writer++)
    {
        writeId[writer] = writer + 1;
        pthread_create(&Writer[writer], NULL, writeDb, &writeId[writer]);
    }

    for (int i = 0; i < readC; i++)
    {
        pthread_join(Reader[i], NULL);
    }
    for (int i = 0; i < writeC; i++)
    {
        pthread_join(Writer[i], NULL);
    }

    return 0;
}



















// 1. Concept Explanation:
// The given code implements a reader-writer problem using semaphores to manage access to a shared resource (Data). The problem involves multiple readers and writers where:

// Readers can read the data concurrently as long as no writer is writing.
// Writers require exclusive access to the data and can modify it only when no readers are reading.
// In the code:

// Readers increase the ReadCount when they enter the critical section and decrease it when they exit. The first reader locks the database to ensure no writers are writing.
// Writers lock the database (using db semaphore) to ensure they have exclusive access to the resource.
// The semaphores used here are:

// enter: This semaphore ensures mutual exclusion for the ReadCount variable. Only one reader can modify the ReadCount at a time.
// db: This semaphore controls access to the database, ensuring only one writer or no readers and writers can access the data at any given time.
// 2. Code Walkthrough (Step-by-Step Explanation):
// readDb Function:
// Purpose: Reads the shared Data after ensuring safe access for multiple readers.
// Steps:
// sem_wait(&enter): Locks the enter semaphore to ensure mutual exclusion while updating ReadCount.
// Increment ReadCount: Increments the count of active readers.
// First Reader Logic: If this is the first reader (ReadCount == 1), it waits for the db semaphore, locking the database to prevent writers.
// sem_post(&enter): Releases the enter semaphore to allow other readers to modify ReadCount.
// Reading Data: The reader can safely read the data (no writers are writing).
// sem_wait(&enter): Locks enter again to safely decrement the ReadCount.
// Decrement ReadCount: Decreases the reader count.
// Last Reader Logic: If this is the last reader (ReadCount == 0), it releases the db semaphore to allow writers.
// sem_post(&enter): Releases enter semaphore after modifying ReadCount.
// writeDb Function:
// Purpose: Writes to the shared Data after ensuring exclusive access to the resource.
// Steps:
// sem_wait(&db): Locks the db semaphore to ensure no readers or other writers can access the resource.
// Modify Data: The writer updates the Data with a new value.
// sem_post(&db): Releases the db semaphore, allowing other writers or readers to access the resource.
// main Function:
// Initialization:
// Takes input for the number of readers and writers.
// Creates threads for each reader and writer.
// Initializes semaphores for managing access (enter and db).
// Thread Creation: Loops through the reader and writer count and creates corresponding threads for them.
// Thread Joining: After thread creation, the main function waits for all threads to finish by using pthread_join().
// 3. Potential External Examiner Questions:
// How does the sem_wait and sem_post mechanism work in this program?

// Explain the role of semaphores in synchronization and why they are used instead of mutexes.
// What will happen if the ReadCount variable is accessed without synchronization?

// Discuss the potential issues related to race conditions and how the enter semaphore prevents them.
// How do you handle simultaneous read and write operations in this program?

// Explain how the program ensures that multiple readers can access the data concurrently but writers have exclusive access.
// Why is the db semaphore required for writers?

// Discuss the importance of locking the database (db) for exclusive access during writing and preventing simultaneous writes.
// How would you modify this code to handle more complex scenarios like priority readers or writers?

// Consider adding logic for prioritizing certain threads (e.g., allowing writers to write even when readers are reading).
// 4. Summary of Important Concepts:
// Semaphores: Used for synchronization in concurrent programming. sem_wait locks the semaphore, and sem_post releases it.
// Reader-Writer Problem: A common synchronization problem where multiple readers can access a shared resource concurrently, but writers need exclusive access.
// Critical Region: A part of the program where shared resources are accessed. It is protected using semaphores to avoid conflicts.