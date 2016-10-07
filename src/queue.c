#include <THB/queue.h>

#include <THB/list.h>

#include <stdlib.h>
#include <string.h>

void queue_enqueue(Queue *queue, void *data) {
        if(queue == NULL) return;
        list_insert_after(queue, NULL, data);
}

void queue_dequeue(Queue *queue, void *data) {
        if(queue == NULL) return;
        ListItem *item = queue->tail;
        list_remove(queue, item, data);
}
