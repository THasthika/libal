#ifndef STACK_H
#define STACK_H 1

#include <stdlib.h>

typedef struct _Stack {
        unsigned long capacity;
        size_t size;
        size_t inc_size;
        void (*destroy)(void *data);
        void *bottom;
        void *top;
} Stack;

void stack_create(Stack *stack, size_t size, size_t inc_size, void (*destroy)(void *data));
void stack_destroy(Stack *stack);
void stack_push(Stack *stack, void *data);
void stack_pop(Stack *stack, void *data);
unsigned int stack_size(Stack *stack);

#define stack_peak(stack) (stack->top);

#endif // STACK_H
