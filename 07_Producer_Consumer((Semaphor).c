// 7
// 2

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int count = 0;

sem_t full, empty;
sem_t S;

void *produce(void *args)
{
    int id = *((int *)args);

    if (count == BUFFER_SIZE)
    {
        printf("\nProducer Cannot Produce Because Buffer is Full");
        return;
    }
    else
    {
        sem_wait(&empty);
        sem_wait(&S);
        printf("\nProducer %d is Entered in Critical Region : ", id);
        int newProduct = count + 1;
        buffer[count] = newProduct;
        printf("\nProducer %d produce new product %d", id, newProduct);
        count = count + 1;
        printf("\nBuffer Status : \n");
        for (int i = 0; i < BUFFER_SIZE; i++)
        {
            printf("%d ", buffer[i]);
        }
        printf("\nProducer %d is Entered in Critical Region : ", id);
        sem_post(&S);
        sem_post(&full);
    }
}

void *consume(void *args)
{
    int id = *((int *)args);

    if (count == 0)
    {
        printf("\nConsumer Cannot Consume Because Buffer is Empty");
        return;
    }
    else
    {
        sem_wait(&full);
        sem_wait(&S);
        printf("\nConsumer %d is Entered in Critical Region : ", id);
        int consumeProduct = buffer[count - 1];
        printf("\nConsumer %d consume product %d", id, consumeProduct);
        count = count - 1;
        buffer[count] = 0;
        printf("\nBuffer Status : \n");
        for (int i = 0; i < BUFFER_SIZE; i++)
        {
            printf("%d ", buffer[i]);
        }
        sem_post(&S);
        sem_post(&empty);
        printf("\nConsumer %d is Exit from Critical Region : ", id);
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
    sem_init(&S, 0, 1);

    for (pro; pro <Prod; pro++)
    {
        ProdId[pro] = pro + 1;
        pthread_create(&Producer[pro], NULL, produce, &ProdId[pro]);
    }
    for (con; con < Consu; con++)
    {
        ConsuId[con] = con + 1;
        pthread_create(&Consumer[con], NULL, consume, &ConsuId[con]);
    }
    for (pro; pro < Prod; pro++)
    {
        ProdId[pro] = pro + 1;
        pthread_create(&Producer[pro], NULL, produce, &ProdId[pro]);
    }

    for (int i = 0; i < Consu; i++)
    {
        pthread_join(Consumer[i], NULL);
    }

    return 0;
}



















// 1. Concept Explanation:
// This code implements the Producer-Consumer problem using semaphores for synchronization. Here’s a breakdown of the key concepts:

// Producer-Consumer Problem: It involves two types of processes:
// Producer: Generates items and places them into a shared buffer.
// Consumer: Consumes items from the shared buffer.
// Buffer: The buffer holds a fixed number of items (in this case, 5). The producer places items into the buffer, and the consumer removes items from it.
// Semaphores:
// full: Tracks how many slots in the buffer are filled (initialized to 0).
// empty: Tracks how many slots in the buffer are empty (initialized to BUFFER_SIZE).
// S: A binary semaphore to ensure mutual exclusion (critical section) for the buffer. It allows only one producer or one consumer to access the buffer at any given time.
// In this scenario:

// Producers wait for an empty slot (empty semaphore) and then enter the critical region to add a product to the buffer.
// Consumers wait for a full slot (full semaphore) and then enter the critical region to remove a product from the buffer.
// 2. Code Walkthrough (Step-by-Step Explanation):
// produce Function:
// Purpose: The producer creates a new product and adds it to the shared buffer.
// Steps:
// Check Buffer: If the buffer is full (count == BUFFER_SIZE), the producer cannot produce a new item.
// sem_wait(&empty): Waits for an empty slot in the buffer.
// sem_wait(&S): Locks the critical section to prevent concurrent access to the buffer.
// Produce Product: Adds a new product to the buffer at the current count index and increments the count.
// sem_post(&S): Releases the critical section lock.
// sem_post(&full): Signals that the buffer now has one more full slot.
// consume Function:
// Purpose: The consumer removes a product from the shared buffer.
// Steps:
// Check Buffer: If the buffer is empty (count == 0), the consumer cannot consume any item.
// sem_wait(&full): Waits for a full slot in the buffer.
// sem_wait(&S): Locks the critical section to prevent concurrent access to the buffer.
// Consume Product: Removes a product from the buffer at the current count - 1 index and decrements the count.
// sem_post(&S): Releases the critical section lock.
// sem_post(&empty): Signals that the buffer now has one more empty slot.
// main Function:
// Initialization:
// The program starts by reading the number of producer and consumer threads from the user.
// Initializes the semaphores and buffer.
// Thread Creation: The program creates producer and consumer threads based on user input.
// Thread Joining: After creating the threads, the main function waits for all threads to finish using pthread_join.
// 3. Potential External Examiner Questions:
// What is the role of the S semaphore in the producer-consumer problem?

// Explain why S is used for mutual exclusion in this scenario and how it helps prevent concurrent access to the shared buffer.
// What would happen if you remove the sem_wait(&S) and sem_post(&S) in the critical sections of both producer and consumer?

// Discuss the potential race conditions and data inconsistencies that might occur without these semaphore operations.
// How does the program handle buffer overflow and underflow?

// Explain the checks in the producer and consumer functions to ensure that they do not exceed the buffer's capacity or try to consume from an empty buffer.
// Why is there a redundant loop where you create producer threads twice in the main function?

// Identify the mistake in the thread creation logic and discuss how this affects the program's execution.
// What changes would you make if you wanted to allow multiple producers and consumers to work simultaneously without affecting the buffer consistency?

// Explore optimizations such as handling synchronization at a finer level or introducing more complex synchronization mechanisms (e.g., conditional variables).
// 4. Summary of Key Concepts and Issues:
// Semaphores: Used to manage the number of available resources and ensure safe concurrent access.

// empty: Tracks the number of empty slots available in the buffer.
// full: Tracks the number of full slots in the buffer.
// S: Ensures mutual exclusion for the critical section (buffer manipulation).
// Critical Section: The section of code where the shared resource (the buffer) is accessed. The producer and consumer cannot enter the critical section simultaneously, and S ensures that only one thread can access the buffer at a time.

// Buffer Handling: The producer adds items to the buffer, and the consumer removes items. Semaphores control the availability of slots and prevent simultaneous read/write operations that could lead to inconsistency.

// Bug in Code: The main function creates the producer threads twice. This is a bug and should be fixed by ensuring the producer threads are created only once.