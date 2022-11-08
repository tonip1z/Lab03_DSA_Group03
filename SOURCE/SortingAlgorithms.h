#pragma once

//Please write prototypes in the same order as in funcion definitions
//e.g SelectionSort prototypes
//    InsertionSort prototypes
//    ...

//Function prototypes for each sorting algorithm goes here
//1. SelectionSort
void SelectionSort(int* a, int n, unsigned long long &num_Comp);

//2. InsertionSort
void InsertionSort(int* a, int n, unsigned long long &num_Comp);

//3. BubbleSort
void BubbleSort(int* a, int n, unsigned long long &num_Comp);
void BubbleSort_with_flag(int* a, int n, unsigned long long &num_Comp);

//4. HeapSort
void HeapSort(int* a, int n, unsigned long long &num_Comp);
void HeapConstruct(int* a, int n, unsigned long long &num_Comp);
void HeapRebuild(int index, int* a, int n, unsigned long long &num_Comp);

//5. MergeSort
void MergeSort(int* a, int n, unsigned long long &num_Comp);
void MergeRun(int* a, int temp[], int p, int t, int q, unsigned long long &num_Comp);
void Sort_on_Run(int* a,int temp[],int p, int q, unsigned long long &num_Comp);

//6. QuickSort
void QuickSort(int* a, int n, unsigned long long &num_Comp);

//7. RadixSort
void RadixSort(int* a, int n, unsigned long long &num_Comp);

//8. ShakerSort
void ShakerSort(int* a, int n, unsigned long long &num_Comp);

//9. ShellSort
void ShellSort(int* a, int n, unsigned long long &num_Comp);

//10. CountingSort
void CountingSort(int* a, int n, unsigned long long &num_Comp);

//11. FlashSort
void FlashSort(int* a, int n, unsigned long long &num_Comp);
void FlashInsertionSort(int* a, int n, unsigned long long &num_Comp);       //Temporary
int GetClass(int value, int minValue, int maxValue, int m, unsigned long long &num_Comp);
void ClassPermute(int* a, int n, int minValue, int maxValue, int freq[], int m, unsigned long long &num_Comp);
void ClassSort(int* a, int n, int freq[], int m, unsigned long long &num_Comp);
void Classify(int* a, int n, int& minValue, int& maxValue, int freq[], int m, unsigned long long &num_Comp);
