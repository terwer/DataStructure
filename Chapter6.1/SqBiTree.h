/************************************************************************/
/*二叉树的顺序存储表示                                                   */
/************************************************************************/ 
#define MAX_TREE_SIZE 100 //二叉树的最大结点数 
#define CHAR 1 //字符型 
//#define CHAR 0 //整型(二者选一)
#if CHAR
typedef char TElemType;
TElemType Nil=' '; //设字符型以空格符为空
#else
typedef int TElemType;
TElemType Nil=0; //设整型以0为空
#endif
typedef TElemType SqBiTree[MAX_TREE_SIZE]; //0号单元存储根结点
typedef int Status;
#define  OK 1
#define  ERROR 0
#define  TRUE 1
#define FALSE 0
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct{
	int level,order; //结点的层,本层序号(按满二叉树计算) 
}position;

/************************************************************************/
/*二叉树的顺序存储的基本操作(23个)                                        */
/************************************************************************/

//构造空二叉树T。因为T是固定数组，不会改变，故不需要& 
Status InitBiTree(SqBiTree T)
{ 
	int i;
	for(i=0;i<MAX_TREE_SIZE;i++)
		T[i]=Nil; //初值为空
	return OK;
}

//由于SqBiTree是定长类型,无法销毁 
void DestroyBiTree(){
}

//按层序次序输入二叉树中结点的值(字符型或整型), 构造顺序存储的二叉树T
Status CreateBiTree(SqBiTree T){ 
	int i=0;
#if CHAR
	int l;
	char s[MAX_TREE_SIZE];
	printf("请按层序输入结点的值(字符)，空格表示空结点，结点数≤%d:\n",MAX_TREE_SIZE);
	gets(s); //输入字符串 */
	l=strlen(s); //求字符串的长度
	//将字符串赋值给T
	for(;i<l;i++) {
		T[i]=s[i];
		//此结点(不空)无双亲且不是根
		if(i!=0&&T[(i+1)/2-1]==Nil&&T[i]!=Nil) {
			printf("出现无双亲的非根结点%c\n",T[i]);
			exit(ERROR);
		}
	}
	for(i=l;i<MAX_TREE_SIZE;i++) //将空赋值给T的后面的结点
		T[i]=Nil;
#else
	printf("请按层序输入结点的值(整型)，0表示空结点，输999结束。结点数≤%d:\n",MAX_TREE_SIZE);
	while(1){
		scanf("%d",&T[i]);
		if(T[i]==999)
			break;
		 //此结点(不空)无双亲且不是根
		if(i!=0&&T[(i+1)/2-1]==Nil&&T[i]!=Nil){
			printf("出现无双亲的非根结点%d\n",T[i]);
			exit(ERROR);
		}
		i++;
	}
	while(i<MAX_TREE_SIZE){
		T[i]=Nil; //将空赋值给T的后面的结点
		i++;
	}
#endif
	return OK;
}

#define ClearBiTree InitBiTree /* 在顺序存储结构中，两函数完全一样 */

//初始条件: 二叉树T存在 
//操作结果: 若T为空二叉树,则返回TRUE,否则FALSE
Status BiTreeEmpty(SqBiTree T){
	if(T[0]==Nil) //根结点为空,则树空
		return TRUE;
	else
		return FALSE;
}

//初始条件: 二叉树T存在。操作结果: 返回T的深度
int BiTreeDepth(SqBiTree T){ 
	int i,j=-1;
	for(i=MAX_TREE_SIZE-1;i>=0;i--) //找到最后一个结点 
		if(T[i]!=Nil)
			break;
	i++; //为了便于计算 
	do
	j++;
	while(i>=pow(2,(double)j));
	return j;
}

//初始条件: 二叉树T存在 
//操作结果:  当T不空,用e返回T的根,返回OK;否则返回ERROR,e无定义 
Status Root(SqBiTree T,TElemType *e){ 
	if(BiTreeEmpty(T)) //T空
		return ERROR;
	else{
		*e=T[0];
		return OK;
	}
}

//初始条件: 二叉树T存在,e是T中某个结点(的位置) 
//操作结果: 返回处于位置e(层,本层序号)的结点的值 
TElemType Value(SqBiTree T,position e)
{ 
	return T[(int)pow(2,(double)e.level-1)+e.order-2];
}

//初始条件: 二叉树T存在,e是T中某个结点(的位置)
//操作结果: 给处于位置e(层,本层序号)的结点赋新值value 
Status Assign(SqBiTree T,position e,TElemType value){
	int i=(int)pow(2,(double)e.level-1)+e.order-2; //将层、本层序号转为矩阵的序号
	if(value!=Nil&&T[(i+1)/2-1]==Nil) //给叶子赋非空值但双亲为空 
		return ERROR;
	else if(value==Nil&&(T[i*2+1]!=Nil||T[i*2+2]!=Nil)) //给双亲赋空值但有叶子（不空）
		return ERROR;
	T[i]=value;
	return OK;
}

