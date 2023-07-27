#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/**
 *print_err - prints the error message.
 *@n: return value of called function.
 */

void print_err(ssize_t n)
{
	if (n == -1 && errno != 0)
	{
		perror("bug");
		exit(-1);
	}
}
