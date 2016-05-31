//
//  BinarySortTree.h
//  DataStructure
//
//  Created by yifa007 on 16/5/31.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#ifndef BinarySortTree_h
#define BinarySortTree_h

#define FALSE	0
#define TRUE	1
#define Nil 	1000

typedef int Status;

typedef struct BiNode
{
    int data;						/* 节点数据 */
    struct BiNode *lchild,*rchild;	/* 左右孩子指针 */
}BiNode, *BiTree;

/*
	当二叉排序树T中不存在关键字等于key的数据元素时，
	插入key并返回TRUE,否则返回FALSE
 */
Status InsertBST(BiTree *T,int key);

int PrintTree(BiTree T);

#endif /* BinarySortTree_h */
