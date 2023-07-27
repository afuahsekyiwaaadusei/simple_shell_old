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
 *@ac: count of program arguments.
 *@av: array of program arguements.
 *@env: program environment.
 *
 *Return: always 0.
 */

int main(int ac, char **av, char **env)
{
	char *line = NULL, **argv, *dup_str, buf[] = "cisfun$ ";
	ssize_t nread, nwrite;
	size_t n = 0;
	pid_t pid;

	if (ac > 1 && av[1] != NULL)
		return (-1);
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
			if ((execve(argv[0], argv, env)) == -1)
				perror("./shell");
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
