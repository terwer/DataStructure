//
//  main.cpp
//  search
//
//  Created by Terwer Green on 16/5/31.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#include <iostream>
#include "BinaryTreeSearch.h"

int main(int argc, const char * argv[])
{
    int i;
    int a[10] = { 62, 88, 58, 47, 35, 73, 51, 99, 37, 93};
    BiTree T = NULL;
    
    for(i = 0;i < 10;i++)
    {
        InsertBST(&T,a[i]);
    }
    PrintTree(T);
    
    //	BiNode myTree;
    
    //	InitBiTree(&myTree);
    //	CreateBiTree(&myTree,50);
    //	CreateBiTree(myTree.lchild,88);
    //	CreateBiTree(myTree.rchild,60);
    //	PrintTree(&myTree);
    
    //HashSearch
    /*
    int i;
    int mykey = 1;
    HashTable myHashTable;
    
    srand((unsigned)time(NULL));
    
    InitHashTable(&myHashTable);
    
    for(i = 0;i < m;i++)
    {
        InsertHash(&myHashTable,rand() % 100);
    }
    
    if(SearchHash(myHashTable,8,&mykey) == SUCCESS)
    {
        printf("The hash table search result is :%d\n",mykey);
        printf("The search result myHashTable.elem[%d] = %d\n",mykey,myHashTable.elem[mykey]);
    }
    else
    {
        printf("Unsuccess!\n");
    }
    */
     
    return 0;
}

