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
 *@av: array of program arguments
 *@env: array of program environment
 *
 *Return: always 0.
 */

int main(void)
{
	char *line = NULL;
	char **argv;
	char buf[] = "cisfun$ ";
	ssize_t nread, nwrite;
	size_t n = 0, arg_count;
	int count = 0;
	pid_t pid;
	char *dup_str, *token;

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
			arg_count = get_arg_no(line);
			arg_count++;
			argv = malloc(sizeof(char *) * arg_count);
			dup_str = str_dup(line);
			token = strtok(dup_str, " ");
			while (token)
			{
				argv[count] = token;
				token = strtok(NULL, " ");
				count++;
			}
			argv[count] = NULL;
			count = execve(argv[0], argv, NULL);
			if (count == -1)
			{
				perror("./shell");
			}
		}
		else
		{
			wait(NULL);
			free(line);
			free(argv);
			free(dup_str);
			
			line = NULL;
			nwrite = write(STDOUT_FILENO, buf, sizeof(buf));
			print_err(nwrite);
			nread = getline(&line, &n, stdin);
			print_err(nread);
		}
	}
	/*free(line);
	free(argv);
	free(dup_str);*/
	return (0);
}
