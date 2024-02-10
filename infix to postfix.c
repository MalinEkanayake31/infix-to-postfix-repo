#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// Define a structure for the stack
struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

// Create a stack with a given capacity
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Check if the stack is full
int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Push an element onto the stack
void push(struct Stack* stack, char item) {
    if (isFull(stack)) {
        printf("Stack is full\n");
        return;
    }
    stack->array[++stack->top] = item;
}

// Pop an element from the stack
char pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return '\0';
    }
    return stack->array[stack->top--];
}

// Get the precedence of an operator
int getPrecedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return -1;
}

// Convert infix expression to postfix expression
void infixToPostfix(char* infix) {
    struct Stack* stack = createStack(strlen(infix));
    if (!stack) return;

    printf("Postfix expression: ");

    for (int i = 0; infix[i]; ++i) {
        if (isalnum(infix[i])) {
            printf("%c", infix[i]);
        } else if (infix[i] == '(') {
            push(stack, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(stack) && stack->array[stack->top] != '(') {
                printf("%c", pop(stack));
            }
            if (!isEmpty(stack) && stack->array[stack->top] != '(') {
                printf("Invalid expression\n");
                return;
            } else {
                pop(stack);
            }
        } else {
            while (!isEmpty(stack) && getPrecedence(infix[i]) <= getPrecedence(stack->array[stack->top])) {
                printf("%c", pop(stack));
            }
            push(stack, infix[i]);
        }
    }

    while (!isEmpty(stack)) {
        printf("%c", pop(stack));
    }

    printf("\n");

    free(stack->array);
    free(stack);
}

int main() {
    char infix[MAX_SIZE];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix);

    return 0;
}
