#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
    }
    else if (pid == 0) {
        printf("Child process created\n");
        printf("Child process ID: %d\n", getpid());
        printf("Parent process ID: %d\n", getppid());
    }
    else {
        wait(NULL);
		printf("Parent process ID: %d\n", getpid());
    }

    return 0;
}
