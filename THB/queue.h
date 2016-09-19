#ifndef QUEUE_H
#define QUEUE_H 1

#include <stdlib.h>

#include <THB/list.h>

typedef List Queue;

#define queue_create list_create
#define queue_destroy list_destroy

void queue_enqueue(Queue *queue, void *data);
void queue_dequeue(Queue *queue, void *data);

#endif // QUEUE_H
