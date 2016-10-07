#include "stack.h"

#include <stdlib.h>
#include <string.h>

void THB_stack_create(THB_Stack *stack, size_t size, size_t inc_size, void (*destroy)(void *data)) {
        stack->size = size;
        stack->inc_size = inc_size;
        stack->capacity = stack->inc_size;
        stack->destroy = destroy;
        stack->bottom = malloc(stack->size * stack->capacity);
        stack->top = stack->bottom - stack->size;
}

void THB_stack_destroy(THB_Stack *stack) {
        if(stack->destroy != NULL) {
                while(stack->top >= stack->bottom) {
                        stack->destroy(stack->top);
                        stack->top -= stack->size;
                }
        }
        free(stack->bottom);
        stack->bottom = 0;
        stack->top = 0;
        stack->size = 0;
        stack->destroy = 0;
        stack->capacity = 0;
        stack->inc_size = 0;
}

void THB_stack_push(THB_Stack *stack, void *data) {
        stack->top += stack->size;
        if(THB_stack_size(stack) > stack->capacity) {
                stack->capacity += stack->inc_size;
                stack->bottom = realloc(stack->bottom, stack->size * stack->capacity);
        }
        memcpy(stack->top, data, stack->size);
}

void THB_stack_pop(THB_Stack *stack, void *data) {
        if(stack->top < stack->bottom) return;
        memcpy(data, stack->top, stack->size);
        stack->top -= stack->size;
        if(THB_stack_size(stack) < stack->capacity - stack->inc_size) {
                stack->capacity -= stack->inc_size;
                stack->bottom = realloc(stack->bottom, stack->size * stack->capacity);
        }
}

unsigned int THB_stack_size(THB_Stack *stack) {
        return (stack->top - stack->bottom + stack->size) / stack->size;
}
