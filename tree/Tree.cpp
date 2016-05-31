//
//  Tree.cpp
//  DataStructure
//
//  Created by Terwer Green on 16/5/31.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include "Tree.h"

bool BSTInsert(BiTree &p, int element)
{
    if(NULL == p){/*空树*/
        p = (BiTree)malloc(sizeof(BiTNode));
        p->data = element;
        p->lchild = p->rchild = NULL;
        return true;
    }
    if(element == p->data)
        return false;
    if(element < p->data)
        return BSTInsert(p->lchild,element);
    return BSTInsert(p->rchild,element);
}

void createBST(BiTree &T, int *a, int len)
{
    T = NULL;
    int i;
    for(i = 0; i<len; i++){
        BSTInsert(T,a[i]);
    }
}

void preOrderTraverse(BiTree T)
{
    if(T){
        std::cout << T->data << " ";
        preOrderTraverse(T->lchild);
        preOrderTraverse(T->rchild);
    }
}

void preOrderTraverse(AVLTree T)
{
    if(T){
        std::cout << T->data << " ";
        preOrderTraverse(T->lchild);
        preOrderTraverse(T->rchild);
    }
}

void preOrderTraverse(BRTree T)
{
    if(T){
        std::cout << T->value << " ";
        preOrderTraverse(T->lchild);
        preOrderTraverse(T->rchild);
    }
}

void inOrderTraverse(BiTree T)
{
    if(T){
        inOrderTraverse(T->lchild);
        std::cout << T->data << " ";
        inOrderTraverse(T->rchild);
    }
}
void inOrderTraverse(AVLTree T)
{
    if(T){
        inOrderTraverse(T->lchild);
        std::cout << T->data << " ";
        inOrderTraverse(T->rchild);
    }
}

void inOrderTraverse(BRTree T)
{
    if(T){
        inOrderTraverse(T->lchild);
        std::cout << T->value << " ";
        std::cout << (T->color ? 'B' : 'R') << " ";
        inOrderTraverse(T->rchild);
    }
}

/*递归查找二叉树T中是否存在data*/
/*指针f指向T的双亲，其初始调用值为NULL*/
/*若查找成功，则指针p指向该数据元素结点，并返回TRUE*/
/*否则指针p指向查找路径上访问的最后一个结点，并返回FALSE*/
bool SearchBST(BiTree T, int data, BiTree f, BiTree &p)
{
    if(!T){
        p = f;
        return false;
    }
    else if(data == T->data){
        p = T;
        return true;
    }
    else if(data < T->data)
        return SearchBST(T->lchild,data,T,p);
    else
        return SearchBST(T->rchild,data,T,p);
}

/*当二叉树T中不存在关键字等于data的数据时*/
/*插入key并返回TRUE，否则返回FALSE*/
bool InsertBST(BiTree T, int data)
{
    BiTree p,s;
    if(!SearchBST(T,data,NULL,p)){
        s = (BiTree)malloc(sizeof(BiTNode));
        s->data = data;
        s->lchild = s->rchild = NULL;
        if(!p)
            T = s;
        else if(data < p->data)
            p->lchild = s;
        else
            p->rchild = s;
        return true;
    }
    else
        return false;
}

/*若二叉排序树T中存在关键字等于data的数据元素时，则删除该数据元素结点*/
/*并返回TRUE，否则返回FALSE*/
bool DeleteBST(BiTree &T, int data)
{
    if(!T)
        return false;
    else{
        if(data == T->data)
            return Delete(T);
        else if(data < T->data)
            return DeleteBST(T->lchild,data);
        else
            return DeleteBST(T->rchild,data);
    }
}

bool Delete(BiTree &p)
{
    BiTree q, s;
    if(p->rchild == NULL){
        q = p;
        p = p->lchild;
        free(q);
    }
    else if(p->lchild == NULL){
        q = p;
        p = p->rchild;
        free(q);
    }
    else{
        q = p;
        s = p->lchild;
        while(s->rchild){      /*向右到尽头，找待删除结点的前驱*/
            q = s;
            s = s->rchild;
        }
        p->data = s->data;   /*s指向被删结点的直接前驱，被删除结点前驱的值取代被删除结点的值*/
        if(q != p)
            q->rchild = s->lchild;  /*重建右子树*/
        else
            q->lchild = s->lchild;  /*重建左子树*/
        free(s);
    }
    return true;
}

