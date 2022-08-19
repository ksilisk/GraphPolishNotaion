#ifndef SRC_STACK_H_
#define SRC_STACK_H_

typedef struct Stack {
    char operation;
    struct Stack* node_next;
} Stack;

typedef struct Stack_Num {
    double number;
    struct Stack_Num* node_next;
} Stack_Num;

Stack* push(Stack* root, char ch);
Stack* pop(Stack* root, char* ch);
Stack_Num* push_num(Stack_Num* root, double num);
Stack_Num* pop_num(Stack_Num* root, double *num);

#endif  //  SRC_STACK_H_
