// Unidirectional pipe
#include<stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int p1[2]; // Pipe: Parent → Child
	pipe(p1);
	pid_t pid = fork();

	if (pid > 0) // Parent Process
	{
		close(p1[0]); // Close read end
		int numbers[5] = {10, 20, 30, 40, 50};
		write(p1[1], numbers, sizeof(numbers)); // Send numbers to child
		close(p1[1]);
		wait(NULL);
	}
	else // Child Process
	{
		close(p1[1]); // Close write end
		int numbers[5];
		read(p1[0], numbers, sizeof(numbers)); // Receive numbers
		
		int sum = 0;
		for (int i = 0; i < 5; i++)
		{
			sum += numbers[i];
		}
		printf("Child: Sum of numbers = %d\n", sum);
		close(p1[0]);
	}
	return 0;
}
