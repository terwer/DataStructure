//
//  main.cpp
//  sort
//
//  Created by Terwer Green on 16/5/30.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Sort.h"

using namespace std;

void print(int arr[], int arr_size);

const int ARR_SIZE = 3;
int main(int argc, const char * argv[])
{
    
    int A[ARR_SIZE];
    printf("please input %d integer:",ARR_SIZE);
    for(int i = 0; i < ARR_SIZE; ++i){
        cin >> A[i];
    }
    int B[ARR_SIZE];
    clock_t t1, t2;
    
    //bubble sort
    for(int i = 0; i < ARR_SIZE; ++i){
        B[i] = A[i];
    }
    t1 = clock();
    bubble_sort(B, ARR_SIZE);
    t2 = clock();
    cout << "bubble sort" << endl;
    cout << "Time: " << (double)(t2-t1)/CLOCKS_PER_SEC << endl;
    print(B, ARR_SIZE);
    
    //insertion sort
    for(int i = 0; i < ARR_SIZE; ++i){
        B[i] = A[i];
    }
    t1 = clock();
    insertion_sort(B, ARR_SIZE);
    t2 = clock();
    cout << "insertion sort" << endl;
    cout << "Time: " << (double)(t2-t1)/CLOCKS_PER_SEC << endl;
    print(B, ARR_SIZE);
    
    //selection sort
    for(int i = 0; i < ARR_SIZE; ++i){
        B[i] = A[i];
    }
    t1 = clock();
    selection_sort(B, ARR_SIZE);
    t2 = clock();
    cout << "selection sort" << endl;
    cout << "Time: " << (double)(t2-t1)/CLOCKS_PER_SEC << endl;
    print(B, ARR_SIZE);
    
    //quick sort
    for(int i = 0; i < ARR_SIZE; ++i){
        B[i] = A[i];
    }
    t1 = clock();
    quick_sort(B, ARR_SIZE);
    t2 = clock();
    cout << "quick sort" << endl;
    cout << "Time: " << (double)(t2-t1)/CLOCKS_PER_SEC << endl;
    print(B, ARR_SIZE);
    
    //merger sort
    for(int i = 0; i < ARR_SIZE; ++i){
        B[i] = A[i];
    }
    t1 = clock();
    merger_sort(B, ARR_SIZE);
    t2 = clock();
    cout << "merger sort" << endl;
    cout << "Time: " << (double)(t2-t1)/CLOCKS_PER_SEC << endl;
    print(B, ARR_SIZE);
    
    return 0;
}


void print(int arr[], int arr_size){
    for (int i = 0; i < arr_size; ++i){
        cout << arr[i] << " ";
    }
    cout <<"\n================================================" << endl;
}


