//
//  queue.m
//  queue
//
//  Created by Terwer Green on 16/5/30.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define STUBPRINTF(...) fprintf(stderr, __VA_ARGS__);

/* Internal implementation definitions */
struct queue_node
{
    queue_item_t item;
    struct queue_node *link;
};

typedef struct queue_node queue_node;

struct Queue
{
    queue_node *front;
    queue_node *rear;
};

/* Functions */

Queue *queue_new(void)
{
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void queue_free(Queue *queue)
{
    assert(queue_isempty(queue));
    free(queue);
}

void queue_insert(Queue *queue, queue_item_t item)
{
    struct queue_node *newN = (struct queue_node*)malloc(sizeof(struct queue_node));
    newN->item = item;
    if (queue->front==NULL)
    {
        queue->front = newN;
        queue->rear = newN;
    }
    else
    {
        queue->rear->link = newN;
        queue->rear = newN;
    }
}

queue_item_t queue_remove(Queue *queue)
{
    assert(!queue_isempty(queue));
    queue_node *temp = queue->front;
    queue_item_t item = temp->item;
    queue->front = queue->front->link;
    free(temp->item);
    free(temp);
    return item;
}

bool queue_isempty(Queue *queue)
{
    return queue->front == NULL;
}
