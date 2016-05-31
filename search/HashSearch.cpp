//
//  HashSearch.cpp
//  search
//
//  Created by Terwer Green on 16/5/31.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "HashSearch.h"

int m = 100; 				// 散列表表长，全局变量

Status InitHashTable(HashTable *H)
{
	int i;
	m = HASHSIZE;
	H->count = m;
	H->elem = (int *)malloc(m * sizeof(int));
	for(i = 0;i < m;i++)
	{
		H->elem[i] = NULLKEY;
	}
	return OK;
}
/* 散列函数 */
int Hash(int key)
{
	return key % m;
}
/* 插入关键字散列表 */
void InsertHash(HashTable *H,int key)
{
	int addr = Hash(key);
	while(H->elem[addr] != NULLKEY)
	{
		addr = (addr + 1) % m;
	}
	H->elem[addr] = key;
	
}

/* 
	散列表查找关键字(O(1))
 */
Status SearchHash(HashTable H,int key,int *addr)
{
	*addr = Hash(key);
	while(H.elem[*addr] != key)
	{
		*addr = (*addr + 1) % m;
		if(H.elem[*addr] == NULLKEY || *addr == Hash(key))
		{
			return UNSUCCESS;
		}
	}
	return SUCCESS;
}