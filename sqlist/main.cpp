//
//  main.cpp
//  sqlist
//
//  Created by Terwer Green on 16/5/30.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#include <iostream>
#include "SqList.h"

using namespace std;

int main(int argc, const char * argv[]) {
    SqList list;
    createList(&list);
    
    if (createList(&list)) {
        printf("create list success\n");
    }
    
    print(&list);
    
    ElemType elem;
    if (getElemByIndex(list, 4, &elem)) {
        printf("elem:%s\n",elem);
    }
    printf("begin insert value\n");
    
    if (insertElemByIndex(&list, 5, "scofield")) {
        print(&list);
    }
    
    if (deleteElemByIndex(&list,3)) {
        printf("deleteElemFromList\n");
        print(&list);
    }
    
    return 0;
}
