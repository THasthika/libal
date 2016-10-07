#include <stdlib.h>
#include <assert.h>

#include <stack.h>

int main(int argc, char **argv) {

	int arr[] = {1, 2, 3, 4, 5, 6};

	THB_Stack *stack = (THB_Stack*) malloc(sizeof(THB_Stack));
	THB_stack_create(stack, sizeof(int), 10, NULL);

	for(int i = 0; i < 6; i++) {
		THB_stack_push(stack, arr+i);
	}

	int a;
	for(int i = 0; i < 6; i++) {
		THB_stack_pop(stack, &a);
		assert(arr[5-i] == a);
	}

	THB_stack_destroy(stack);
	free(stack);
	return 0;
}