//初始条件: 二叉树T存在,e是T中某个结点
//操作结果: 若e是T的非根结点,则返回它的双亲,否则返回＂空＂ 
TElemType Parent(SqBiTree T,TElemType e){ 
	int i;
	if(T[0]==Nil) //空树
		return Nil;
	for(i=1;i<=MAX_TREE_SIZE-1;i++)
		if(T[i]==e) //找到e 
			return T[(i+1)/2-1];
	return Nil; //没找到e
}

//初始条件: 二叉树T存在,e是T中某个结点
//操作结果: 返回e的左孩子。若e无左孩子,则返回＂空＂
TElemType LeftChild(SqBiTree T,TElemType e){ 
	int i;
	if(T[0]==Nil) //空树
		return Nil;
	for(i=0;i<=MAX_TREE_SIZE-1;i++)
		if(T[i]==e) //找到e
			return T[i*2+1];
	return Nil; //没找到e 
}

/* 初始条件: 二叉树T存在,e是T中某个结点 */
/* 操作结果: 返回e的右孩子。若e无右孩子,则返回＂空＂ */
TElemType RightChild(SqBiTree T,TElemType e){ 
	int i;
	if(T[0]==Nil) /* 空树 */
		return Nil;
	for(i=0;i<=MAX_TREE_SIZE-1;i++)
		if(T[i]==e) /* 找到e */
			return T[i*2+2];
	return Nil; /* 没找到e */
}

//初始条件: 二叉树T存在,e是T中某个结点 
//操作结果: 返回e的左兄弟。若e是T的左孩子或无左兄弟,则返回＂空＂ 
TElemType LeftSibling(SqBiTree T,TElemType e){
	int i;
	if(T[0]==Nil) //空树
		return Nil;
	for(i=1;i<=MAX_TREE_SIZE-1;i++)
		if(T[i]==e&&i%2==0) //找到e且其序号为偶数(是右孩子)
			return T[i-1];
	return Nil; //没找到e 
}

//初始条件: 二叉树T存在,e是T中某个结点
//操作结果: 返回e的右兄弟。若e是T的右孩子或无右兄弟,则返回＂空＂
TElemType RightSibling(SqBiTree T,TElemType e){ 
	int i;
	if(T[0]==Nil) //空树 
		return Nil;
	for(i=1;i<=MAX_TREE_SIZE-1;i++)
		if(T[i]==e&&i%2) //找到e且其序号为奇数(是左孩子) 
			return T[i+1];
	return Nil; //没找到e 
}

//InsertChild()用到。
//把从q的j结点开始的子树移为从T的i结点开始的子树 
void Move(SqBiTree q,int j,SqBiTree T,int i) {
	if(q[2*j+1]!=Nil) //q的左子树不空
		Move(q,(2*j+1),T,(2*i+1)); //把q的j结点的左子树移为T的i结点的左子树 
	if(q[2*j+2]!=Nil) //q的右子树不空
		Move(q,(2*j+2),T,(2*i+2)); //把q的j结点的右子树移为T的i结点的右子树
	T[i]=q[j]; //把q的j结点移为T的i结点
	q[j]=Nil; //把q的j结点置空
}

//初始条件: 二叉树T存在,p是T中某个结点的值,LR为0或1,非空二叉树c与T
//不相交且右子树为空 
//操作结果: 根据LR为0或1,插入c为T中p结点的左或右子树。p结点的原有左或 
//右子树则成为c的右子树 
Status InsertChild(SqBiTree T,TElemType p,Status LR,SqBiTree c){
	int j,k,i=0;
	for(j=0;j<(int)pow(2,(double)BiTreeDepth(T))-1;j++) //查找p的序号
		if(T[j]==p) //j为p的序号
			break;
	k=2*j+1+LR; //k为p的左或右孩子的序号
	if(T[k]!=Nil) //p原来的左或右孩子不空 
		Move(T,k,T,2*k+2); //把从T的k结点开始的子树移为从k结点的右子树开始的子树
	Move(c,i,T,k); //把从c的i结点开始的子树移为从T的k结点开始的子树
	return OK;
}


typedef int QElemType; /* 设队列元素类型为整型(序号) */
#include "SqQueue.h" /* 顺序非循环队列 */

//初始条件: 二叉树T存在,p指向T中某个结点,LR为1或0 
//操作结果: 根据LR为1或0,删除T中p所指结点的左或右子树 
Status DeleteChild(SqBiTree T,position p,int LR){ 
	int i;
	Status k=OK; //队列不空的标志
	SqQueue q;
	InitQueue(&q); //初始化队列，用于存放待删除的结点 
	i=(int)pow(2,(double)p.level-1)+p.order-2; //将层、本层序号转为矩阵的序号
	if(T[i]==Nil) //此结点空 
		return ERROR;
	i=i*2+1+LR; //待删除子树的根结点在矩阵中的序号 
	while(k){
		if(T[2*i+1]!=Nil) //左结点不空 
			EnQueue(&q,2*i+1); //入队左结点的序号
		if(T[2*i+2]!=Nil) //右结点不空
			EnQueue(&q,2*i+2); //入队右结点的序号
		T[i]=Nil; //删除此结点 
		k=DeQueue(&q,&i); //队列不空 
	}
	return OK;
}

