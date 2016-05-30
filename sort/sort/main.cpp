//
//  main.cpp
//  sort
//
//  Created by yifa007 on 16/5/30.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Sort.h"

using namespace std;

void print(int arr[], int arr_size);

const int ArrSize = 3;
int main(int argc, const char * argv[]) {
    
    int A[ArrSize];
    printf("please input %d integer:",ArrSize);
    for(int i = 0; i < ArrSize; ++i)
        cin >> A[i];
    int B[ArrSize];
    clock_t t1, t2;
    
    //bubble sort
    for(int i = 0; i < ArrSize; ++i)
        B[i] = A[i];
    t1 = clock();
    bubble_sort(B, ArrSize);
    t2 = clock();
    cout << "bubble sort" << endl;
    cout << "Time: " << (double)(t2-t1)/CLOCKS_PER_SEC << endl;
    print(B, ArrSize);
    
    //insertion sort
    for(int i = 0; i < ArrSize; ++i)
        B[i] = A[i];
    t1 = clock();
    insertion_sort(B, ArrSize);
    t2 = clock();
    cout << "insertion sort" << endl;
    cout << "Time: " << (double)(t2-t1)/CLOCKS_PER_SEC << endl;
    print(B, ArrSize);
    
    //selection sort
    for(int i = 0; i < ArrSize; ++i)
        B[i] = A[i];
    t1 = clock();
    selection_sort(B, ArrSize);
    t2 = clock();
    cout << "selection sort" << endl;
    cout << "Time: " << (double)(t2-t1)/CLOCKS_PER_SEC << endl;
    print(B, ArrSize);
    
    //quick sort
    for(int i = 0; i < ArrSize; ++i)
        B[i] = A[i];
    t1 = clock();
    quick_sort(B, ArrSize);
    t2 = clock();
    cout << "quick sort" << endl;
    cout << "Time: " << (double)(t2-t1)/CLOCKS_PER_SEC << endl;
    print(B, ArrSize);
    
    //merger sort
    for(int i = 0; i < ArrSize; ++i)
        B[i] = A[i];
    t1 = clock();
    merger_sort(B, ArrSize);
    t2 = clock();
    cout << "merger sort" << endl;
    cout << "Time: " << (double)(t2-t1)/CLOCKS_PER_SEC << endl;
    print(B, ArrSize);
    
    return 0;
}


void print(int arr[], int arr_size){
    for (int i = 0; i < arr_size; ++i)
        cout << arr[i] << " ";
    cout <<"\n================================================" << endl;
}


