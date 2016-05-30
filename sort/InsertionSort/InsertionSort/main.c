//
//  main.c
//  InsertionSort
//
//  Created by Terwer Green on 15/7/22.
//  Copyright (c) 2015年 Terwer Green. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "InsertionSort.h"

int main() {
    
    RecordList recordList;
    //初始化
    recordList.length = 0;
    
    //插入纪录
    for (int i = 0; i < 10; i++) {
        int item = rand() % 10;
        Record record = {item,i};
        insertRecordByIndex(&recordList,record,i);
    }
    printf("原始记录表:");
    printRecordList(recordList);
    printf("\n");
    
    //直接插入排序
    insertSort(&recordList);
    
    printf("直接插入排序后的记录表:");
    printRecordList(recordList);
    printf("\n");
    
    return 0;
}