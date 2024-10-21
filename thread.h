#ifndef THREAD_H
#define THREAD_H

typedef struct {
    int index;
    int total_threads;
} ThreadData;

void pattern1(int threads);
void pattern2(int threads);

#endif