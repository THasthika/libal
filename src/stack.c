#include "stack.h"

#include <stdlib.h>
#include <string.h>

void AL_stack_create(AL_Stack *stack, size_t item_size, size_t inc_size, void (*destroy)(void *data))
{
    stack->item_size = item_size;
    stack->inc_size = inc_size;
    stack->capacity = stack->inc_size;
    stack->destroy = destroy;
    stack->bottom = malloc(stack->item_size * stack->capacity);
    stack->top = stack->bottom - stack->item_size;
}

void AL_stack_destroy(AL_Stack *stack)
{
    if(stack->destroy != NULL) {
        while(stack->top >= stack->bottom) {
            stack->destroy(stack->top);
            stack->top -= stack->item_size;
        }
    }
    free(stack->bottom);
    stack->bottom = 0;
    stack->top = 0;
    stack->item_size = 0;
    stack->destroy = 0;
    stack->capacity = 0;
    stack->inc_size = 0;
}

void AL_stack_push(AL_Stack *stack, void *data)
{
    stack->top += stack->item_size;
    if(AL_stack_size(stack) > stack->capacity) {
        stack->capacity += stack->inc_size;
        size_t offset = stack->top - stack->bottom;
        stack->bottom = realloc(stack->bottom, stack->item_size * stack->capacity);
        stack->top = stack->bottom + offset;
    }
    memcpy(stack->top, data, stack->item_size);
}

void AL_stack_pop(AL_Stack *stack, void *data)
{
    if(stack->top < stack->bottom) return;
    memcpy(data, stack->top, stack->item_size);
    stack->top -= stack->item_size;
    if(AL_stack_size(stack) < stack->capacity - stack->inc_size) {
        stack->capacity -= stack->inc_size;
        size_t offset = stack->top - stack->bottom;
        stack->bottom = realloc(stack->bottom, stack->item_size * stack->capacity);
        stack->top = stack->bottom + offset;
    }
}

size_t AL_stack_size(AL_Stack *stack)
{
    return (stack->top - stack->bottom + stack->item_size) / stack->item_size;
}
