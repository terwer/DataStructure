//
//  LinkedList.h
//  linkedlist
//
//  Created by Terwer Green on 16/5/30.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#ifndef LinkedList_h
#define LinkedList_h

typedef const char* ElemType;

struct Node {
    ElemType data;
    struct Node *next;
};

struct Node *createList();

void deleteNode(struct Node *prev);

struct Node *insertNode(struct Node *prev, ElemType data);

int length(struct Node *head);

void print(struct Node *head);

struct Node *getNode(struct Node *head, int i);

void deleteList(struct Node *head);

#endif
