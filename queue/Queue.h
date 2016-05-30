//
//  queue.h
//  queue
//
//  Created by Terwer Green on 16/5/30.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>

/* External interface declarations */

struct Queue;
typedef struct Queue queue;
typedef char *queue_item_t;

/* Function declarations */

Queue *queue_new(void);

void queue_free(Queue*);

void queue_insert(Queue*, queue_item_t);

queue_item_t queue_remove(Queue*);

bool queue_isempty(Queue*);

#endif
