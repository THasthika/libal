#include <stdlib.h>
#include <assert.h>

#include <queue.h>

int main(int argc, char **argv) {

	int arr[] = {1, 2, 3, 4, 5, 6};

	THB_Queue *queue = (THB_Queue*) malloc(sizeof(THB_Queue));
	THB_queue_create(queue, sizeof(int), NULL);

	for(int i = 0; i < 6; i++) {
		THB_queue_enqueue(queue, arr+i);
	}

	int a;
	for(int i = 0; i < 6; i++) {
		THB_queue_dequeue(queue, &a);
		assert(arr[i] == a);
	}

	THB_queue_destroy(queue);
	free(queue);
	return 0;
}
