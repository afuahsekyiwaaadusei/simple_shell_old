#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

/**
 *main - a program that prints "$ ",
 *wait for the user to enter a command, and executes it.
 *
 *Return: always 0.
 */

int main(void)
{
	char *line = NULL, **argv, *dup_str;
	char buf[] = "cisfun$ ";
	ssize_t nread, nwrite;
	size_t n = 0;
	pid_t pid;

	nwrite = write(STDOUT_FILENO, buf, sizeof(buf));
	print_err(nwrite);
	nread = getline(&line, &n, stdin);
	print_err(nread);
	while (nread != -1)
	{
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		pid = fork();
		print_err(pid);
		if (pid == 0)
		{
			nread = -1;
			dup_str = str_dup(line);
			argv = _argv(dup_str);
			if ((execve(argv[0], argv, NULL)) == -1)
			{
				perror("./shell");
			}
		}
		else
		{
			wait(NULL);
			free(line);
			line = NULL;
			nwrite = write(STDOUT_FILENO, buf, sizeof(buf));
			print_err(nwrite);
			nread = getline(&line, &n, stdin);
			print_err(nread);
		}
	}
	free(line);
	free(argv);
	free(dup_str);
	return (0);
}
