#include "thread.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void* pattern1_thread(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int sleep_time = rand() % 8 + 1;

    fprintf(stdout, "Thread %d (tid %lu) started: will sleep for %d seconds\n",
            data->index, pthread_self(), sleep_time);

    sleep(sleep_time);

    fprintf(stdout, "Thread %d (tid %lu) exiting.\n", data->index,
            pthread_self());

    free(data);
    return NULL;
}

void pattern1(int threads) {
    fprintf(stdout, "** Pattern 1: creating %d threads **\n", threads);

    pthread_t thread_ids[threads];

    for (int i = 1; i <= threads; i++) {
        ThreadData* data = malloc(sizeof(ThreadData));
        data->index = i;

        if (pthread_create(&thread_ids[i - 1], NULL, pattern1_thread, data) !=
            0) {
            perror("Failed to create thread");
            exit(1);
        }

        fprintf(stdout, "Parent: created thread %d (tid %lu)\n", i,
                thread_ids[i - 1]);
    }

    for (int i = 0; i < threads; i++) {
        pthread_join(thread_ids[i], NULL);
    }

    fprintf(stdout, "** Pattern 1: All threads have exited **\n");
}

void* pattern2_thread(void* arg) {
    ThreadData* data = (ThreadData*)arg;

    // Check if another child thread should be created
    if (data->index < data->total_threads) {
        pthread_t child_thread;
        ThreadData* child_data = malloc(sizeof(ThreadData));
        child_data->index = data->index + 1;
        child_data->total_threads = data->total_threads;

        fprintf(stdout, "Thread %d (tid %lu) started.\n", data->index,
                pthread_self());
        // Create the next thread
        if (pthread_create(&child_thread, NULL, pattern2_thread, child_data) !=
            0) {
            perror("Failed to create child thread");
            exit(1);
        }

        fprintf(stdout, "Thread %d (tid %lu) created Thread %d (tid %lu)\n",
                data->index, pthread_self(), child_data->index, child_thread);

        int sleep_time = rand() % 8 + 1;
        fprintf(stdout, "Thread %d (tid %lu) sleeping for %d seconds.\n",
                data->index, pthread_self(), sleep_time);
        sleep(sleep_time);

        pthread_join(child_thread, NULL);
    } else if (data->index == data->total_threads) {
        int sleep_time = rand() % 8 + 1;
        fprintf(stdout, "Thread %d (tid %lu) sleeping for %d seconds.\n",
                data->index, pthread_self(), sleep_time);
        sleep(sleep_time);
    }

    fprintf(stdout, "Thread %d (tid %lu) exiting.\n", data->index,
            pthread_self());
    free(data);
    return NULL;
}

void pattern2(int threads) {
    fprintf(stdout, "** Pattern 2: creating %d threads **\n", threads);
    pthread_t first_thread;
    ThreadData* data = malloc(sizeof(ThreadData));
    data->index = 1;
    data->total_threads = threads;

    if (pthread_create(&first_thread, NULL, pattern2_thread, data) != 0) {
        perror("Failed to create thread");
        exit(1);
    }

    pthread_join(first_thread, NULL);
    fprintf(stdout, "** Pattern 2: All threads have exited **\n");
}