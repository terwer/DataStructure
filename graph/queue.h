//
//  queue.h
//  graph
//
//  Created by Terwer Green on 16/5/31.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

typedef struct item_t {
    void *data;
    struct item_t *next;
} item_t;

typedef struct {
    item_t *head;
    item_t *tail;
    int size;
} queue_t;

queue_t *create_empty_queue(void);
void q_push(queue_t *Q, void *data);
void *q_pop(queue_t *Q);
void *q_peek(queue_t *Q);
int q_not_empty(queue_t *Q);
void print_queue(queue_t *Q);
