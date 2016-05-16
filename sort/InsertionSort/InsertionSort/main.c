//
//  main.c
//  InsertionSort
//
//  Created by Terwer Green on 15/7/22.
//  Copyright (c) 2015年 Terwer Green. All rights reserved.
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "InsertionSort.h"

int main() {
    
    RecordList RList;
    //初始化
    RList.length = 0;
    
    //插入纪录
    for (int i = 0; i < 10; i++) {
        int item = rand()%10;
        Record r1 = {item,i};
        insertRecordByIndex(&RList,r1,i);
    }
    printf("原始记录表:");
    printRecordList(RList);
    printf("\n");
    
    //直接插入排序
    insertSort(&RList);
    
    printf("直接插入排序后的记录表:");
    printRecordList(RList);
    printf("\n");
    
    return 0;
}