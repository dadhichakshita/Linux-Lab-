#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 5
#define PRODUCE_COUNT 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Declare semaphores and mutex
HANDLE emptySlots;
HANDLE fullSlots;
HANDLE mutex;

// Producer thread function
DWORD WINAPI producer(LPVOID lpParam) {
    int item;
    for (int i = 1; i <= PRODUCE_COUNT; i++) {
        item = i;  // Produce an item

        WaitForSingleObject(emptySlots, INFINITE); // Wait if buffer full
        WaitForSingleObject(mutex, INFINITE);      // Enter critical section

        buffer[in] = item;
        printf("Producer produced item %d at buffer[%d]\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        ReleaseMutex(mutex);       // Exit critical section
        ReleaseSemaphore(fullSlots, 1, NULL); // Signal item available

        Sleep(500); // Simulate production time
    }
    return 0;
}

// Consumer thread function
DWORD WINAPI consumer(LPVOID lpParam) {
    int item;
    for (int i = 1; i <= PRODUCE_COUNT; i++) {
        WaitForSingleObject(fullSlots, INFINITE); // Wait if buffer empty
        WaitForSingleObject(mutex, INFINITE);     // Enter critical section

        item = buffer[out];
        printf("Consumer consumed item %d from buffer[%d]\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        ReleaseMutex(mutex);        // Exit critical section
        ReleaseSemaphore(emptySlots, 1, NULL); // Signal slot empty

        Sleep(1000); // Simulate consumption time
    }
    return 0;
}

int main() {
    HANDLE producerThread, consumerThread;

    // Initialize synchronization objects
    emptySlots = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);
    fullSlots = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);
    mutex = CreateMutex(NULL, FALSE, NULL);

    // Create threads
    producerThread = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    consumerThread = CreateThread(NULL, 0, consumer, NULL, 0, NULL);

    // Wait for threads to complete
    WaitForSingleObject(producerThread, INFINITE);
    WaitForSingleObject(consumerThread, INFINITE);

    // Clean up
    CloseHandle(producerThread);
    CloseHandle(consumerThread);
    CloseHandle(emptySlots);
    CloseHandle(fullSlots);
    CloseHandle(mutex);

    printf("\nSimulation finished successfully.\n");
    return 0;
}
