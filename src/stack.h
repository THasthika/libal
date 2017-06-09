#ifndef AL_STACK_H
#define AL_STACK_H 1

#include <stdlib.h>

typedef struct _AL_Stack {
        unsigned long capacity;
        size_t item_size;
        size_t inc_size;
        void (*destroy)(void *data);
        void *bottom;
        void *top;
} AL_Stack;

void AL_stack_create(AL_Stack *stack, size_t item_size, size_t inc_size, void (*destroy)(void *data));
void AL_stack_destroy(AL_Stack *stack);
void AL_stack_push(AL_Stack *stack, void *data);
void AL_stack_pop(AL_Stack *stack, void *data);
unsigned int AL_stack_size(AL_Stack *stack);

#define AL_stack_peak(stack) (stack->top);

#endif // AL_STACK_H
