//
//  main.cpp
//  linkedlist
//
//  Created by Terwer Green on 16/5/30.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#include <iostream>
#include "LinkedList.h"

int main(int argc, const char * argv[]) {
    
    struct Node *linkedlist = createList();
    print(linkedlist);
    
    printf("insert node\n");
    insertNode(linkedlist, "terwer");
    insertNode(linkedlist, "green");
    insertNode(linkedlist, "terwer");
    print(linkedlist);
    
    Node *node = getNode(linkedlist, 1);
    printf("get node:%s\n",node->data);
    
    printf("delete node\n");
    deleteNode(linkedlist);
    print(linkedlist);
    
    printf("delete list\n");
    deleteList(linkedlist);
    print(linkedlist);
    
    return 0;
}
