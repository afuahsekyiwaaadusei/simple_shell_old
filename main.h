#ifndef SHELL_H
#define SHELL_H
#include <unistd.h>
void print_err(ssize_t n);
char *str_dup(char *str);
int get_arg_no(char *str);
#endif
