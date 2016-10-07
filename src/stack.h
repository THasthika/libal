#ifndef THB_STACK_H
#define THB_STACK_H 1

#include <stdlib.h>

typedef struct _THB_Stack {
        unsigned long capacity;
        size_t size;
        size_t inc_size;
        void (*destroy)(void *data);
        void *bottom;
        void *top;
} THB_Stack;

void THB_stack_create(THB_Stack *stack, size_t size, size_t inc_size, void (*destroy)(void *data));
void THB_stack_destroy(THB_Stack *stack);
void THB_stack_push(THB_Stack *stack, void *data);
void THB_stack_pop(THB_Stack *stack, void *data);
unsigned int THB_stack_size(THB_Stack *stack);

#define THB_stack_peak(stack) (stack->top);

#endif // THB_STACK_H
