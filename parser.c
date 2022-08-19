#include "stack.h"
#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int priority(char s) {
    int res = 0;
    switch (s) {
        case 'T': case '^':
            res = 5;
            break;
        case 'Y':
            res = 4;
            break;
        case '(':
            res = 1;
            break;
        case 'Q': case 'R':
            res = 4;
            break;
        case 'W': case 'E':
            res = 4;
            break;
        case '+': case '-':
            res = 2;
            break;
        case '*': case '/':
            res = 3;
            break;
    }
    return res;
}

char* parser(char *form) {
    Stack *temp; char temp_ch;
    Stack *stack_math = NULL;
    int i = 0;  // count-ер для form
    int j = 0;  // count-ер для выходной строки
    int n = 10;  // длина выходной строки
    char *result = malloc(n * sizeof(char));
    while (form[i] != '\0') {
        if (form[i] == ')') {
            while (stack_math && stack_math->operation != '(') {
                stack_math = pop(stack_math, &temp_ch);
                if (!stack_math)
                    temp_ch = '\0';
                result = add_result(result, temp_ch, j++, &n);
                result = add_result(result, ' ', j++, &n);
            }
            temp = stack_math;
            if (stack_math)
                stack_math = stack_math->node_next;
            free(temp);
        }
        result = check_math_func(form, &stack_math, result, i, &j, &n);
        if (form[i] == '+' || form[i] == '-' || form[i] == '*' || form[i] == '/' || form[i] == '^') {
            while (stack_math != NULL && (priority(stack_math->operation) > priority(form[i]) ||
                (form[i] != '^' && priority(stack_math->operation) == priority(form[i])))) {
                stack_math = pop(stack_math, &temp_ch);
                result = add_result(result, temp_ch, j++, &n);
                result = add_result(result, ' ', j++, &n);
            }
            stack_math = push(stack_math, form[i]);
        }
        i++;
    }
    while (stack_math) {
        stack_math = pop(stack_math, &temp_ch);
        result = add_result(result, temp_ch, j++, &n);
    }
    result = add_result(result, '\0', j, &n);
    return result;
}

char* add_result(char *res, char s, int index, int *len) {
    if (index == *len) {
        *len *= 2;
        char *buf = malloc(*len * sizeof(char));
        for (int i = 0; i < index; i++) {
            buf[i] = res[i];
        }
        for (int i = index; i < *len; i++) {
            buf[i] = '\0';
        }
        free(res);
        res = buf;
    }
    res[index] = s;
    return res;
}

char* check_math_func(char *form, Stack **stack_math, char *res, int i, int *j, int *n) {
    char temp = '\0';
    int flag = 0;
    if (form[i] == 's' && form[i+2] == 'n') {
        flag = 1; temp = 'Q'; }
    if (form[i] == 'c' && form[i+2] == 's') {
        flag = 1; temp = 'W'; }
    if (form[i] == 't' && form[i+2] == 'n') {
        flag = 1; temp = 'E'; }
    if (form[i] == 'c' && form[i+2] == 'g') {
        flag = 1; temp = 'R'; }
    if (form[i] == 's' && form[i+2] == 'r') {
        flag = 1; temp = 'T'; }
    if (form[i] == 'l' && form[i+1] == 'n') {
        flag = 1; temp = 'Y'; }
    if (flag) {
        *stack_math = push(*stack_math, temp);
        if (*j != 0) {
            res = add_result(res, ' ', (*j)++, n);
        }
    }
    if (form[i] == 'x') {
        res = add_result(res, 'x', (*j)++, n);
        res = add_result(res, ' ', (*j)++, n);
    }
    if (form[i] >= '0' && form[i] <= '9') {
        res = add_result(res, form[i] , (*j)++, n);
        if (!(form[i+1] >= '0' && form[i+1] <= '9'))
            res = add_result(res, ' ', (*j)++, n);
    }
    if (form[i] == '(')
        *stack_math = push(*stack_math, '(');
    return res;
}
