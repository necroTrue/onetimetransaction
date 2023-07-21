#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>
#include "file_search_lib.h"

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static volatile int file_found = 0;

void* search_file(void* arg) {
    const char* target_file = (const char*)arg;
    char current_path[256];

    pthread_mutex_lock(&mutex);
    if (file_found) {
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }
    pthread_mutex_unlock(&mutex);

    DIR* dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to open directory");
        pthread_exit(NULL);
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        if (entry->d_type == DT_DIR) {
          
            if (pthread_create(&tid, NULL, search_file, (void*)target_file) != 0) {
                perror("Failed to create thread");
                continue;
            }
            pthread_detach(tid);
        } else if (strcmp(entry->d_name, target_file) == 0) {
            
            file_found = 1;
            getcwd(current_path, sizeof(current_path));
            printf("File found: %s/%s\n", current_path, target_file);
            pthread_mutex_unlock(&mutex);
            closedir(dir);
            pthread_exit(NULL);
        }
    }

    closedir(dir);
    pthread_exit(NULL);
}
