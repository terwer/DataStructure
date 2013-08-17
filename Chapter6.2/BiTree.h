﻿/************************************************************************/
/*  二叉树的二叉链表存储表示                                              */
/************************************************************************/
#define  OK 1
#define  OVERFLOW -2
#define  TRUE 1
#define  FALSE 0
#define CHAR //字符型
// #define INT //整型（二者选一）
#ifdef CHAR
typedef char TElemType;
TElemType Nil=' '; //字符型以空格符为空
#endif
#ifdef INT
typedef int TElemType;
TElemType Nil=0; //整型以0为空 
#endif
typedef int Status;
#include <stdlib.h>

typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild,*rchild; //左右孩子指针
}BiTNode,*BiTree;

/************************************************************************/
/* 二叉树的二叉链表存储的基本操作(22个)                                   */
/************************************************************************/

//操作结果: 构造空二叉树T
Status InitBiTree(BiTree *T){
	*T=NULL;
	return OK;
}

//初始条件: 二叉树T存在。
//销毁二叉树T 
void DestroyBiTree(BiTree *T){
	//非空树
	if(*T) {
		if((*T)->lchild) //有左孩子
			DestroyBiTree(&(*T)->lchild); //销毁左孩子子树
		if((*T)->rchild) /* 有右孩子 */
			DestroyBiTree(&(*T)->rchild); //销毁右孩子子树
		free(*T); //释放根结点
		*T=NULL; //空指针赋0
	}
}

//算法6.4:按先序次序输入二叉树中结点的值（可为字符型或整型，在主程中
//定义），构造二叉链表表示的二叉树T。变量Nil表示空（子）树。有改动
void CreateBiTree(BiTree *T){ 
	TElemType ch;
#ifdef CHAR
	//printf("请顺序输入二叉树的结点（字符），空节点用空格表示：\n");
	scanf("%c",&ch);
#endif
#ifdef INT
	//printf("请顺序输入二叉树的结点（整型），空节点用0表示：\n");
	scanf("%d",&ch);
#endif
	if(ch==Nil) //空 
		*T=NULL;
	else{
		*T=(BiTree)malloc(sizeof(BiTNode));
		if(!*T)
			exit(OVERFLOW);
		(*T)->data=ch; //生成根结点
		CreateBiTree(&(*T)->lchild); //构造左子树
		CreateBiTree(&(*T)->rchild); //构造右子树
	}
}

//初始条件: 二叉树T存在 
//操作结果: 若T为空二叉树,则返回TRUE,否则FALSE 
Status BiTreeEmpty(BiTree T){ 
	if(T)
		return FALSE;
	else
		return TRUE;
}

#define ClearBiTree DestroyBiTree

//初始条件: 二叉树T存在。
//操作结果: 返回T的深度 
int BiTreeDepth(BiTree T){ 
	int i,j;
	if(!T)
		return 0;
	if(T->lchild)
		i=BiTreeDepth(T->lchild);
	else
		i=0;
	if(T->rchild)
		j=BiTreeDepth(T->rchild);
	else
		j=0;
	return i>j?i+1:j+1;
}

//初始条件: 二叉树T存在。
//操作结果: 返回T的根 
TElemType Root(BiTree T){ 
	if(BiTreeEmpty(T))
		return Nil;
	else
		return T->data;
}

//初始条件: 二叉树T存在，p指向T中某个结点
//操作结果: 返回p所指结点的值 
TElemType Value(BiTree p){ 
	return p->data;
}

//给p所指结点赋值为value 
void Assign(BiTree p,TElemType value){ 
	p->data=value;
}



typedef BiTree QElemType; //设队列元素为二叉树的指针类型
#include "LinkQueue.h"

//初始条件: 二叉树T存在,e是T中某个结点 
//操作结果: 若e是T的非根结点,则返回它的双亲,否则返回＂空＂ 
TElemType Parent(BiTree T,TElemType e){
	LinkQueue q;
	QElemType a;
	//非空树
	if(T) 
	{
		InitQueue(&q); //初始化队列 
		EnQueue(&q,T); //树根入队 
		//队不空
		while(!QueueEmpty(q)) {
			DeQueue(&q,&a); //出队,队列元素赋给a
			if(a->lchild&&a->lchild->data==e||a->rchild&&a->rchild->data==e)
				//找到e(是其左或右孩子) */
				return a->data; //返回e的双亲的值 
			//没找到e,则入队其左右孩子指针(如果非空) 
			else {
				if(a->lchild)
					EnQueue(&q,a->lchild);
				if(a->rchild)
					EnQueue(&q,a->rchild);
			}
		}
	}
	return Nil; //树空或没找到e
}


