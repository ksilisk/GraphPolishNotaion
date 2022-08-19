#ifndef SRC_MATHS_H_
#define SRC_MATHS_H_

double calculate(char *result, double x);
double execute_binary(double first, double second, char operation);
char* add_digit(char *number, char digit, int count_digit);
int is_operator(char ch);
double execute_unary(double num, char operation);
void clean_number(char *number);
int is_number(char *num);

#endif  //  SRC_MATHS_H_
