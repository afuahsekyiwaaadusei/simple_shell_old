#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

/**
 *main - a program that prints "$ ",
 *wait for the user to enter a command, and executes it.
 *
 *Return: always 0.
 */

int main(void)
{
	char *line = NULL, *argv[3], buf[] = "cisfun$ ";
	ssize_t nread, nwrite;
	size_t n = 0;
	pid_t pid;
	extern char **environ;

	nwrite = write(STDOUT_FILENO, buf, sizeof(buf));
	if (nwrite == -1)
		perror("write system call");
	nread = getline(&line, &n, stdin);
	if (nread == -1)
		perror("getline function");
	while (nread != -1)
	{

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		pid = fork();
		if (pid == -1)
			perror("fork system call");
		else if (pid == 0)
		{
			nread = -1;
			argv[0] = line;
			argv[1] = NULL;
			if ((execve(argv[0], argv, environ)) == -1)
			{
				perror("./shell");
			}
		}
		else
		{
			wait(NULL);
			line = NULL;
			nwrite = write(STDOUT_FILENO, buf, sizeof(buf));
			if (nwrite == -1)
				perror("write system call");
			nread = getline(&line, &n, stdin);
			if (nread == -1)
				perror("getline function");
		}
	}

	free(line);
	return (0);
}
