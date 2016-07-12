#include <THB/queue.h>

#include <THB/list.h>

#include <stdlib.h>
#include <string.h>

void THB_queue_enqueue(THB_Queue *queue, void *data) {
        if(queue == NULL) return;
        THB_list_insert_after(queue, NULL, data);
}

void THB_queue_dequeue(THB_Queue *queue, void *data) {
        if(queue == NULL) return;
        THB_ListItem *item = queue->tail;
        THB_list_remove(queue, item, data);
}
