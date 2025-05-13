#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[]) {
    int i;
    printf("Selected environment variables:\n");

    for (i = 0; envp[i] != NULL; i++) {
        if (strncmp(envp[i], "SHELL=", 6) == 0) {
            printf("SHELL: %s\n", envp[i] + 6);
        } else if (strncmp(envp[i], "PATH=", 5) == 0) {
            printf("PATH: %s\n", envp[i] + 5);
        } else if (strncmp(envp[i], "USERNAME=", 9) == 0) {
            printf("USERNAME: %s\n", envp[i] + 9);
        } else if (strncmp(envp[i], "USER=", 5) == 0) {
            printf("USER: %s\n", envp[i] + 5);
        }
    }

    printf("\nOther environment variables:\n");

    for (i = 0; envp[i] != NULL; i++) {
        if (
            strncmp(envp[i], "SHELL=", 6) != 0 &&
            strncmp(envp[i], "PATH=", 5) != 0 &&
            strncmp(envp[i], "USERNAME=", 9) != 0 &&
            strncmp(envp[i], "USER=", 5) != 0
        ) {
            char *eq = strchr(envp[i], '=');
            if (eq != NULL) {
                printf("Key: %.*s, Value: %s\n", (int)(eq - envp[i]), envp[i], eq + 1);
            }
        }
    }

    return 0;
}