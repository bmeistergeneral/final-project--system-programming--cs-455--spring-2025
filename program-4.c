#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#define BUFFER_SIZE 256

int main() {
    char *dynamic_string;
    char maps_path[BUFFER_SIZE];
    FILE *fp;
    char line[BUFFER_SIZE];
    uintptr_t text_end = 0;
    uintptr_t data_end = 0;
    uintptr_t bss_end = 0;
    pid_t pid = getpid(); // Gets current process ID

    // Dynamically allocates 1024 bytes
    dynamic_string = malloc(1024);
    if (dynamic_string == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Builds path to /proc/[pid]/maps
    snprintf(maps_path, BUFFER_SIZE, "/proc/%d/maps", pid);
    fp = fopen(maps_path, "r"); // Open memory map file for this process
    if (fp == NULL) {
        perror("fopen");
        free(dynamic_string);
        exit(EXIT_FAILURE);
    }

    // Reads each line of the maps file
    while (fgets(line, BUFFER_SIZE, fp) != NULL) {
        uintptr_t start, end;
        char permissions[5];
        long offset;
        char device[6];
        int inode;
        char pathname[BUFFER_SIZE];

        // Parses memory map line into components
        if (sscanf(line, "%lx-%lx %4s %lx %5s %d %s",
                   &start, &end, permissions, &offset, device, &inode, pathname) == 7) {
            // If it's the executable's text segment (read-execute)
            if (strstr(permissions, "r-xp") && strstr(pathname, "/program4")) {
                text_end = end;
            }
            // If it's a writable/readable segment for data or heap
            else if ((strstr(permissions, "rw-p") || strstr(permissions, "r--p")) &&
                     (strstr(pathname, "/program4") || strstr(pathname, "[heap]"))) {
                if (end > data_end) {
                    data_end = end; // Update highest data segment end
                }
            }
            // If it's the stack, infer BSS ends before it
            else if ((strstr(permissions, "rw-p") || strstr(permissions, "r--p")) &&
                     strstr(pathname, "[stack]")) {
                if (start > bss_end) {
                    bss_end = start; // Approximate BSS end as start of stack
                }
            }
        }
    }

    fclose(fp);               // Close the maps file
    free(dynamic_string);     // Free allocated memory

    // Print the inferred memory segment ends
    printf("End of program text: %p\n", (void *)text_end);
    printf("End of initialized data segment (approximate): %p\n", (void *)data_end);
    printf("End of uninitialized data segment (BSS) (approximate): %p\n", (void *)bss_end);

    return 0;
}