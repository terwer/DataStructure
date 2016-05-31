//
//  Tree.h
//  DataStructure
//
//  Created by Terwer Green on 16/5/31.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#ifndef Tree_h
#define Tree_h

/*二叉树的二叉链表结构*/
typedef struct BiTNode{
    int data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

/*平衡二叉树*/
typedef struct AVLNode{
    int hight;            /*树高度*/
    int data;
    AVLNode *lchild,*rchild;
}AVLNode, *AVLTree;

/*红黑树*/
typedef enum Color{
    RED = 0,
    BLACK = 1
}Color;

typedef struct BRNode{
    struct BRNode* parent;
    struct BRNode* lchild;
    struct BRNode* rchild;
    int value;
    Color color;
}BRNode, *BRTree;

void preOrderTraverse(BiTree T);
void inOrderTraverse(BiTree T);
void preOrderTraverse(AVLTree T);
void inOrderTraverse(AVLTree T);
void preOrderTraverse(BRTree T);
void inOrderTraverse(BRTree T);
bool Delete(BiTree &p);

/*二叉查找树*/
bool BSTInsert(BiTree &p, int element);
void createBST(BiTree &T, int *a, int len);
bool SearchBST(BiTree T, int data, BiTree f, BiTree &p);
bool InsertBST(BiTree T, int data);
bool DeleteBST(BiTree &T, int data);

/*平衡二叉树*/
void R_Rotate(AVLTree &p);
void L_Rotate(AVLTree &p);
void LeftBalance(AVLTree &p);
void RightBalance(AVLTree &p);
void InsertAVL(AVLTree &p, int data);
void AVLRemove(AVLTree &p, int data);
AVLTree FindNode(AVLTree p, int data);
void CreateAVL(AVLTree &p, int *a, int len);

/*红黑树*/
void BRTreeInsert(BRTree &brTree, int value);
void CreateBRTree(BRTree &T, int *a, int len);

#endif /* Tree_h */
