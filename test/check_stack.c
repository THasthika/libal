#include <stdlib.h>
#include <assert.h>

#include <THB/stack.h>

int main(int argc, char **argv) {

	int arr[] = {1, 2, 3, 4, 5, 6};

	Stack *stack = (Stack*) malloc(sizeof(Stack));
	stack_create(stack, sizeof(int), 10, NULL);

	for(int i = 0; i < 6; i++) {
		stack_push(stack, arr+i);
	}

	int a;
	for(int i = 0; i < 6; i++) {
		stack_pop(stack, &a);
		assert(arr[5-i] == a);
	}

	stack_destroy(stack);
	free(stack);
	return 0;
}
