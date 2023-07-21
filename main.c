#include <stdio.h>
#include <pthread.h>
#include "file_search_lib.h"

int main() {
    const char* target_file = "example.txt"; 
    if (pthread_create(&tid, NULL, search_file, (void*)target_file) != 0) {
        perror("Failed to create thread");
        return 1;
    }
    pthread_join(tid, NULL);

    return 0;
}
