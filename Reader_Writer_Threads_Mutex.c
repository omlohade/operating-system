#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Declare mutexes for synchronizing readers and writers
pthread_mutex_t mutex;       // Protects access to read_count
pthread_mutex_t write_mutex; // Provides exclusive access for writers to shared_data

int read_count = 0;          // Counts the number of active readers
int shared_data = 0;         // The shared data that readers and writers access

// Reader function
void* reader(void* arg) {
	// Retrieve reader ID from argument passed by main
	int reader_id = *((int*)arg);

	// Begin reader entry section
	pthread_mutex_lock(&mutex);          // Lock mutex to update read_count safely, This mutex lock ensures that only one thread can modify read_count at a time.
	read_count++;                        // Increment the reader count
	if (read_count == 1) {               // If this is the first reader,
		pthread_mutex_lock(&write_mutex); // lock write_mutex to block writers
	}
	printf("Reader %d is entering the critical region:\n", reader_id);
	pthread_mutex_unlock(&mutex);        // Unlock mutex for other readers

	// Reading the shared data (Critical Section for readers)
	printf("Reader %d: reads shared data as %d\n", reader_id, shared_data);

	// Begin reader exit section
	pthread_mutex_lock(&mutex);          // Lock mutex to safely decrement read_count
	printf("Reader %d is leaving the critical region.\n", reader_id);
	read_count--;                        // Decrement the reader count
	if (read_count == 0) {               // If this is the last reader,
		pthread_mutex_unlock(&write_mutex); // unlock write_mutex to allow writers
	}
	pthread_mutex_unlock(&mutex);        // Unlock mutex for other readers

	return NULL; // End of reader function
}

// Writer function
void* writer(void* arg) {
	// Retrieve writer ID from argument passed by main
	int writer_id = *((int*)arg);

	// Begin writer entry section
	pthread_mutex_lock(&write_mutex);    // Lock write_mutex to gain exclusive access
	printf("\nWriter %d is entering the critical region:\n", writer_id);

	// Writing to the shared data (Critical Section for writers)
	shared_data += 10;                   // Modify shared_data
	printf("Writer %d: writes shared data as %d\n", writer_id, shared_data);

	printf("Writer %d is leaving the critical region.\n", writer_id);
	pthread_mutex_unlock(&write_mutex);  // Unlock write_mutex to allow other writers or readers

	return NULL; // End of writer function
}

int main() {
	int num_readers, num_writers;

	// Get the number of readers and writers from the user
	printf("Enter the number of readers: ");
	scanf("%d", &num_readers);
	printf("Enter the number of writers: ");
	scanf("%d", &num_writers);

	// Arrays of threads.
	pthread_t readers[num_readers];
	pthread_t writers[num_writers];

	// Arrays to store thread IDs for readers and writers
	int reader_ids[num_readers];
	int writer_ids[num_writers];

	// Initialize mutexes
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&write_mutex, NULL);

	// Creating reader threads
	for (int i = 0; i < num_readers; i++) {
		reader_ids[i] = i + 1;                               // Assign a unique ID to each reader
		pthread_create(&readers[i], NULL, reader, &reader_ids[i]); // Create reader thread
	}

	// Creating writer threads
	for (int i = 0; i < num_writers; i++) {
		writer_ids[i] = i + 1;                               // Assign a unique ID to each writer
		pthread_create(&writers[i], NULL, writer, &writer_ids[i]); // Create writer thread
	}

	// Joining reader threads (wait for all readers to finish)
	for (int i = 0; i < num_readers; i++) {
		pthread_join(readers[i], NULL);                      // Wait for each reader thread to complete
	}

	// Joining writer threads (wait for all writers to finish)
	for (int i = 0; i < num_writers; i++) {
		pthread_join(writers[i], NULL);                      // Wait for each writer thread to complete
	}

	// Destroy mutexes after threads have finished
	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&write_mutex);

	return 0; // End of main function
}
