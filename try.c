#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main() {
    char *myString = "/bin/ls -l /tmp";
    /*char *length = str_dup(myString);*/
    char **argv = _argv(myString);
    int i = 0;
    while (argv[i] != NULL) 
    {
	    printf("argv[%d] = %s\n", i, *argv);
	    i++;
    }

   /* printf("The string: %s\n", argv[1]);
    printf("The string: %s\n", argv[1]);
    printf("The string: %s\n", argv[2]);*/
    free(argv);
    return 0;
}
