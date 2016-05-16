//
//  InsertionSort.c
//  InsertionSort
//
//  Created by Terwer Green on 15/7/22.
//  Copyright (c) 2015年 Terwer Green. All rights reserved.
//

#include "InsertionSort.h"

//根据索引插入纪录到列表
void insertRecordByIndex(RecordList *L,Record record,int index)
{
    printf("正在插入数据%d，其他信息%d\n",record.key,record.otherinfo);
    int i=L->length-1;
    //从L->length-1从后往前扫描
    for (; i>=index;--i) {
        L->record[i+1]=L->record[i];
    }
    L->record[index]=record;
    ++L->length;
    printf("插入后当前长度：%d\n",L->length);
}

//插入排序
void insertSort(RecordList *L)
{
    printf("开始插入排序...\n");
    
    //1、初始时刻，第一个元素本来假设是有序的
    //2、从第二个元素开始, 依次循环插入
    //3、可以将元素看成两部分，已经排好序的和尚未排序的，每次从尚未排好序的元素中取出元素和已经排好序的比较，插入到指定位置
    for (int i = 1; i < L->length; i++) {
        int j=i;
        while (j>0&&(L->record[j-1].key)>(L->record[j].key)) {
            int temp;
            temp=L->record[j-1].key;
            L->record[j-1].key=L->record[j].key;
            L->record[j].key=temp;
            --j;
        }
    }
    
    printf("排序完成\n");
}

//数据全部记录
void printRecordList(RecordList L)
{
    printf("\n关键字\t\t原始位置");
    for (int i = 0; i < L.length; i++) {
        printf("\n%d\t\t%d",L.record[i].key,L.record[i].otherinfo);
    }
}