//返回二叉树T中指向元素值为s的结点的指针。另加 
BiTree Point(BiTree T,TElemType s){ 
	LinkQueue q;
	QElemType a;
	//非空树 
	if(T) {
		InitQueue(&q); //初始化队列 
		EnQueue(&q,T); //根结点入队 
		//队不空 
		while(!QueueEmpty(q)) {
			DeQueue(&q,&a); //出队,队列元素赋给a 
			if(a->data==s)
				return a;
			if(a->lchild) //有左孩子 
				EnQueue(&q,a->lchild); //入队左孩子
			if(a->rchild) //有右孩子
				EnQueue(&q,a->rchild); //入队右孩子
		}
	}
	return NULL;
}

//初始条件: 二叉树T存在,e是T中某个结点
//操作结果: 返回e的左孩子。若e无左孩子,则返回＂空＂
TElemType LeftChild(BiTree T,TElemType e){
	BiTree a;
	//非空树 
	if(T) {
		a=Point(T,e); //a是结点e的指针 
		if(a&&a->lchild) //T中存在结点e且e存在左孩子 */
			return a->lchild->data; //返回e的左孩子的值 
	}
	return Nil; /* 其余情况返回空 */
}

//初始条件: 二叉树T存在,e是T中某个结点 
//操作结果: 返回e的右孩子。若e无右孩子,则返回＂空＂
TElemType RightChild(BiTree T,TElemType e){ 
	BiTree a;
	//非空树 
	if(T) {
		a=Point(T,e); //a是结点e的指针 
		if(a&&a->rchild) //T中存在结点e且e存在右孩子 
			return a->rchild->data; //返回e的右孩子的值 
	}
	return Nil; //其余情况返回空
}

//初始条件: 二叉树T存在,e是T中某个结点 */
//操作结果: 返回e的左兄弟。若e是T的左孩子或无左兄弟,则返回＂空＂ 
TElemType LeftSibling(BiTree T,TElemType e){
	TElemType a;
	BiTree p;
	//非空树 
	if(T) {
		a=Parent(T,e); //a为e的双亲
		p=Point(T,a); //p为指向结点a的指针
		if(p->lchild&&p->rchild&&p->rchild->data==e) //p存在左右孩子且右孩子是e 
			return p->lchild->data; /* 返回p的左孩子(e的左兄弟) */
	}
	return Nil; //树空或没找到e的左兄弟
}

//初始条件: 二叉树T存在,e是T中某个结点
//操作结果: 返回e的右兄弟。若e是T的右孩子或无右兄弟,则返回＂空＂
TElemType RightSibling(BiTree T,TElemType e){
	TElemType a;
	BiTree p;
	//非空树 
	if(T) {
		a=Parent(T,e); //a为e的双亲 
		p=Point(T,a); //p为指向结点a的指针
		if(p->lchild&&p->rchild&&p->lchild->data==e) //p存在左右孩子且左孩子是e
			return p->rchild->data; //返回p的右孩子(e的右兄弟)
	}
	return Nil; //树空或没找到e的右兄弟
}

//初始条件: 二叉树T存在,p指向T中某个结点,LR为0或1,非空二叉树c与T
//不相交且右子树为空 
//操作结果: 根据LR为0或1,插入c为T中p所指结点的左或右子树。p所指结点的 
//原有左或右子树则成为c的右子树
Status InsertChild(BiTree p,int LR,BiTree c) { 
    //p不空
	if(p){
		if(LR==0){
			c->rchild=p->lchild;
			p->lchild=c;
		}
		//LR==1 
		else {
			c->rchild=p->rchild;
			p->rchild=c;
		}
		return OK;
	}
	return ERROR; //p空
}

