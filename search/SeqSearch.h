//
//  SeqSearch.h
//  DataStructure
//
//  Created by Terwer Green on 16/5/31.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#ifndef SeqSearch_h
#define SeqSearch_h

#define MAXSIZE 10

typedef struct
{
    int r[MAXSIZE];
    int length;
}sqList;

/* 顺序查找(O(n))
	L为数组，n为要查找的数组个数，key为要查找的关键字
 */
int SeqSearch_1(sqList *L,int n,int key);

int SeqSearch_2(sqList *L,int n,int key);

/* 	折半查找(O(logn))
	又称为二分查找。他的前提是线性表中的记录必须是关键码有序
	（通常从小到大有序），线性表必须采用顺序存储。折半查找的
	基本思路是：在有序表中，取中间记录作为比较对象，若给定值
	与中间记录的关键字相等，则查找成功；若给定值小于中间记录
	的关键字，则在中间记录的左半边区继续查找；若给定值大于中
	间记录的关键字，则在中间记录的右半区继续查找；不断重复上
	述过程，直到查找成功；获取没有该记录，则失败。
 */
int BinarySearch(sqList *L,int n,int key);

/* 插值查找(O(logn))
 low + high		   1
	折半查找中 mid = ------------ = low + ---(high - low)
 2				   2
 
 key - L->r[low]
	插值查找中 mid = low + ------------------------(high - low)
 L->r[high] - L->r[low]
 */
int InterpolationSearch(sqList *L,int n,int key);

/*	斐波那契查找(O(logn))
	利用黄金分割原理实现的
	mid = low +F[k - 1] - 1
 */
int FibonacciSearch(sqList *L,int n,int key);

#endif /* SeqSearch_h */
