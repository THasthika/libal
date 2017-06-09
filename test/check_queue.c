#include <stdlib.h>
#include <assert.h>

#include <queue.h>

void test_ptr()
{
	int arr[] = {1, 2, 3, 4, 5, 6};

	AL_Queue *queue = (AL_Queue*) malloc(sizeof(AL_Queue));
	AL_queue_create(queue, sizeof(int*), NULL);

	int *p = arr;

	for(int i = 0; i < 6; i++) {
		AL_queue_enqueue(queue, &p);
		p += 1;
	}

	int *a = NULL;
	for(int i = 0; i < 6; i++) {
		AL_queue_dequeue(queue, &a);
		assert(arr+i == a);
	}

	AL_queue_destroy(queue);
	free(queue);
}

int main(int argc, char **argv)
{
	int arr[] = {1, 2, 3, 4, 5, 6};

	AL_Queue *queue = (AL_Queue*) malloc(sizeof(AL_Queue));
	AL_queue_create(queue, sizeof(int), NULL);

	for(int i = 0; i < 6; i++) {
		AL_queue_enqueue(queue, arr+i);
	}

	int a;
	for(int i = 0; i < 6; i++) {
		AL_queue_dequeue(queue, &a);
		assert(arr[i] == a);
	}

	AL_queue_destroy(queue);
	free(queue);

	test_ptr();
	return 0;
}
