#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct {
    char *cmd;
    char *args[10];
} Command;


void	execute_commands(Command commands[], int num_commands, char *input_file,
		char *output_file)
{
	int		i;
	int		num_pipes;
	int		pipes[num_pipes][2];
	pid_t	pid;
	int		input_fd;
	int		output_fd;

	num_pipes = num_commands - 1;
	// Create the pipes
	for (i = 0; i < num_pipes; ++i)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	for (i = 0; i < num_commands; ++i)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			// Child process
			if (i == 0)
			{
				// First command: read from input_file
				input_fd = open(input_file, O_RDONLY);
				if (input_fd == -1)
				{
					perror("open input_file");
					exit(EXIT_FAILURE);
				}
				dup2(input_fd, STDIN_FILENO);
				close(input_fd);
			}
			else
			{
				// Read from previous pipe
				dup2(pipes[i - 1][0], STDIN_FILENO);
			}
			if (i == num_commands - 1)
			{
				// Last command: write to output_file
				output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC,
						0644);
				if (output_fd == -1)
				{
					perror("open output_file");
					exit(EXIT_FAILURE);
				}
				dup2(output_fd, STDOUT_FILENO);
				close(output_fd);
			}
			else
			{
				// Write to next pipe
				dup2(pipes[i][1], STDOUT_FILENO);
			}
			// Close all pipe file descriptors
			for (int j = 0; j < num_pipes; ++j)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
			}
			// Execute command
			execvp(commands[i].cmd, commands[i].args);
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	// Parent process: close all pipe file descriptors
	for (i = 0; i < num_pipes; ++i)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	// Wait for all child processes to finish
	for (i = 0; i < num_commands; ++i)
	{
		wait(NULL);
	}
}

int	main(void)
{
	Command	commands[3] = {{"ls", {"ls", NULL}}, {"grep", {"grep", "main",
			NULL}}, {"wc", {"wc", "-l", NULL}}};

	execute_commands(commands, 3, "input.txt", "output.txt");
	return (0);
}
