//
//  main.cpp
//  generalizedlist
//
//  Created by Terwer Green on 16/5/30.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#include <iostream>
#include "GeneralizedList.h"

int main(int argc, const char * argv[]) 
{
    char s[MAXSIZE],a[MAXSIZE];
    GList head;
    GList L;
    
    printf("please input a string:");
    scanf("%s",s);
    head = GLCreate(s);
    DisplayList(head);
    printf("\n");
    
    printf("The Head is:");
    DisplayList(GetHead(head));
    printf("\n");
    
    printf("The Tail is: ");
    DisplayList(GetTail(head));
    printf("\n");
    
    printf("The Length is %d\n",Length(head));
    printf("The Depth is %d\n",Depth(head));
    printf("The Atom number is %d\n",CountAtom(head));
    
    printf("Copy the List:\n");
    CopyList(&L,head);
    DisplayList(L);
    printf("\n");
    
    printf("Merge the List\n");
    Merge(&L,head);
    DisplayList(L);
    printf("\n");
    
    printf("PreOrder:");
    PreOrder(head);
    printf("\n");
    
    printf("input a string:");
    scanf("%s",a);
    L = GLCreate(a);
    DisplayList(L);
    printf(" Eqaul ");
    DisplayList(head);
    printf(":");
    if (Equal(L,head)) printf("yes!\n");
    else printf("no!\n");
    return 0;
}
