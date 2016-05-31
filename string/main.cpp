//
//  main.cpp
//  string
//
//  Created by Terwer Green on 16/5/31.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#include <iostream>
#include "KMP.h"

int main(int argc, const char * argv[]) {
   
    char T[1000],P[100];
    printf("\nPlease enter the text: \n");
    while(gets(T)){
        printf("\nPlease enter the pattern: \n");
        gets(P);
        int pos = kmp_matcher(T,P);
        if(pos != -1){
            printf("\nString Occur at position:%d \n",pos+1);
        }else{
            printf("\nNo match found.\n");
        }
        printf("\nPlease enter the text: \n");
    }
    
    return 0;
}
