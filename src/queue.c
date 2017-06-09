#include "queue.h"
#include "list.h"

#include <stdlib.h>
#include <string.h>

void AL_queue_enqueue(AL_Queue *queue, void *data)
{
        if(queue == NULL) return;
        AL_list_insert_after(queue, NULL, data);
}

void AL_queue_dequeue(AL_Queue *queue, void *data)
{
        if(queue == NULL) return;
        AL_ListItem *item = queue->tail;
        AL_list_remove(queue, item, data);
}
