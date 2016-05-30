//
//  GeneralizedList.h
//  generalizedlist
//
//  Created by Terwer Green on 16/5/30.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#ifndef GeneralizedList_h
#define GeneralizedList_h

#define AtomType char
#define MAXSIZE  1024
#define ElemTag int
#define OK       1
#define ERROR    0

typedef struct GLNode
{
    ElemTag tag;
    union
    {
        AtomType  atom;
        struct GLNode *hp;
    }atom_hp;
    struct GLNode *tp;
}GLNode,*GList;

//功能：分离出广义表中表头部分
//返回：分离后剩下的字符串，不包括逗号
void Disastr(char *s,char *hstr);

//功能：根据输入的字符串，建立广义表
//返回：成功则返回建立的广义表的表头，否则，返回NULL
GLNode * GLCreate(char *s);

void DisplayList(GList head);

//功能：取出广义表的表头部分
//返回：成功则返回广义表的表头，否则，返回空或退出
GList GetHead(GList L);

//功能：取出广义表的表尾部分
//返回：成功返回广义表的表尾部分，否则，返回空或者退出
GList GetTail(GList L);

//功能:求出广义表的长度
//返回值:广义表的长度
int Length(GList L);

//功能：求得广义表的深度
//输入：需求深度的广义表的指针
int Depth(GList L);

//功能：统计原子结点的个数
//输入：需统计的广义表指针
int CountAtom(GList L);

//功能：完成广义表的复制,将res复制到dest中
//返回：成功返回1，否则，返回0
bool CopyList(GList *dest,GList res);

//功能：合并广义表，如果p为空，则申请空间，将q复制到p中
//例如：((a,b),c) 和(a,b)合并之后为：((a,b),c,a,b)
//算法描述：先找到第一个广义表的最后一个结点，将其链到第二个广义表的首元素即可
void Merge(GList *p,GLNode *q);

//功能：类似二叉树的先序遍历遍历广义表L
//eg：例如(a,(b,(c),d))结果为：a,b,c,d
//算法描述：
//L若为原子结点，显示该数据，递归调用遍历后续元素，也即:write(L->atom_hp.atom);PreOrder(L->tp);
//L是子表结点，递归调用遍历该子表，遍历后续元素，也即:PreOrder(L->atom_hp.tp);PreOrder(L->tp);
void PreOrder(GList L);

// 判断两个广义表是否相等，相等，返回1，否则，返回0
// 相等的定义：两个广义表具有相同的存储结构，对应的原子结点的数据域也相等
//算法描述：
// 形式：条件
//Equal(p,q) = Equal(p->tp,q->tp) ; p->tag = 0 && q->tag = 0 && p->atom_hp.atom = q->atom_hp.atom
//Equal(p,q) = Equal(p->atom_hp.hp,q->atom_hp.hp) && Equal(p->tp,q->tp) ; p->tag = 1 && q->tag = 1
//Equal(p,q) = false     ; p->tag = 0 && q->tag = 0 p->atom_hp.atom != q->atom_hp.atom 或者 p->tag *p->tag + q->tag*q->tag =1
//Equal(p,q) = false      ; p q 其中之一为NULL
bool Equal(GList p,GList q);

#endif /* GeneralizedList_h */
