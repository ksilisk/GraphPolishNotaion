#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_
#include "stack.h"

int priority(char s);
char* parser(char *form);
char* add_result(char *res, char s, int index, int *len);
char* check_math_func(char *form, Stack **stack_math, char *res, int i, int *j, int *n);
double math_hh(char *a, double x);

#endif  //  SRC_PARSER_H_
