// 4
// 3

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int count = 0;

sem_t full, empty;
pthread_mutex_t mutex;

void *produce(void *args)
{
    int id = *((int *)args);

    if (count == BUFFER_SIZE)
    {
        printf("\nProducer Cannot Produce Because Buffer is Full");
    }
    else
    {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        printf("\nProducer %d is Entered in Critical Region : ",id);
        printf int newProduct = count + 1;
        buffer[count] = newProduct;
        printf("\nProducer %d produce new product %d", id, newProduct);
        count = count + 1;
        printf("\nBuffer Status : \n");
        for (int i = 0; i < BUFFER_SIZE; i++)
        {
            printf("%d ", buffer[i]);
        }
        printf("\nProducer %d is Exit from Critical Region : ",id);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}   

void *consume(void *args)
{
    int id = *((int *)args);

    if (count == 0)
    {
        printf("\nConsumer Cannot Consume Because Buffer is Empty");
    }
    else
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        printf("\nConsumer %d is Entered in Critical Region : ",id);
        int consumeProduct = buffer[count - 1];
        printf("\nConsumer %d consume product %d", id, consumeProduct);
        count = count - 1;
        buffer[count] = 0;
        printf("\nBuffer Status : \n");
        for (int i = 0; i < BUFFER_SIZE; i++)
        {
            printf("%d ", buffer[i]);
        }
        printf("\nConsumer %d is Exit from Critical Region : ",id);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main()
{
    // Producer Count
    int Prod = 0;
    int Consu = 0;
    printf("\nEnter the number of Producer : ");
    scanf("%d", &Prod);
    printf("\nEnter the number of Consumer : ");
    scanf("%d", &Consu);
    int pro = 0;
    int con = 0;
    int counter = 0;

    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        buffer[i] = 0;
    }

    // creating threads
    pthread_t Producer[Prod], Consumer[Consu];
    int ProdId[Prod], ConsuId[Consu];

    // initialising semaphores
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);
    pthread_mutex_init(&mutex, NULL);

    for (pro; pro < Prod; pro++)
    {
        ProdId[pro] = pro + 1;
        pthread_create(&Producer[pro], NULL, produce, &ProdId[pro]);
    }
    for (con; con < Consu; con++)
    {
        ConsuId[con] = con + 1;
        pthread_create(&Consumer[con], NULL, consume, &ConsuId[con]);
    }

    for (int i = 0; i < Prod; i++)
    {
        pthread_join(Producer[i], NULL);
    }
    for (int i = 0; i < Consu; i++)
    {
        pthread_join(Consumer[i], NULL);
    }

    return 0;
}




















// Concept: Producer-Consumer Problem
// The Producer-Consumer problem is a classic synchronization problem that involves two types of processes:

// Producers: Entities that create items and place them into a shared buffer.
// Consumers: Entities that take items from the buffer for use.
// The goal is to ensure mutual exclusion and proper synchronization between producers and consumers as they work on the shared buffer, maintaining data integrity without conflicts.

// Challenges in the Producer-Consumer Problem
// Buffer Overflow: If the producer tries to add an item to a full buffer, it could cause data loss or errors.
// Buffer Underflow: If the consumer tries to remove an item from an empty buffer, it will have no data to process.
// Race Conditions: Both producer and consumer accessing the buffer at the same time can corrupt the data.
// Solution Approach Using Mutex and Semaphores
// To solve these challenges, we use mutex locks and semaphores:

// Mutex (Mutual Exclusion): A mutex lock ensures that only one thread (either producer or consumer) can access the critical section (shared buffer) at a time. This prevents race conditions.
// Semaphores:
// empty: A counting semaphore initialized to the buffer size, representing the number of empty slots in the buffer. Producers wait on empty before producing, decreasing the count.
// full: A counting semaphore initialized to zero, representing the number of full slots. Consumers wait on full before consuming, increasing the count when a product is consumed.
// These two semaphores coordinate the access, ensuring that producers don’t overfill the buffer, and consumers don’t consume from an empty buffer.

// Code Analysis: Producer-Consumer Implementation
// Step-by-Step Explanation

// This code defines the producer-consumer problem with a shared buffer of fixed size (5) and uses mutex and semaphore synchronization:

// buffer[]: An integer array with a fixed size BUFFER_SIZE to hold produced items.

// count: Tracks the number of items in the buffer.

// Semaphores (full, empty): Control buffer capacity access for producers and consumers.

// Mutex (mutex): Ensures only one thread can update buffer and count at a time.

// produce() Function: Represents the producer’s behavior.

// Checks if count == BUFFER_SIZE (buffer is full).
// If there’s space, the producer:
// Waits on empty, acquires the mutex, and produces an item.
// Updates the buffer and increments count.
// Releases the mutex and signals full.
// consume() Function: Represents the consumer’s behavior.