/*平衡二叉树*/

int Max(int lhs, int rhs)
{
    return lhs>rhs ? lhs : rhs;
}

/*返回树高，空节点为-1，叶节点为0*/
int Hight(AVLTree p)
{
    if(p)
        return p->hight;
    return -1;
}
/*节点插入在左子树的左儿子中造成失衡*/
/*右旋操作,顺时针*/
void R_Rotate(AVLTree &p)
{
    AVLTree lchild = p->lchild;
    p->lchild = lchild->rchild;    /*旋转节点左孩子的右孩子成为旋转结点左孩子*/
    lchild->rchild = p;            /*旋转节点成为旋转结点左孩子的右孩子*/
    p = lchild;                    /*旋转节点的左孩子顶部节点成为树根*/
    
    p->rchild->hight = Max(Hight(p->rchild->lchild),Hight(p->rchild->rchild))+1; /*更新原树根高度*/
    p->hight = Max(Hight(p->lchild),Hight(p->rchild))+1;                           /*更新现树根高度*/
}

/*节点插入右子树的右儿子造成失衡*/
/*左旋操作，逆时针*/
void L_Rotate(AVLTree &p)
{
    AVLTree rchild = p->rchild;
    p->rchild = rchild->lchild;    /*旋转节点右孩子的左孩子成为旋转节点的右孩子*/
    rchild->lchild = p;            /*旋转节点成为旋转节点右孩子的左孩子*/
    p = rchild;                    /*旋转节点右孩子顶部节点成为树根*/
    
    p->lchild->hight = Max(Hight(p->lchild->lchild),Hight(p->lchild->rchild))+1; /*更新原树根高度*/
    p->hight = Max(Hight(p->lchild),Hight(p->rchild))+1;                          /*更新现树根高度*/
}

/*节点插入左子树的右孩子造成失衡*/
/*左平衡操作*/
void LeftBalance(AVLTree &p)
{
    // 	AVLTree lc,rc;
    // 	lc = p->lchild;
    // 	switch(lc->bf){
    // 	case 1:
    // 		p->bf = lc->bf = 0;
    // 		R_Rotate(p);
    // 		break;
    // 	case -1:
    // 		rc = lc->rchild;
    // 		switch(rc->bf){
    // 		case 1:
    // 			p->bf = -1;
    // 			lc->bf = 0;
    // 			break;
    // 		case 0:
    // 			p->bf = lc->bf = 0;
    // 			lc->bf = 1;
    // 			break;
    // 		}
    // 		rc->bf = 0;
    // 		L_Rotate(p->lchild);
    // 		R_Rotate(p);
    // 		break;
    // 	}
    L_Rotate(p->lchild);            /*对旋转节点的左孩子节点进行一次左旋操作*/
    R_Rotate(p);                    /*对旋转节点进行一次右旋操作*/
}

/*节点插入右子树的左孩子造成失衡*/
/*右平衡操作*/
void RightBalance(AVLTree &p)
{
    // 	AVLTree lc, rc;
    // 	rc = p->rchild;
    // 	switch(rc->bf){
    // 	case -1:
    // 		p->bf = lc->bf = 0;
    // 		L_Rotate(p);
    // 		break;
    // 	case 1:
    // 		lc = rc->lchild;
    // 		switch(lc->bf){
    // 		case 1:
    // 			p->bf = 0;
    // 			rc->bf = -1;
    // 			break;
    // 		case 0:
    // 			p->bf = rc->bf = 0;
    // 			break;
    // 		case -1:
    // 			p->bf = 0;
    // 			rc->bf = 1;
    // 			break;
    // 		}
    // 		lc->bf = 0;
    // 		R_Rotate(p->rchild);
    // 		L_Rotate(p);
    // 		break;
    // 	}
    R_Rotate(p->rchild);            /*对旋转节点的右孩子节点进行右旋操作*/
    L_Rotate(p);                    /*对旋转节点进行左旋操作*/
}

