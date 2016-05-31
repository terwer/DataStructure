//
//  main.cpp
//  tree
//
//  Created by Terwer Green on 16/5/31.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#include <iostream>
#include "Tree.h"

using namespace std;

int main(int argc, const char * argv[]) {
   	int a[10] = {6, 3, 2, 1, 7, 9, 8, 0, 4, 5};
    //BiTree T;
    //createBST(T,a,10);
    //InsertBST(T,9);
    //DeleteBST(T,2);
    //inOrderTraverse(T);
    //std::cout << std::endl;
    //preOrderTraverse(T);
    //std::cout << std::endl;
    //
    //BiTree f=NULL, p=NULL;
    //std::cout << SearchBST(T,11,f,p);
    //std::cout << p->data;
    
    //AVLTree T=NULL;
    //CreateAVL(T,a,10);
    //InsertAVL(T,10);
    //AVLRemove(T,6);
    //inOrderTraverse(T);
    //std::cout << std::endl;
    //preOrderTraverse(T);
    //AVLTree pT = FindNode(T,8);
    BRTree T = NULL;
    CreateBRTree(T,a,10);
    preOrderTraverse(T);
    cout << endl;
    inOrderTraverse(T);
    cout << endl;
    cin.get();
    cin.get();
    return 0;
}
