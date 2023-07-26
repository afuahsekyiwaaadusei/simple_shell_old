#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/**
 *_argv - creates an array of pointers
 *@line: string to be broken into pointers. 
 *
 *Return: an array of pointers
 */

char **_argv(char *line)
{
	char **argv, *dup_str, *token;
	size_t arg_count;
	int count = 0;

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
	free(dup_str);
	return (argv);
}