void InsertAVL(AVLTree &p, int data)
{
    // 	if(!p){
    // 		p = (AVLTree)malloc(sizeof(AVLNode));
    // 		p->bf = 0;
    // 		p->data = data;
    // 		p->lchild = p->rchild = NULL;
    // 	}
    // 	else if(data == p->data){
    // 		taller = false;
    // 		return 0;
    // 	}
    // 	else if(data < p->data){
    // 		if(!InsertAVL(p->lchild,data,taller))
    // 			return 0;
    // 		if(taller){
    // 			switch(p->bf){
    // 			case 1:
    // 				LeftBalance(p);
    // 				taller = false;
    // 				break;
    // 			case 0:
    // 				p->bf = 1;
    // 				taller = true;
    // 				break;
    // 			case -1:
    // 				p->bf = 0;
    // 				taller = false;
    // 				break;
    // 			}
    // 		}
    // 	}
    // 	else{
    // 		if(InsertAVL(p->rchild,data,taller))
    // 			return 0;
    // 		if(taller){
    // 			switch(p->bf){
    // 			case 1:
    // 				p->bf = 0;
    // 				taller = false;
    // 				break;
    // 			case 0:
    // 				p->bf = -1;
    // 				taller = true;
    // 				break;
    // 			case -1:
    // 				RightBalance(p);
    // 				taller = false;
    // 				break;
    // 			}
    // 		}
    // 	}
    // 	return 1;
    if(p == NULL){
        p = (AVLTree)malloc(sizeof(AVLNode));
        p->data = data;
        p->lchild = p->rchild = NULL;
        p->hight = 0;
    }
    else if(data < p->data){
        InsertAVL(p->lchild,data);
        if(Hight(p->lchild) - Hight(p->rchild) == 2){ /*左子树高于右子树*/
            if(data < p->lchild->data)
                R_Rotate(p);
            else
                LeftBalance(p);
        }
    }
    else if(data > p->data){
        InsertAVL(p->rchild,data);
        if(Hight(p->rchild) - Hight(p->lchild) == 2){ /*右子树高于左子树*/
            if(data > p->rchild->data)
                L_Rotate(p);
            else
                RightBalance(p);
        }
    }
    p->hight = Max(Hight(p->lchild),Hight(p->rchild))+1;
}

AVLTree FindNode(AVLTree p, int data)
{
    if(!p)
        return NULL;
    if(data < p->data)
        return FindNode(p->lchild,data);
    else if(data > p->data)
        return FindNode(p->rchild,data);
    else
        return p;
}

void CreateAVL(AVLTree &p, int *a, int len)
{
    for(int i=0; i<10; i++)
        InsertAVL(p,a[i]);
}

void AVLRemove(AVLTree &p, int data)
{
    if(p == NULL)
        return;
    if(data < p->data){
        AVLRemove(p->lchild,data);
        if(Hight(p->rchild)-Hight(p->lchild)==2){
            if(p->rchild->rchild!=NULL && (Hight(p->rchild->lchild)>Hight(p->rchild->rchild)))
                RightBalance(p);
            else
                L_Rotate(p);
        }
        
    }
    else if(data > p->data){
        AVLRemove(p->rchild,data);
        if(Hight(p->lchild)-Hight(p->rchild)==2){
            if(p->lchild->rchild!=NULL && (Hight(p->lchild->rchild)>Hight(p->lchild->lchild)))
                LeftBalance(p);
            else
                R_Rotate(p);
        }
    }
    else{
        if(p->lchild && p->rchild){
            AVLTree pTemp = p->rchild;
            while(pTemp->lchild!=NULL)
                pTemp = pTemp->lchild;
            p->data = pTemp->data;
            p->hight = pTemp->hight;
            AVLRemove(p->rchild,pTemp->data);
            if(Hight(p->lchild)-Hight(p->rchild)==2){
                if(p->lchild->rchild!=NULL && (Hight(p->lchild->rchild)>Hight(p->lchild->lchild)))
                    LeftBalance(p);
                else
                    R_Rotate(p);
            }
        }
        else{
            AVLTree pTemp = p;
            if(p->lchild == NULL)
                p = p->rchild;
            else if(p->rchild == NULL)
                p = p->lchild;
        }
    }
    if(p == NULL) return;
    p->hight = Max(Hight(p->lchild),Hight(p->rchild))+1;
    return;
}

