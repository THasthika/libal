#ifndef THB_QUEUE_H
#define THB_QUEUE_H 1

#include <stdlib.h>

#include "list.h"

typedef THB_List THB_Queue;

#define THB_queue_create THB_list_create
#define THB_queue_destroy THB_list_destroy

void THB_queue_enqueue(THB_Queue *queue, void *data);
void THB_queue_dequeue(THB_Queue *queue, void *data);

#endif // THB_QUEUE_H
