//
//  SeqSearch.cpp
//  search
//
//  Created by Terwer Green on 16/5/31.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SeqSearch.h"

/* 顺序查找(O(n))
	L为数组，n为要查找的数组个数，key为要查找的关键字 
*/
int SeqSearch_1(sqList *L,int n,int key)
{
	int i;
	for(i = 1;i <= n;i++)
	{
		if(L->r[i] == key)
		{
			return i;
		}
	}
	return 0;
}

int SeqSearch_2(sqList *L,int n,int key)
{
	int i;
	L->r[0] = key;
	i = n;
	while(L->r[i] != key)
	{
		i--;
	}
	return i;
}

/* 	折半查找(O(logn))
	又称为二分查找。他的前提是线性表中的记录必须是关键码有序
	（通常从小到大有序），线性表必须采用顺序存储。折半查找的
	基本思路是：在有序表中，取中间记录作为比较对象，若给定值
	与中间记录的关键字相等，则查找成功；若给定值小于中间记录
	的关键字，则在中间记录的左半边区继续查找；若给定值大于中
	间记录的关键字，则在中间记录的右半区继续查找；不断重复上
	述过程，直到查找成功；获取没有该记录，则失败。
*/
int BinarySearch(sqList *L,int n,int key)
{
	int low,high,mid;
	low = 1;
	high = n;
	while(low <= high)
	{
		mid = (low + high) / 2;
		if(key < L->r[mid])
		{
			high = mid - 1;
		}
		else if(key > L->r[mid])
		{
			low = mid + 1;
		}
		else
		{
			return mid;
		}
	}
    return 0;
}

/* 插值查找(O(logn))
					  low + high		   1
	折半查找中 mid = ------------ = low + ---(high - low)
						  2				   2

							    key - L->r[low]
	插值查找中 mid = low + ------------------------(high - low)
							L->r[high] - L->r[low]
*/
int InterpolationSearch(sqList *L,int n,int key)
{
	int low,high,mid;
	low = 1;
	high = n;
	while(low <= high)
	{
		mid = low +((key - L->r[low]) / (L->r[high] - L->r[low])) * (high - low);

		if(key < L->r[mid])
		{
			high = mid - 1;
		}
		else if(key > L->r[mid])
		{
			low = mid + 1;
		}
		else
		{
			return mid;
		}
	}
    return 0;
}

int F(int k)
{
	if(0 == k)
	{
		return 0;
	}
	if(1 == k)
	{
		return 1;
	}
	if(k > 1)
	{
		return F(k - 1) + F(k - 2);
	}
    return 0;
}

/*	斐波那契查找(O(logn))
	利用黄金分割原理实现的
	mid = low +F[k - 1] - 1
*/
int FibonacciSearch(sqList *L,int n,int key)
{
	int low,high,mid,i,k;
	low = 1;
	high = n;
	k = 0;
	
	while(n > F(k) - 1)	/* 计算n位于斐波那契数列的位置 */
	{
		k++;
	}
	for(i = n;i < F(k) - 1;i++) /* 补全不满的数值 */
	{
		L->r[i] = L->r[n];
	}
	
	while(low <= high)
	{
		mid = low + F(k - 1) - 1;	/* 计算当前分割的下标 */
		if(key < L->r[mid])
		{
			high = mid - 1;			/* 调整最高下标 */
			k = k - 1;
		}
		else if(key > L->r[mid])
		{
			low = mid + 1;
			k = k - 2;
		}
		else
		{
			if(mid <= n)
			{
				return mid;
			}
			else
			{
				return n;
			}
		}
	}
	return 0;
}
