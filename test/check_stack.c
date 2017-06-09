#include <stdlib.h>
#include <assert.h>

#include <stack.h>

void test_ptr()
{
	int arr[] = {1, 2, 3, 4, 5 , 6};

	AL_Stack *stack = (AL_Stack*) malloc(sizeof(AL_Stack));
	AL_stack_create(stack, sizeof(int*), 3, NULL);

	int *p = arr;

	for(int i = 0; i < 6; i++) {
		AL_stack_push(stack, &p);
		p += 1;
	}

	int *a;
	for(int i = 0; i < 6; i++) {
		AL_stack_pop(stack, &a);
		assert(&arr[5-i] == a);
	}

	AL_stack_destroy(stack);
	free(stack);
}

int main(int argc, char **argv) {

	int arr[] = {1, 2, 3, 4, 5, 6};

	AL_Stack *stack = (AL_Stack*) malloc(sizeof(AL_Stack));
	AL_stack_create(stack, sizeof(int), 10, NULL);

	for(int i = 0; i < 6; i++) {
		AL_stack_push(stack, arr+i);
	}

	int a;
	for(int i = 0; i < 6; i++) {
		AL_stack_pop(stack, &a);
		assert(arr[5-i] == a);
	}

	AL_stack_destroy(stack);
	free(stack);

	test_ptr();

	return 0;
}
