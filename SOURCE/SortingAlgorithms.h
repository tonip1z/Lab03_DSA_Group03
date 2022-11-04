#pragma once

//Please write prototypes in the same order as in funcion definitions
//e.g SelectionSort prototypes
//    InsertionSort prototypes
//    ...

//Function prototypes for each sorting algorithm goes here

//7. RadixSort
void RadixSort(int a[], int n);
int getMax(int a[], int n);
void CountRadix(int a[], int n, int exp);

//10. CountingSort
void CountingSort(int arr[], int n);

//11. FlashSort
long long FlashSort(int a[], int n);
long long InsertionSort(int a[], int n, long long &nComp);        //Temporary
int GetClass(int value, int minValue, int maxValue, int m);
long long ClassPermute(int a[], int n, int minValue, int maxValue, int freq[], int m);
long long ClassSort(int a[], int n, int freq[], int m);
long long Classify(int a[], int n, int& minValue, int& maxValue, int freq[], int m);