#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int fd[2];
	pipe(fd);
	pid_t pid = fork();
	
	if (pid > 0) // Parent Process
	{
		close(fd[0]); // Close read end
		int numbers[5] = {10, 20, 30, 40, 50};
		write(fd[1], numbers, sizeof(numbers)); // Send numbers
		close(fd[1]);
		wait(NULL);
	}
	else // Child Process
	{
		close(fd[1]); // Close write end
		dup2(fd[0], 0); // Redirect pipe read end to stdin
		close(fd[0]);

		int numbers[5];
		read(0, numbers, sizeof(numbers)); // Read from stdin
		
		int sum = 0;
		for (int i = 0; i < 5; i++)
		{
			sum += numbers[i];
		}
		printf("Child: Sum = %d\n", sum);
	}
	return 0;
}
