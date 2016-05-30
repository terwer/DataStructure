//
//  SqList.cpp
//  DataStructure
//
//  Created by Terwer Green on 16/5/30.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#include <stdio.h>
#include "SqList.h"

Status createList(SqList *list)
{
    if (!list) {
        return ERROR;
    }
    
    for (int i = 0; i < MAX_SIZE; i++) {
        list->elem[i] = "green";
        list->length = i;
        if (i == MAX_SIZE -3) {
            list->elem[i] = "terwer";
        }
    }
    return OK;
}

Status print(SqList *list)
{
    if (!list) {
        return ERROR;
        
    }
    else{
        for (int i = 0; i < list->length; i++) {
            printf("element: %s\n",list->elem[i]);
        }
        
        return OK;
    }
}

Status getElemByIndex(SqList list, int idx, ElemType *elem)
{
    
    if(idx < 0|| idx > list.length-1)
    {
        printf("list.length = %d",list.length);
        printf("beyong scope\n");
        return ERROR;
    }else{
        *elem = list.elem[idx];
        return OK;
    }
}

Status insertElemByIndex(SqList *list,int idx, ElemType elem)
{
    if (idx < 0|| idx > list->length) {
        return ERROR;
    }else{
        //list.item[idx] = *elem;
        //list.item[idx +1];
        ++list->length;
        for (int j = idx; j<list->length; j++) {
            //printf("list.value[list.length]=%s\n",list->elem[list->length]);
            list->elem[list->length] = list->elem[--list->length];
        }
        list->elem[idx] = elem;
        return OK;
    }
}

Status deleteElemByIndex(SqList *list,int idx)
{
    printf("list->length:%d\n",list->length);
    if (idx < 0|| idx >= list->length) {
        printf("index overflow");
        return ERROR;
    }
    //list->elem[idx] = NULL;
    for (int i = idx; i < list->length; i++) {
        int j = i+1;
        
        list->elem[i] = list->elem[j];
        if (i == list->length -1) {
            list->elem[i] = NULL;
        }
    }
    list->length--;
    printf("list->length:%d\n",list->length);
    return OK;
}