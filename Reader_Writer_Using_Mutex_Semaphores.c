#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

// Declare two semaphores: one for controlling read/write access and another for read count updates
sem_t rw_mutex, mutex;
int read_count = 0;   // Number of active readers
int shared_data = 0;  // Shared data to be read/written by reader and writer threads

// Reader function
void* reader(void* arg) {
    int reader_id = *((int*)arg);  // Retrieve reader ID from argument

    // Entry section for readers
    sem_wait(&mutex);              // Lock `mutex` to safely update `read_count`
    read_count++;                  // Increment `read_count` to indicate a new reader has entered

    if (read_count == 1) {         // If this is the first reader,
        sem_wait(&rw_mutex);       // lock `rw_mutex` to block writers
    }
    printf("Reader %d is entering the critical region:\n", reader_id);
    sem_post(&mutex);              // Unlock `mutex` for other readers to proceed

    // Critical section for reading the shared data
    printf("Reader %d: reads shared data as %d\n", reader_id, shared_data);

    // Exit section for readers
    sem_wait(&mutex);              // Lock `mutex` to safely update `read_count` during exit
    printf("Reader %d is leaving the critical region:\n", reader_id);
    read_count--;                  // Decrement `read_count` as this reader finishes

    if (read_count == 0) {         // If this is the last reader,
        sem_post(&rw_mutex);       // unlock `rw_mutex` to allow writers access
    }
    sem_post(&mutex);              // Unlock `mutex` for other readers to proceed

    return NULL;                   // End of reader function
}

// Writer function
void* writer(void* arg) {
    int writer_id = *((int*)arg);  // Retrieve writer ID from argument

    // Writers need exclusive access to the shared data, so they lock `rw_mutex`
    sem_wait(&rw_mutex);           // Lock `rw_mutex` to ensure no other readers/writers access shared data
    printf("\nWriter %d is entering the critical region:\n", writer_id);
    
    // Critical section for writing to the shared data
    shared_data += 10;             // Modify the shared data
    printf("Writer %d: writes shared data as %d\n", writer_id, shared_data);
    
    printf("\nWriter %d is leaving the critical region:\n", writer_id);
    sem_post(&rw_mutex);           // Unlock `rw_mutex` after writing, allowing other readers or writers to proceed

    return NULL;                   // End of writer function
}

int main() {
    int num_readers, num_writers;

    // Get the number of readers and writers from the user
    printf("Enter the number of readers: ");
    scanf("%d", &num_readers);
    printf("Enter the number of writers: ");
    scanf("%d", &num_writers);

    // Initialize arrays for thread identifiers
    pthread_t readers[num_readers], writers[num_writers];
    int reader_ids[num_readers], writer_ids[num_writers];

    // Initialize semaphores with an initial value of 1 (binary semaphore for mutual exclusion)
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    // Creating reader threads
    for (int i = 0; i < num_readers; i++) {
        reader_ids[i] = i + 1;                              // Assign unique IDs to readers
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);  // Create each reader thread
    }

    // Creating writer threads
    for (int i = 0; i < num_writers; i++) {
        writer_ids[i] = i + 1;                              // Assign unique IDs to writers
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);  // Create each writer thread
    }

    // Joining reader threads to ensure they complete execution
    for (int i = 0; i < num_readers; i++) {
        pthread_join(readers[i], NULL);
    }

    // Joining writer threads to ensure they complete execution
    for (int i = 0; i < num_writers; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores after all threads have finished
    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;   // End of main function
}
