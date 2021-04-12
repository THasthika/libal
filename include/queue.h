#ifndef AL_QUEUE_H
#define AL_QUEUE_H 1

#include "common.h"

#include "list.h"

typedef AL_List AL_Queue;

#define AL_queue_create AL_list_create
#define AL_queue_destroy AL_list_destroy

void AL_queue_enqueue(AL_Queue *queue, void *data);
void AL_queue_dequeue(AL_Queue *queue, void *data);

#endif // AL_QUEUE_H
