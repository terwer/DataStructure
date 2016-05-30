//
//  SqList.h
//  DataStructure
//
//  Created by Terwer Green on 16/5/30.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#ifndef SqList_h
#define SqList_h

#define ERROR 0
#define OK 1
#define STATUS int
#define MAX_SIZE 10
typedef int Status;
typedef const char* ElemType;

typedef struct {
    ElemType elem[MAX_SIZE];
    int length;
}SqList;

Status createList(SqList *list);

Status print(SqList *list);

Status getElemByIndex(SqList list, int idx, ElemType *elem);

Status insertElemByIndex(SqList *list,int idx, ElemType elem);

Status deleteElemByIndex(SqList *list,int idx);

#endif /* SqList_h */
