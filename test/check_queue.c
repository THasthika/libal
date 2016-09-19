#include <stdlib.h>
#include <assert.h>

#include <THB/queue.h>

int main(int argc, char **argv) {

	int arr[] = {1, 2, 3, 4, 5, 6};

	Queue *queue = (Queue*) malloc(sizeof(Queue));
	queue_create(queue, sizeof(int), NULL);

	for(int i = 0; i < 6; i++) {
		queue_enqueue(queue, arr+i);
	}

	int a;
	for(int i = 0; i < 6; i++) {
		queue_dequeue(queue, &a);
		assert(arr[i] == a);
	}

	queue_destroy(queue);
	free(queue);
	return 0;
}
