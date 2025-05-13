#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main() {
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    char *program3_ptr;
    off_t offset;
    char replacement[] = "PROGRAM 3";

    // Opens the README.md file in read-write mode
    fd = open("README.md", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Reads the contents of the file
    bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    buffer[bytes_read] = '\0';

    // Finds the position of "Program 3"
    program3_ptr = strstr(buffer, "Program 3");
    if (program3_ptr == NULL) {
        fprintf(stderr, "'Program 3' not found in README.md\n");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Calculates the offset from the beginning of the file
    offset = program3_ptr - buffer;

    // Moves the file offset to the beginning of "Program 3"
    if (lseek(fd, offset, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Writes the uppercase replacement
    if (write(fd, replacement, strlen(replacement)) == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Closes the file
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    printf("Successfully replaced 'Program 3' with 'PROGRAM 3' in README.md\n");

    return 0;
}