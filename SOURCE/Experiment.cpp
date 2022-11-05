#include <iostream>
#include "DataGenerator.h"
#include "SortingAlgorithms.h"
#include "Experiment.h"

using namespace std;

//SORT_ALGO[] definition
//SORT_ALGO[] is an array of function pointers, each points to the corresponding sorting algorithm in order as follow:
//      SORT_ALGO[0] points to SelectionSort()
//      SORT_ALGO[1] points to InsertionSort()
//      SORT_ALGO[2] points to BubbleSort()
//      SORT_ALGO[3] points to HeapSort()
//      SORT_ALGO[4] points to MergeSort()
//      SORT_ALGO[5] points to QuickSort()
//      SORT_ALGO[6] points to RadixSort()
//      SORT_ALGO[7] points to ShakerSort()
//      SORT_ALGO[8] points to ShellSort()
//      SORT_ALGO[9] points to CountingSort()
//      SORT_ALGO[10] points to FlashSort()

//Thank you Mr. Pham Nguyen Son Tung for introducing us to function pointers
void (*SORT_ALGO[11])(int* a, int n, long long &num_Comp) = {SelectionSort, InsertionSort, BubbleSort, HeapSort, MergeSort, QuickSort, RadixSort, ShakerSort, ShellSort, CountingSort, FlashSort};

//DATA_SIZE definition:
//      DATA_SIZE[0] = 10000
//      DATA_SIZE[1] = 30000
//      DATA_SIZE[2] = 50000
//      DATA_SIZE[3] = 100000
//      DATA_SIZE[4] = 300000
//      DATA_SIZE[5] = 500000

void Experiment()
{
    //for each DATA_SIZE
    for (int i = 0; i < 6; i++)
    {
        int* a = new int[DATA_SIZE[i]];

        //for each sorting algorithm
        for (int j = 0; j < 10; j++)
        {

        }

        delete[] a;
    }
}