//
//  HashSearch.h
//  DataStructure
//
//  Created by Terwer Green on 16/5/31.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#ifndef HashSearch_h
#define HashSearch_h

#define SUCCESS 		1
#define UNSUCCESS	    0
#define NULLKEY		-32768
#define HASHSIZE 		12

#define OK 				1

typedef int Status;

typedef struct
{
    int *elem;
    int count;
}HashTable;

Status InitHashTable(HashTable *H);

/* 散列函数 */
int Hash(int key);

/* 插入关键字散列表 */
void InsertHash(HashTable *H,int key);

/*
	散列表查找关键字(O(1))
 */
Status SearchHash(HashTable H,int key,int *addr);

#endif /* HashSearch_h */