// Checks if count == 0 (buffer is empty).
// If there are items to consume, the consumer:
// Waits on full, acquires the mutex, and consumes an item.
// Updates the buffer and decrements count.
// Releases the mutex and signals empty.
// Algorithm Explanation

// Initialization:

// Semaphores are initialized: empty to buffer capacity and full to 0.
// Mutex lock is initialized.
// Thread Creation:

// A number of producer and consumer threads are created.
// Each producer and consumer executes their respective functions (produce() and consume()), managing access to buffer.
// Synchronization Using Semaphores and Mutex:

// Semaphores ensure buffer limits are respected.
// Mutex lock ensures one producer or consumer modifies buffer at a time.
// Questions and Answers for Potential Exam

// What does the mutex lock achieve in this code?

// The mutex lock enforces mutual exclusion, allowing only one thread to modify the shared buffer and count at a time, preventing race conditions.
// How do full and empty semaphores control the buffer?

// empty prevents producers from producing when the buffer is full, while full prevents consumers from consuming when the buffer is empty.
// What happens if there are more producers than consumers (or vice versa)?

// Producers will wait if the buffer is full; consumers will wait if the buffer is empty. Regardless of their number, the synchronization ensures they wait until conditions allow them to proceed.
// Updated Code for Errors and Clarifications
// There is an error in the produce() function where printf is used incorrectly. Here’s the corrected code, including the creation of the product in produce():

// c
// Copy code
// #include <stdio.h>
// #include <stdlib.h>
// #include <semaphore.h>
// #include <pthread.h>

// #define BUFFER_SIZE 5
// int buffer[BUFFER_SIZE];
// int count = 0;

// sem_t full, empty;
// pthread_mutex_t mutex;

// void *produce(void *args)
// {
//     int id = *((int *)args);

//     if (count == BUFFER_SIZE)
//     {
//         printf("\nProducer Cannot Produce Because Buffer is Full");
//     }
//     else
//     {
//         sem_wait(&empty);
//         pthread_mutex_lock(&mutex);
//         printf("\nProducer %d is Entered in Critical Region : ", id);
        
//         int newProduct = count + 1; // Corrected line to declare and initialize newProduct
//         buffer[count] = newProduct;
//         printf("\nProducer %d produce new product %d", id, newProduct);
//         count = count + 1;

//         printf("\nBuffer Status : \n");
//         for (int i = 0; i < BUFFER_SIZE; i++)
//         {
//             printf("%d ", buffer[i]);
//         }
//         printf("\nProducer %d is Exit from Critical Region : ", id);
//         pthread_mutex_unlock(&mutex);
//         sem_post(&full);
//     }
// }   

// void *consume(void *args)
// {
//     int id = *((int *)args);

//     if (count == 0)
//     {
//         printf("\nConsumer Cannot Consume Because Buffer is Empty");
//     }
//     else
//     {
//         sem_wait(&full);
//         pthread_mutex_lock(&mutex);
//         printf("\nConsumer %d is Entered in Critical Region : ", id);
        
//         int consumeProduct = buffer[count - 1];
//         printf("\nConsumer %d consume product %d", id, consumeProduct);
//         count = count - 1;
//         buffer[count] = 0;

//         printf("\nBuffer Status : \n");
//         for (int i = 0; i < BUFFER_SIZE; i++)
//         {
//             printf("%d ", buffer[i]);
//         }
//         printf("\nConsumer %d is Exit from Critical Region : ", id);
//         pthread_mutex_unlock(&mutex);
//         sem_post(&empty);
//     }
// }

// int main()
// {
//     // Producer Count
//     int Prod = 0;
//     int Consu = 0;
//     printf("\nEnter the number of Producer : ");
//     scanf("%d", &Prod);
//     printf("\nEnter the number of Consumer : ");
//     scanf("%d", &Consu);
//     int pro = 0;
//     int con = 0;

//     for (int i = 0; i < BUFFER_SIZE; i++)
//     {
//         buffer[i] = 0;
//     }

//     // creating threads
//     pthread_t Producer[Prod], Consumer[Consu];
//     int ProdId[Prod], ConsuId[Consu];

//     // initialising semaphores
//     sem_init(&full, 0, 0);
//     sem_init(&empty, 0, BUFFER_SIZE);
//     pthread_mutex_init(&mutex, NULL);

//     for (pro; pro < Prod; pro++)
//     {
//         ProdId[pro] = pro + 1;
//         pthread_create(&Producer[pro], NULL, produce, &ProdId[pro]);
//     }
//     for (con; con < Consu; con++)
//     {
//         ConsuId[con] = con + 1;
//         pthread_create(&Consumer[con], NULL, consume, &ConsuId[con]);
//     }

