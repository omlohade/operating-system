#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 3
#define MAX_MEALS 1 // Number of times each philosopher will eat

sem_t forks[NUM_PHILOSOPHERS];
pthread_mutex_t lock;
int meal_count[NUM_PHILOSOPHERS] = {0}; // Tracks meals for each philosopher

void *philosopher(void *arg)
{
    int id = *((int *)arg);
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    while (meal_count[id] < MAX_MEALS)
    {
        // Thinking
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        // Picking up forks
        pthread_mutex_lock(&lock);
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);
        pthread_mutex_unlock(&lock);

        // Eating
        printf("Philosopher %d is eating.\n", id);
        sleep(2); // Eating time
        meal_count[id]++;
        printf("Philosopher %d finished eating (%d/%d times).\n", id, meal_count[id], MAX_MEALS);

        // Putting down forks
        sem_post(&forks[left]);
        sem_post(&forks[right]);
    }

    printf("Philosopher %d is done eating and leaving.\n", id);
    return NULL;
}

int main()
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize semaphores and mutex
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_init(&forks[i], 0, 1);
    }
    pthread_mutex_init(&lock, NULL);

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Wait for all philosophers to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    // Cleanup
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_destroy(&forks[i]);
    }
    pthread_mutex_destroy(&lock);

    printf("All philosophers have finished eating.\n");
    return 0;
}



















// This code implements the Dining Philosophers Problem using semaphores and a mutex. In this problem, philosophers sit at a table and alternate between thinking and eating, but they need two forks to eat. The code ensures that philosophers pick up both forks before eating and put them down afterward while avoiding deadlock and race conditions.

// 1. Concept Explanation:
// Problem Overview:

// There are NUM_PHILOSOPHERS philosophers who think and eat.
// Each philosopher needs two forks (one on the left and one on the right) to eat. The forks are shared resources, and only one philosopher can use a fork at a time.
// Semaphores:

// forks[]: An array of semaphores, each representing a fork. Each fork can be used by only one philosopher at a time, and the semaphores ensure mutual exclusion for the forks.
// pthread_mutex_t lock: A mutex used to prevent race conditions when philosophers pick up and put down forks. This ensures only one philosopher can attempt to pick up the forks at a time.
// Philosopher Actions:

// Thinking: The philosopher thinks for a while.
// Eating: The philosopher picks up both forks, eats, and then puts the forks back down.
// Deadlock and Starvation Avoidance:

// Each philosopher locks the mutex before trying to pick up both forks. This prevents deadlock, where philosophers could wait indefinitely for each other’s forks.
// Semaphores ensure mutual exclusion, and the mutex ensures proper sequencing of the pick-up process.
// 2. Code Walkthrough (Step-by-Step Explanation):
// philosopher Function:
// Purpose: Simulates the behavior of each philosopher (thinking, eating, and putting down forks).
// Steps:
// Thinking: Each philosopher thinks (simulated with sleep(1)).
// Pick up forks:
// The philosopher locks the mutex (pthread_mutex_lock(&lock)) to ensure that only one philosopher can attempt to pick up the forks at a time.
// They then try to pick up the left and right forks (sem_wait(&forks[left]) and sem_wait(&forks[right])).
// After picking up both forks, the philosopher unlocks the mutex (pthread_mutex_unlock(&lock)).
// Eating: The philosopher eats (simulated with sleep(2)), incrementing their meal_count each time they finish eating.
// Put down forks: After eating, the philosopher releases both forks (sem_post(&forks[left]) and sem_post(&forks[right])).
// The philosopher repeats the above process until they have eaten MAX_MEALS times.
// main Function:
// Initialization:
// Initializes the semaphores for each fork (sem_init(&forks[i], 0, 1)).
// Initializes the mutex (pthread_mutex_init(&lock, NULL)).
// Thread Creation:
// Creates a thread for each philosopher (pthread_create(&philosophers[i], NULL, philosopher, &ids[i])).
// Thread Joining:
// Waits for all philosopher threads to finish (pthread_join(philosophers[i], NULL)).
// Cleanup:
// Destroys the semaphores and the mutex after the philosophers finish eating.
// 3. Potential External Examiner Questions:
// Why is a mutex used in this code, and what would happen if it were removed?

// The mutex ensures that only one philosopher can attempt to pick up both forks at the same time. Without it, multiple philosophers could try to pick up the forks simultaneously, leading to race conditions.
// What is the role of semaphores in this code, and how do they help prevent deadlock?

// Semaphores (forks[]) are used to represent the availability of forks. A philosopher can only pick up a fork if the corresponding semaphore allows it. This helps ensure that only one philosopher can use a fork at a time, preventing deadlock by controlling access to shared resources.
// What would happen if the philosopher thread tries to pick up forks without waiting for the mutex lock?

// If the mutex was not used, multiple philosophers could simultaneously attempt to pick up forks, which could lead to inconsistent state or deadlock, as they might each pick up one fork and wait for the other indefinitely.
// Explain why the philosophers only eat once (MAX_MEALS = 1), and how would the behavior change if MAX_MEALS were greater than 1?

// With MAX_MEALS = 1, each philosopher eats only once before leaving. If MAX_MEALS were greater than 1, each philosopher would repeat the cycle of thinking and eating the specified number of times. The mutex and semaphore logic would still ensure proper synchronization and prevent race conditions.
// Can this implementation be generalized to more philosophers, and if so, how?

// Yes, the implementation can easily be generalized to more philosophers by adjusting the NUM_PHILOSOPHERS constant. However, when the number of philosophers increases, issues like deadlock and starvation need careful handling to ensure all philosophers can eventually eat.
// 4. Summary of Key Concepts and Issues:
// Deadlock Prevention: The use of a mutex and semaphores ensures that deadlock is prevented by making sure that philosophers do not indefinitely wait for each other’s resources.

// Race Condition Prevention: The mutex ensures that no two philosophers simultaneously pick up forks, preventing inconsistent states.

// Fork Allocation: Semaphores control access to the shared forks and maintain synchronization so that only one philosopher can use a fork at a time.

// Issues with Scalability:

// If the number of philosophers increases, there’s a potential for starvation (some philosophers may never get a chance to eat if they are always waiting for forks).
// A more complex solution (e.g., using a more advanced synchronization technique like Chandy/Misra's solution) would be required to address such issues as the number of philosophers grows.