#pragma once

//Please write prototypes in the same order as in funcion definitions
//e.g SelectionSort prototypes
//    InsertionSort prototypes
//    ...

//Function prototypes for each sorting algorithm goes here
//1. SelectionSort
void SelectionSort(int a[], int n);

//3. BubbleSort
void BubbleSort(int a[], int n);
void BubbleSort_with_flag(int a[], int n);

//5. MergeSort
void MergeSort(int a[], int n);
void MergeRun(int a[], int temp[], int p, int t, int q);
void Sort_on_Run(int a[],int temp[],int p, int q);

//7. RadixSort
void RadixSort(int a[], int n);

//9. ShellSort
void ShellSort(int a[],int n);

//10. CountingSort
void CountingSort(int arr[], int n);

//11. FlashSort
long long FlashSort(int a[], int n);
long long InsertionSort(int a[], int n, long long &nComp);        //Temporary
int GetClass(int value, int minValue, int maxValue, int m);
long long ClassPermute(int a[], int n, int minValue, int maxValue, int freq[], int m);
long long ClassSort(int a[], int n, int freq[], int m);
long long Classify(int a[], int n, int& minValue, int& maxValue, int freq[], int m);