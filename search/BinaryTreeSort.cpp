//
//  BinarySortTree.cpp
//  search
//
//  Created by Terwer Green on 16/5/31.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BinaryTreeSort.h"

/* 操作结果：构造空二叉树T */
void InitBiTree(BiTree T)
{
	T->lchild = NULL;
	T->rchild = NULL;
}
/* 算法6.4：按先序次序输入二叉树中结点的值(可为字符型或整型，在主程中定义)，
   构造二叉链表表示的二叉树T。变量Nil表示空(子)树。*/
int CreateBiTree(BiTree T,int data)
{ 
	// int number;
	// printf("\nPlease enter a int( < 1000):");
	// scanf("%d",&number); 					// 输入结点的值
	if(data > 2147483647) 						// 结点的值为空
	{
		return 0;
	}
	else 									// 结点的值不为空
	{ 
		if(T == NULL)		// 指针为空开辟新空间赋值
		{
			T = (BiTree)malloc(sizeof(BiNode)); 	// 生成根结点
			InitBiTree(T);
			if(!T)
			{
				return 0;
			}		
			T->data = data; 
			return 1;
		}
		else
		{
			T->data = data;
			return 1;
		}
					// 将值赋给T所指结点
//		CreateBiTree(T->lchild); 			// 递归构造左子树
//		CreateBiTree(T->rchild); 			// 递归构造右子树
	}
}

// 初始条件：二叉树T存在。操作结果：销毁二叉树T
void DestroyBiTree(BiTree T)
{
	if( T ) 								// 非空树
	{ 
		DestroyBiTree(T->lchild); 			// 递归销毁左子树，如无左子树，则不执行任何操作
		DestroyBiTree(T->rchild); 				// 递归销毁右子树，如无右子树，则不执行任何操作
		free(T); // 释放根结点
		T = NULL; // 空指针赋0
	}
}


/* 
	递归查找二叉排序树T中是否存在key，
	指针f指向T的双亲，其初始调用值为NULL
	若查找成功，则指针p指向该数据元素的节点，并返回TRUE
	否则指针p指向查找路径上访问的最后一个节点并返回FALSE
 */
Status SearchBST(BiTree T,int key,BiTree f,BiTree *p)
{
	if(!T)												/* 查找不成功 */
	{
		*p = f;
		return FALSE;
	}
	else if(key == T->data)								/* 查找成功 */
	{
		*p = T;
		return TRUE;
	}
	else if(key < T->data)
	{
		return SearchBST( T->lchild, key, T, p);		/* 在左子树继续查找 */
	}
	else
	{
		return SearchBST( T->rchild, key, T, p);
	}
}

/*
	当二叉排序树T中不存在关键字等于key的数据元素时，
	插入key并返回TRUE,否则返回FALSE
*/
Status InsertBST(BiTree *T,int key)
{
	BiTree p,s;
	if(!SearchBST( *T, key, NULL, &p))	/* 查找不成功 */
	{
		s = (BiTree)malloc(sizeof(BiNode));
		s->data = key;
		s->lchild = s->rchild = NULL;
		if( !p )
		{
			*T = s;					/* 插入s为新的结点 */
		}
		else if(key < p->data)
		{
			p->lchild = s;			/* 插入s为左孩子 */
		}
		else
		{
			p->rchild = s;			/* 插入s为右孩子 */
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/* 若二叉树T中存在关键字等于key的数据元素时，删除该结点 */
Status DeleteBST(BiTree *T, int key)
{
	if(!*T)	/* 不存在关键字等于key的数据元素 */
	{
		return FALSE;
	}
    return TRUE;
}


int PrintTree(BiTree T)
{
	if(T == NULL)
	{
		printf("This is a void tree!\n");
		return FALSE;
	}
	else
	{
		printf("Tree node data is:%4d\n",T->data);
		PrintTree(T->lchild);
		PrintTree(T->rchild);
        return TRUE;
	}
}

