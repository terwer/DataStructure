//
//  InsertionSort.h
//  InsertionSort
//
//  Created by Terwer Green on 15/7/22.
//  Copyright (c) 2015年 Terwer Green. All rights reserved.
//

#ifndef __InsertionSort__InsertionSort__
#define __InsertionSort__InsertionSort__
#endif

#include <stdio.h>

//列表最大长度
#define MAXSIZE 100

typedef int KeyType; //关键字类型
typedef int InfoType;//其他数据项类型

//排序数据项
typedef struct {
    KeyType key; //关键字项
    InfoType otherinfo; //其它数据项
} Record; //记录类型

//排序列表
typedef struct{
    Record record[MAXSIZE + 1];//记录空间,0单元用作监视哨
    int length;//当前记录数
}RecordList;//记录表

//根据索引插入纪录到列表
void insertRecordByIndex(RecordList *L,Record record,int index);

//插入排序
void insertSort(RecordList *L);

//数据全部记录
void printRecordList(RecordList L);

