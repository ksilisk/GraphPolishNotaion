#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

Stack* push(Stack *root, char ch) {
    Stack *temp = (Stack*) malloc(sizeof(Stack));
    temp->operation = ch;
    temp->node_next = root;
    return temp;
}

Stack* pop(Stack *root, char *ch) {
    Stack *temp = root;
    *ch = temp->operation;
    root = root->node_next;
    free(temp);
    return root;
}

Stack_Num* push_num(Stack_Num *root, double num) {
    Stack_Num *temp = (Stack_Num*) malloc(sizeof(Stack_Num));
    temp->number = num;
    temp->node_next = root;
    return temp;
}

Stack_Num* pop_num(Stack_Num *root, double *num) {
    Stack_Num *temp = root;
    *num = temp->number;
    root = root->node_next;
    free(temp);
    return root;
}