/*红黑树***********************************************************/
/*每个节点要么是红色，要么是黑色***********************************/
/*根节点是黑色的***************************************************/
/*每个叶节点，空节点是黑色的***************************************/
/*如果一个节点为红色，那么他的两个儿子都是黑色*********************/
/*对每个节点，从该节点到其子孙节点的所有路径上包含相同数目的黑节点*/

BRTree getRoot(BRTree T)
{
    while(T->parent)
        T = T->parent;
    return T;
}

void BRTreeLeftRotate(BRTree &brTree)
{
    BRTree rc = brTree->rchild;        /*记录节点的右孩子*/
    BRTree p = brTree->parent;         /*记录节点的父亲*/
    
    brTree->parent = rc;
    brTree->rchild = rc->lchild;       /*将节点的右孩子设置为节点右孩子的左孩子*/
    if(rc->lchild != NULL){
        rc->lchild->parent = brTree;   /*如果rc的左孩子非空，则设置其父亲为brTree*/
    }
    
    if(p){
        if(p->lchild == brTree)
            p->lchild =rc;
        else
            p->rchild = rc;
    }
    
    rc->lchild = brTree;
    rc->parent = p;
}

void BRTreeRightRotate(BRTree &brTree)
{
    BRTree lc = brTree->lchild;
    BRTree p = brTree->parent;
    
    brTree->parent = lc;
    brTree->lchild = lc->rchild;
    
    if(lc->rchild != NULL){
        lc->rchild->parent = brTree;
    }
    
    if(p){
        if(p->lchild == brTree)
            p->lchild = lc;
        else
            p->rchild = lc;
    }
    
    lc->rchild = brTree;
    lc->parent = p;
}

/*插入节点后，要维持红黑树四条性质的不变性*/
void BRInsertFixup(BRTree &T, BRTree z)
{
    BRTree Temp;
    while(z->parent && z->parent->color == RED){    /*插入节点的父节点为红色，破坏红黑树的性质*/
        if(z->parent->parent->lchild == z->parent){ /*判断z是否为父节点的左孩子*/
            Temp = z->parent->parent->rchild;       /*Temp记录z的叔父节点*/
            if(Temp && Temp->color == RED){
                Temp->color = BLACK;
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->rchild){
                    z = z->parent;
                    BRTreeLeftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                BRTreeRightRotate(z->parent->parent);
            }
        }
        else{
            Temp = z->parent->parent->lchild;
            if(Temp && Temp->color == RED){
                z->parent->color = BLACK;
                Temp->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->lchild){
                    z = z->parent;
                    BRTreeRightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                BRTreeLeftRotate(z->parent->parent);
            }
        }
    }
    T = getRoot(z);
    T->color = BLACK;
}

void BRTreeInsert(BRTree &brTree, int value)
{
    if(!brTree){
        brTree = (BRTree)malloc(sizeof(BRNode));
        brTree->parent = brTree->lchild = brTree->rchild = NULL;
        brTree->color = BLACK;
        brTree->value = value;
    }
    else{
        BRTree x = brTree;     /*x保存当前顶点的父母节点*/
        BRTree p = NULL;       /*p保存当前节点*/
        while(x != NULL){
            p = x;
            if(value < x->value)
                x = x->lchild;
            else if(value > x->value)
                x = x->rchild;
            else
                return;
        }
        x = (BRTree)malloc(sizeof(BRNode));
        x->color = RED;
        x->lchild = x->rchild = NULL;
        x->parent = p;
        x->value = value;
        if(value < p->value)
            p->lchild = x;
        else
            p->rchild = x;
        BRInsertFixup(brTree, x);         /*插入后调整*/
    }
}

void CreateBRTree(BRTree &T, int *a, int len)
{
    for(int i=0; i<len; i++)
        BRTreeInsert(T,a[i]);
}