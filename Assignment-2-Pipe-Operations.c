#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    int choice;
    printf("1. Bidirectional Pipe\n");
    printf("2. Unidirectional Pipe\n");
    printf("3. Sort + Uniq using Pipe\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1: // Bidirectional pipe
    {
        int fd[2];
        pipe(fd);
        pid_t pid = fork();

        if (pid > 0)
        {
            close(fd[0]);
            int numbers[5] = {10, 20, 30, 40, 50};
            write(fd[1], numbers, sizeof(numbers));
            close(fd[1]);
            wait(NULL);
        }
        else
        {
            close(fd[1]);
            dup2(fd[0], 0);
            close(fd[0]);

            int numbers[5];
            read(0, numbers, sizeof(numbers));

            int sum = 0;
            for (int i = 0; i < 5; i++)
                sum += numbers[i];

            printf("Child: Sum = %d\n", sum);
        }
        break;
    }

    case 2: // Unidirectional Pipe
    {
        int p1[2];
        pipe(p1);
        pid_t pid = fork();

        if (pid > 0)
        {
            close(p1[0]);
            int numbers[5] = {10, 20, 30, 40, 50};
            write(p1[1], numbers, sizeof(numbers));
            close(p1[1]);
            wait(NULL);
        }
        else
        {
            close(p1[1]);
            int numbers[5];
            read(p1[0], numbers, sizeof(numbers));

            int sum = 0;
            for (int i = 0; i < 5; i++)
                sum += numbers[i];

            printf("Child: Sum = %d\n", sum);
            close(p1[0]);
        }
        break;
    }

    case 3: // sort and uniq using pipe
    {
        int fd[2];
        pid_t pid;

        int filedes = open("file1", O_RDONLY);
        if (filedes < 0)
        {
            perror("open");
            exit(1);
        }

        dup2(filedes, STDIN_FILENO);
        close(filedes);

        if (pipe(fd) == -1)
        {
            perror("pipe");
            exit(1);
        }

        pid = fork();

        if (pid == 0)
        {
            // Child → sort
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);

            execl("/usr/bin/sort", "sort", (char *)NULL);
            perror("sort failed");
            exit(1);
        }
        else if (pid > 0)
        {
            // Parent → uniq
            dup2(fd[0], STDIN_FILENO);
            close(fd[1]);
            close(fd[0]);

            execl("/usr/bin/uniq", "uniq", (char *)NULL);
            perror("uniq failed");
            exit(1);
        }
        else
        {
            perror("fork");
            exit(1);
        }

        break;
    }

    default:
        printf("Invalid choice!\n");
    }
