#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int main() {
    DIR *dir;
    struct dirent *entry;
    FILE *fp;
    char stat_path[BUFFER_SIZE];
    char line[BUFFER_SIZE];
    pid_t top_pid = -1;
    pid_t parent_pid = -1;

    // Find the PID of the 'top' program
    dir = opendir("/proc");
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        if (isdigit(entry->d_name[0])) {
            snprintf(stat_path, BUFFER_SIZE, "/proc/%s/comm", entry->d_name);
            fp = fopen(stat_path, "r");
            if (fp != NULL) {
                if (fgets(line, BUFFER_SIZE, fp) != NULL) {
                    // Remove trailing newline
                    line[strcspn(line, "\n")] = 0;
                    if (strcmp(line, "top") == 0) {
                        top_pid = atoi(entry->d_name);
                        fclose(fp);
                        break;
                    }
                }
                fclose(fp);
            }
        }
    }
    closedir(dir);

    if (top_pid != -1) {
        // Get the parent PID of the 'top' process
        snprintf(stat_path, BUFFER_SIZE, "/proc/%d/stat", top_pid);
        fp = fopen(stat_path, "r");
        if (fp != NULL) {
            // The fourth field in /proc/[pid]/stat is the parent PID
            if (fscanf(fp, "%*d %*s %*c %d", &parent_pid) == 1) {
                printf("Parent PID of 'top' (%d): %d\n", top_pid, parent_pid);
            } else {
                fprintf(stderr, "Error reading parent PID for process %d\n", top_pid);
            }
            fclose(fp);
        } else {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("'top' process not found.\n");
    }

    return 0;
}