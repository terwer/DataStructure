//
//  KMP.cpp
//  DataStructure
//
//  Created by Terwer Green on 16/5/31.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "KMP.h"

void picalculator(char pattern[],int pi[],int patlen)
{
    int i,j;
    pi[0]=0;  //pi[first character in the pattern]=0
    j=0;
    i=1;
    while(i<patlen){ // that i is less than the length of pattern
        if(pattern[i]==pattern[j]){
            pi[i]=j+1;
            i++;
            j++;
            
        }else if(j>0){
            j=pi[j-1];
        }else {
            pi[i]=0;
            i++;
        }
    } //end of while
    
}

int kmp_matcher(char text[], char pattern[])
{
    int i,j,F[100];	// the maximum size of Pattern String
    int patlen = (int)strlen(pattern);
    int textlen = (int)strlen(text);
    picalculator(pattern,F,patlen);
    i=0;
    j=0;
    while(i<textlen){
        if(text[i]==pattern[j]){
            
            if(j==patlen-1)
                return i-j; // means, in (i-j)th position, there is a match occur
            else{
                i++;
                j++;
            }
        }else if(j>0){
            j=F[j-1];
        }else{
            i++;
        } 
    }
    return -1; // No match found
}