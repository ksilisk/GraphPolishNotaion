#include "parser.h"
#include "maths.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

double calculate(char *result, double x) {
    int len = strlen(result);
    Stack_Num *dig_nums = NULL;
    double first; double second;
    int count_digit = 0; double temp;
    char *number = malloc(10 * sizeof(char));
    for (int i = 0; i < len; i++) {
        if (result[i] >= '0' && result[i] <= '9') {
            number = add_digit(number, result[i], count_digit);
            count_digit++;
        } else {
            if (is_number(number)) {
                dig_nums = push_num(dig_nums, atof(number));
            }
            clean_number(number);
            count_digit = 0;
            if (is_operator(result[i])) {
                if (result[i] == '+' || result[i] == '-' ||
                    result[i] == '*' || result[i] == '/' ||
                    result[i] == '^') {
                    dig_nums = pop_num(dig_nums, &first);
                    dig_nums = pop_num(dig_nums, &second);
                    temp = execute_binary(first, second, result[i]);
                    dig_nums = push_num(dig_nums, temp);
                } else {
                    dig_nums = pop_num(dig_nums, &first);
                    temp = execute_unary(first, result[i]);
                    dig_nums = push_num(dig_nums, temp);
                }
            }
            if (result[i] == 'x') {
                dig_nums = push_num(dig_nums, x);
            }
        }
    }
    dig_nums = pop_num(dig_nums, &temp);
    dig_nums = NULL;
    free(number);
    return temp;
}

double execute_binary(double first, double second, char operation) {
    double result = 0;
    switch (operation) {
        case '+':
            result = first + second;
            break;
        case '-':
            result = first - second;
            break;
        case '*':
            result = first * second;
            break;
        case '/':
            result = second / first;
            break;
        case '^':
            for (int i = 0; i < first; i++) {
                second *= second;
            }
            result = second;
            break;
    }
    return result;
}

double execute_unary(double num, char operation) {
    double result = 0;
    switch (operation) {
        case 'Q':
            result = sin(num);
            break;
        case 'W':
            result = cos(num);
            break;
        case 'E':
            result = tan(num);
            break;
        case 'R':
            result = 1.0/tan(num);
            break;
        case 'T':
            result = sqrt(num);
            break;
        case 'Y':
            result = log(num);
            break;
    }
    return result;
}

char* add_digit(char *number, char digit, int count_digit) {
    int len = strlen(number);
    if (len == count_digit) {
        char *buf = malloc(len * 2 * sizeof(char));
        for (int i = 0; i < len; i++) {
            buf[i] = number[i];
        }
        free(number);
        number = buf;
    }
    number[count_digit] = digit;
    return number;
}

void clean_number(char *number) {
    int len = strlen(number);
    for (int i = 0; i < len; i++) {
        number[i] = '\0';
    }
}

int is_operator(char ch) {
    int flag = 0;
    switch (ch) {
        case '+': case '-': case '*':
            flag = 1;
            break;
        case '/': case '^': case 'Q':
            flag = 1;
            break;
        case 'W': case 'E': case 'R':
            flag = 1;
            break;
        case 'T': case 'Y':
            flag = 1;
            break;
    }
    return flag;
}

int is_number(char *num) {
    int len = strlen(num);
    int flag = 0;
    for (int i = 0; i < len; i++) {
        if (num[i] >= '0' && num[i] <= '9') {
            flag++;
        }
    }
    return flag;
}