//初始条件: 二叉树T存在,p指向T中某个结点,LR为0或1 
//操作结果: 根据LR为0或1,删除T中p所指结点的左或右子树 
Status DeleteChild(BiTree p,int LR) { 
	//p不空 
	if(p){
		if(LR==0) //删除左子树 
			ClearBiTree(&p->lchild);
		else //删除右子树 
			ClearBiTree(&p->rchild);
		return OK;
	}
	return ERROR; //p空 
}

//初始条件: 二叉树T存在,Visit是对结点操作的应用函数。算法6.1，有改动 
//操作结果: 先序递归遍历T,对每个结点调用函数Visit一次且仅一次 
void PreOrderTraverse(BiTree T,Status(*Visit)(TElemType)){

	//T不空 
	if(T) {
		Visit(T->data); //先访问根结点 
		PreOrderTraverse(T->lchild,Visit); //再先序遍历左子树 
		PreOrderTraverse(T->rchild,Visit); //最后先序遍历右子树 
	}
}

//初始条件: 二叉树T存在,Visit是对结点操作的应用函数
//操作结果: 中序递归遍历T,对每个结点调用函数Visit一次且仅一次
void InOrderTraverse(BiTree T,Status(*Visit)(TElemType)){ 
	if(T){
		InOrderTraverse(T->lchild,Visit); //先中序遍历左子树 
		Visit(T->data); //再访问根结点 
		InOrderTraverse(T->rchild,Visit); //最后中序遍历右子树
	}
}

typedef BiTree SElemType; /* 设栈元素为二叉树的指针类型 */
#include "SqStack.h"

//采用二叉链表存储结构，Visit是对数据元素操作的应用函数。算法6.3
//中序遍历二叉树T的非递归算法(利用栈)，对每个数据元素调用函数Visit
Status InOrderTraverse1(BiTree T,Status(*Visit)(TElemType)){ 
	SqStack S;
	InitStack(&S);
	while(T||!StackEmpty(S)){
		//根指针进栈,遍历左子树 
		if(T){ 
			Push(&S,T);
			T=T->lchild;
		}
		//根指针退栈,访问根结点,遍历右子树 
		else{ 
			Pop(&S,&T);
			if(!Visit(T->data))
				return ERROR;
			T=T->rchild;
		}
	}
	printf("\n");
	return OK;
}

//采用二叉链表存储结构，Visit是对数据元素操作的应用函数。算法6.2 
//中序遍历二叉树T的非递归算法(利用栈)，对每个数据元素调用函数Visit 
Status InOrderTraverse2(BiTree T,Status(*Visit)(TElemType)){
	SqStack S;
	BiTree p;
	InitStack(&S);
	Push(&S,T); //根指针进栈 
	while(!StackEmpty(S)){
		while(GetTop(S,&p)&&p)
			Push(&S,p->lchild); //向左走到尽头
		Pop(&S,&p); //空指针退栈
		if(!StackEmpty(S)){ //访问结点,向右一步
			Pop(&S,&p);
			if(!Visit(p->data))
				return ERROR;
			Push(&S,p->rchild);
		}
	}
	printf("\n");
	return OK;
}

//初始条件: 二叉树T存在,Visit是对结点操作的应用函数
//操作结果: 后序递归遍历T,对每个结点调用函数Visit一次且仅一次
void PostOrderTraverse(BiTree T,Status(*Visit)(TElemType)){ 
	 //T不空
	if(T){
		PostOrderTraverse(T->lchild,Visit); //先后序遍历左子树 
		PostOrderTraverse(T->rchild,Visit); //再后序遍历右子树 
		Visit(T->data); //最后访问根结点 
	}
}

//初始条件：二叉树T存在,Visit是对结点操作的应用函数
//操作结果：层序递归遍历T(利用队列),对每个结点调用函数Visit一次且仅一次 
void LevelOrderTraverse(BiTree T,Status(*Visit)(TElemType)){ 
	LinkQueue q;
	QElemType a;
	if(T){
		InitQueue(&q);
		EnQueue(&q,T);
		while(!QueueEmpty(q)){
			DeQueue(&q,&a);
			Visit(a->data);
			if(a->lchild!=NULL)
				EnQueue(&q,a->lchild);
			if(a->rchild!=NULL)
				EnQueue(&q,a->rchild);
		}
		printf("\n");
	}
}