Status(*VisitFunc)(TElemType); /* 函数变量 */

//PreOrderTraverse()调用
void PreTraverse(SqBiTree T,int e){
	VisitFunc(T[e]);
	if(T[2*e+1]!=Nil) //左子树不空
		PreTraverse(T,2*e+1);
	if(T[2*e+2]!=Nil) //右子树不空 
		PreTraverse(T,2*e+2);
}

//初始条件: 二叉树存在,Visit是对结点操作的应用函数
//操作结果: 先序遍历T,对每个结点调用函数Visit一次且仅一次。
//一旦Visit()失败,则操作失败 
Status PreOrderTraverse(SqBiTree T,Status(*Visit)(TElemType)){ 
	printf("\n************************************************************************\n");
	printf("*二叉树的先序遍历                                                      *\n");
	printf("************************************************************************\n");

	VisitFunc=Visit;
	if(!BiTreeEmpty(T)) //树不空
		PreTraverse(T,0);
	printf("\n");
	return OK;
}

//InOrderTraverse()调用 
void InTraverse(SqBiTree T,int e){
	if(T[2*e+1]!=Nil) //左子树不空
		InTraverse(T,2*e+1);
	VisitFunc(T[e]);
	if(T[2*e+2]!=Nil) //右子树不空
		InTraverse(T,2*e+2);
}

//初始条件: 二叉树存在,Visit是对结点操作的应用函数
//操作结果: 中序遍历T,对每个结点调用函数Visit一次且仅一次。一旦Visit()失败,则操作失败 
Status InOrderTraverse(SqBiTree T,Status(*Visit)(TElemType)){       
	printf("\n************************************************************************\n");
	printf("*二叉树的中序遍历                                                      *\n");
	printf("************************************************************************\n");

	VisitFunc=Visit;
	if(!BiTreeEmpty(T)) //树不空
		InTraverse(T,0);
	printf("\n");
	return OK;
}

//PostOrderTraverse()调用
void PostTraverse(SqBiTree T,int e){ 
	if(T[2*e+1]!=Nil) //左子树不空
		PostTraverse(T,2*e+1);
	if(T[2*e+2]!=Nil) //右子树不空
		PostTraverse(T,2*e+2);
	VisitFunc(T[e]);
}

//初始条件: 二叉树T存在,Visit是对结点操作的应用函数
//操作结果: 后序遍历T,对每个结点调用函数Visit一次且仅一次。
//一旦Visit()失败,则操作失败
Status PostOrderTraverse(SqBiTree T,Status(*Visit)(TElemType)){ 
	printf("\n************************************************************************\n");
	printf("*二叉树的后序遍历                                                      *\n");
	printf("************************************************************************\n");

	VisitFunc=Visit;
	if(!BiTreeEmpty(T)) //树不空
		PostTraverse(T,0);
	printf("\n");
	return OK;
}

//层序遍历二叉树
void LevelOrderTraverse(SqBiTree T,Status(*Visit)(TElemType)){ 
	printf("\n************************************************************************\n");
	printf("*二叉树的层次遍历                                                      *\n");
	printf("************************************************************************\n");

	int i=MAX_TREE_SIZE-1,j;
	while(T[i]==Nil)
		i--; //找到最后一个非空结点的序号
	for(j=0;j<=i;j++)  //从根结点起,按层序遍历二叉树
		if(T[j]!=Nil)
			Visit(T[j]); //只遍历非空的结点
	printf("\n");
}

//逐层、按本层序号输出二叉树
void Print(SqBiTree T){
	int j,k;
	position p;
	TElemType e;
	for(j=1;j<=BiTreeDepth(T);j++){
		printf("第%d层: ",j);
		for(k=1;k<=pow(2,(double)j-1);k++){
			p.level=j;
			p.order=k;
			e=Value(T,p);
			if(e!=Nil)
				printf("%d:%c ",k,e);
		}
		printf("\n");
	}
}

//输出树的形状
void PrintTree(SqBiTree T){
	printf("\n************************************************************************\n");
	printf("*二叉树的形状显示                                                       *\n");
	printf("************************************************************************\n");

	int j,k;
	position p;
	TElemType e;
	int d=BiTreeDepth(T);
	for(j=1;j<=d;j++){
		//打印空格
		int m;
		for (m=1;m<=(pow(2,(double)d-j)-1);m++){//注意比后面的少一次方
			printf(" ");
		}

		//打印元素
		for(k=1;k<=pow(2,(double)j-1);k++){
			p.level=j;
			p.order=k;
			e=Value(T,p);
			if(e!=Nil)
				printf("%c",e);
			else
				printf(" ");
			
			//打印空格
			int n;
			for (n=1;n<=(pow(2,(double)d-j+1)-1);n++){							
					printf(" ");
			}

		}
		printf("\n");//某一行结束

	}
}