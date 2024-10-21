#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "thread.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stdout, "Usage: %s <pattern> <threads>\n", argv[0]);
            exit(1);
    }

    srand(time(NULL));

    int threads = atoi(argv[1]);
    int pattern = atoi(argv[2]);
    
    if (threads < 1 || threads > 256 ||
        (pattern < 1 || pattern > 2)) {
        fprintf(stdout,
                "Invalid arguments. Number of processes must be between 1 and "
                "256, and pattern number must be 1 or 2\n");
        return 1;
    }

    if (pattern == 1) {
        pattern1(threads);
    } else if (pattern == 2) {
        pattern2(threads);
    } else {
        fprintf(stdout, "Invalid pattern. Use 1 or 2.\n");
            exit(1);
    }

    return 0;
}