//     for (int i = 0; i < Prod; i++)
//     {
//         pthread_join(Producer[i], NULL);
//     }
//     for (int i = 0; i < Consu; i++)
//     {
//         pthread_join(Consumer[i], NULL);
//     }

//     return 0;
// }
// This corrected code ensures:

// Producers and consumers access the buffer sequentially.
// It handles situations where the buffer may be full or empty by blocking producers or consumers as necessary.





// You said:
// what is difference between mutex and semaphore then
// ChatGPT said:
// ChatGPT
// Difference Between Mutex and Semaphore
// Mutex (Mutual Exclusion) and Semaphore are both synchronization tools used in multithreading and concurrent programming, but they have different characteristics and use cases. Below is a comparison between the two:

// 1. Basic Definition
// Mutex (Mutual Exclusion): A mutex is a synchronization object used to protect shared resources so that only one thread can access the resource at any given time. It is essentially a lock that guarantees exclusive access to a resource.

// Key Point: Only one thread can own a mutex at a time.
// Semaphore: A semaphore is a synchronization tool that maintains a count, which is used to control access to a shared resource. It allows multiple threads to access the resource concurrently, but in limited numbers, based on the value of the semaphore.

// Key Point: Semaphores can be used to manage multiple threads (more than one thread can hold a semaphore).
// 2. Usage and Purpose
// Mutex:

// Used when you need exclusive access to a resource.
// Only one thread can lock a mutex at any time.
// Ideal for protecting critical sections where resources are accessed by a single thread at a time.
// Semaphore:

// Used to manage access to a pool of resources (or to control the number of threads accessing a particular resource).
// Can allow multiple threads to access the resource simultaneously, but within the limit set by the semaphore count.
// Useful for limiting the number of concurrent accesses to a resource.
// 3. Mechanism of Working
// Mutex:

// Only one thread can lock a mutex at a time. If a second thread attempts to lock the same mutex, it will block until the first thread releases it.
// A thread that locks a mutex must also be the one to unlock it. It is owned by the thread that locks it.
// Semaphore:

// A semaphore works with a count. When the count is greater than 0, a thread can "decrease" the count (acquire the semaphore). When the count reaches 0, other threads trying to acquire the semaphore will block until the count becomes greater than 0.
// Semaphores don't have an "owner". Multiple threads can signal (release) or wait (acquire) on a semaphore, depending on the semaphore's value.
// 4. Types of Semaphore
// Binary Semaphore (also known as a Mutex):

// A special type of semaphore where the count is either 0 or 1. It behaves similarly to a mutex but can be used by multiple threads to signal and wait.
// Counting Semaphore:

// A semaphore with a larger count that can represent multiple resources. For example, it can manage the number of available connections in a connection pool.
// 5. Block and Wake-up Mechanism
// Mutex:

// If a thread tries to lock a mutex that is already locked, it will block until the mutex is available.
// Mutexes are owned by the thread that locks them. Other threads cannot unlock a mutex they did not lock.
// Semaphore:

// When a thread waits on a semaphore, it blocks if the count is 0. When another thread releases the semaphore (increments the count), a waiting thread is woken up.
// Semaphores are not owned by any thread, so any thread can signal the semaphore.
// 6. Use Cases
// Mutex:

// Used for exclusive access to a resource. For example, when multiple threads need to modify a shared variable or data structure (e.g., updating a shared counter or modifying shared data), a mutex is used to ensure that only one thread modifies it at a time.
// Semaphore:

// Used when you want to manage access to a fixed number of resources. For example, controlling the number of threads that can access a database connection pool, controlling the number of concurrent downloads, or limiting access to a shared resource.
// 7. Performance Impact
// Mutex:
// The performance of mutexes is generally good but can degrade when multiple threads are frequently contending for the same lock. It is typically used when mutual exclusion is needed.
// Semaphore:
// Semaphores can be more efficient when you need to manage access to multiple resources simultaneously. However, they can become complex to manage and debug, especially when trying to coordinate many threads.
// Key Differences at a Glance:
// Feature	Mutex	Semaphore
// Purpose	Protects a resource, allowing only one thread at a time.	Controls access to multiple resources, allowing several threads concurrently.
// Count	Binary (0 or 1).	Can have any count value.
// Thread Ownership	Owned by the thread that locks it.	No ownership; any thread can signal or wait.
// Blocking	Blocks other threads until unlocked.	Blocks threads when count reaches 0.
// Use Case	Protecting critical sections (e.g., single resource).	Managing a pool of resources or limiting concurrent access.
// Conclusion
// Use Mutex when you need to ensure that only one thread accesses a critical section of code or data at a time.
// Use Semaphore when you need to manage access to a resource pool and allow multiple threads to work concurrently, but with a controlled limit.