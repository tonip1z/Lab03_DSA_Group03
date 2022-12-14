#include <iostream>
#include "SortingAlgorithms.h"

#define MAX_VAL 500001 //used in CountingSort

using namespace std;

//Remember the naming standard: [Algorithm_name]Sort() e.g: QuickSort(), BubbleSort(),...
//Function prototypes goes to "SortingAlgorithms.h"
//Please implement the sorting algorithms in order as follow to avoid merge conflict:
//1. SelectionSort
//2. InsertionSort
//3. BubbleSort
//4. HeapSort
//5. MergeSort
//6. QuickSort
//7. RadixSort
//8. ShakerSort
//9. ShellSort
//10. CountingSort
//11. FlashSort

//Implementation goes here, write code in corresponding section for each algorithm
//----------------------------------------------//
//1. SelectionSort
// In Selection Sort, we will have an array unsorted or nearly sorted. The idea of this is to find the smallest 
// value (for the ascended array) or the largest value (for the descended array) and put it into the first position 
// of the part of the array we need to sort. This process continues until the array is fully sorted.
void SelectionSort(int* a, int n, unsigned long long &num_Comp) 
{
    num_Comp = 0;
    for (int i = 0; (++num_Comp) && (i < n - 1); i++)
    {
        int k_min = i;
        for (int j = i + 1; (++num_Comp) && (j < n); j++)
            if ((++num_Comp) && (a[k_min] > a[j]))      //find the smallest value 
                k_min = j;
        swap(a[i], a[k_min]);
    }
}

//----------------------------------------------//
//2. InsertionSort
//this implementation was refered from: https://www.geeksforgeeks.org/insertion-sort/
void InsertionSort(int* a, int n, unsigned long long &num_Comp)
{
    num_Comp = 0;
	int i, j, key;
	for (i = 1; (++num_Comp) && (i < n); i++)
	{
		key = a[i];
		j = i - 1;
		while ((++num_Comp) && (j >= 0) && (++num_Comp) && (a[j] > key)) //if (a[i] > key) is false, still count the comparison itself, although this is compiler dependent
		{
			a[j + 1] = a[j]; 
			j = j - 1;
		}
		a[j + 1] = key;
	}
}

//----------------------------------------------//
//3. BubbleSort
//The idea for BubbleSort was refered from "A Common-Sense Guide to Data Structures and Algorithms: Level Up Your Core Programming Skills", 2nd edition, by Jay Wengrow, at page 48
//This is a implementation for that idea, along with another implementation that uses flags
void BubbleSort(int* a, int n, unsigned long long &num_Comp)
{
    num_Comp = 0;
    for (int i = 0; (++num_Comp) && (i < n - 1); i++)
        for (int j = n - 1; (++num_Comp) && (j > i); j--)
            if ((++num_Comp) && (a[j] < a[j - 1]))
                swap(a[j], a[j - 1]);
}

void BubbleSort_with_flag(int* a, int n, unsigned long long &num_Comp)
{
    num_Comp = 0;
    int i = 0;
    bool flag = true;
    while ((++num_Comp) && (flag))
    {
        flag = false;
        for (int j = n - 1; (++num_Comp) && (j > i); j--)
        {
            if ((++num_Comp) && (a[j] < a[j - 1]))
            {
                swap(a[j], a[j - 1]);
                flag = true;
            }
            i++;
        }
    }
}

//----------------------------------------------//
//4. HeapSort
//this implementation was refered from: https://www.geeksforgeeks.org/heap-sort/
void HeapRebuild(int index, int* a, int n, unsigned long long &num_Comp)
{
	int max = index;
	int j = 2 * max + 1;
	int k = 2 * max + 2;
	if ((++num_Comp) && (j <= n) && (++num_Comp) && (a[max] < a[j]))
		max = j;
	if ((++num_Comp) && (k <= n) && (++num_Comp) && (a[max] < a[k]))
		max = k;
	if ((++num_Comp) && (max != index))
	{
		swap(a[index], a[max]);
		HeapRebuild(max, a, n, num_Comp);
	}
}

void HeapConstruct(int* a, int n, unsigned long long &num_Comp)
{
	int index;
	for (index = n / 2 - 1; (++num_Comp) && (index >= 0); index--)
		HeapRebuild(index, a, n, num_Comp);
}

void HeapSort(int* a, int n, unsigned long long &num_Comp)
{
    num_Comp = 0;
	HeapConstruct(a, n, num_Comp);
	int m = n - 1;
	while ((++num_Comp) && (m > 0))
	{
		swap(a[0], a[m]);
		m = m - 1;
		HeapRebuild(0, a, m, num_Comp);
	}
}

//----------------------------------------------//
//5. MergeSort
// Merge Sort with Recursion (using divide and conquer technique).
// Basically, the sort itself means: Array(Unsorted) = Run1(Unsorted) + Run2(Unsorted) -> Run1(Sorted) + Run2(Sorted) = Array(Sorted) 
// This is a flexible merge sort, can be used to sort all values in array a or part of it, just by changing the range p and q.
// The arguments contain array a (unsorted), array temp to store the answer, begin, pivot, end (of the sorting range).
// Using the pivot, array a has been splitted into two runs: the first half and the second half of the original array. 

//This idea was refered in "Giao trinh Cau truc du lieu va Giai thuat" by professor Do Xuan Loi, in the section for Merge Sort (sap xep tron), page 228
//This implementation was largely inspired by professor Do Xuan Loi as well
void MergeRun(int* a, int temp[], int p, int t, int q, unsigned long long &num_Comp)     
{
    int m = 0;      // starting point of array temp
    int n = t - 1;    //end point of the first run
    int i = p;
    int j = t;
    
    while (((++num_Comp) && (i <= n)) && ((++num_Comp) && (j <= q)))
    {
        if((++num_Comp) && (a[i] <= a[j]))
        {
            temp[m] = a[i];
            i++;
        }
        else
        {
            temp[m] = a[j];
            j++;
        }
        m++;
    }
    
    // Put the rest of the first run into array temp
    for (int r = i; (++num_Comp) && (r <= n); r++)
    {
        temp[m] = a[r];
        m++;
    }
    
    // Put the rest of the second run into array temp
    for (int r = j; (++num_Comp) && (r <= q); r++)
    {
        temp[m] = a[r];
        m++;
    }

    // Print all values from array temp back to array a
    for (int r = 0; (++num_Comp) && (r < m); r++)
        a[p + r] = temp[r];
}

void Sort_on_Run(int* a, int temp[], int p, int q, unsigned long long &num_Comp)
{
    if ((++num_Comp) && (p < q))
    {
        int k = (p + q) / 2; // Split the array into 2
        Sort_on_Run(a, temp, p, k, num_Comp);
        Sort_on_Run(a, temp, k + 1, q, num_Comp);
        MergeRun(a, temp, p, k + 1, q, num_Comp);
    }
}

void MergeSort(int* a, int n, unsigned long long &num_Comp)
{
    num_Comp = 0;
    int* temp = new int[n];
    Sort_on_Run(a, temp, 0, n - 1, num_Comp);
    delete[] temp;
}

//----------------------------------------------//
//6. QuickSort
//This implemetation of left-pivot Quick sort was refered in "Algorithms in a Nutshell: A Practical Guide" by George T. Heineman
//An online version of this book is available on the learning platform O'Reilly
//A section for Quick Sort can be found here: https://www.oreilly.com/library/view/algorithms-in-a/9780596516246/ch04s04.html?fbclid=IwAR35mN7sHevpsu2UPMkC-4unMsV_Gqar14eALLI63QSAua6GgBxlgU87GEg

int Partition(int* a, int left, int right, unsigned long long &num_Comp) //Return the pivot position while arranging all the elements to their correct sub-array
{
    int pivot = a[left];
    int i = right;
    
    for (int j = right; (++num_Comp) && (j > left); j--)
        if ((++num_Comp) && (a[j] > pivot))
        {
            swap(a[i], a[j]);
            i--;
        }

    swap(a[i], a[left]);
    return i;
}

void QS_Recursion(int* a, int left, int right, unsigned long long &num_Comp) 
{
	if ((++num_Comp) && (right <= left))
		return;

	int SplitPoint = Partition(a, left, right, num_Comp);

	QS_Recursion(a, left, SplitPoint - 1, num_Comp);
	QS_Recursion(a, SplitPoint + 1, right, num_Comp);
}

void QuickSort(int* a, int n, unsigned long long &num_Comp)
{
    num_Comp = 0;
    //we have to seperate the function itself to match the function pointer format
    QS_Recursion(a, 0, n - 1, num_Comp);
}

//----------------------------------------------//
//7. RadixSort
// Least Significant Decimal Radix Sort
void RadixSort(int* a, int n, unsigned long long &num_Comp)
{
    num_Comp = 0;

    const int base = 10;     // Number of "buckets" = 10
    int bucket[base];
    int* p = new int[n];

    int max = a[0];
    for (int i = 1; (++num_Comp) && (i < n); i++)
        if ((++num_Comp) && (a[i] > max))
            max = a[i];
    int weight = 1;

    while ((++num_Comp) && (max / weight > 0))
    {
        // Create empty buckets (starting value of every bucket = 0) 
        for(int i = 0; (++num_Comp) && (i < base); i++)
            bucket[i] = 0;  // In here we use the 'bucket' array to count the number of values later on 
        
        // Count the number of values of each bucket, one by one
        for(int i = 0; (++num_Comp) && (i < n); i++)
            bucket[(a[i] / weight) % base]++;

        // Count the number of values that have been listed in the buckets
        for(int i = 1; (++num_Comp) && (i < base); i++)
            bucket[i] += bucket[i - 1];
        
        // Putting values into buckets (bucket[i] loops because bucket[i] = n, the number of values in array a)
        for(int i = n - 1; (++num_Comp) && (i >= 0); i--)
        {
            bucket[(a[i] / weight) % base]--;
            p[bucket[(a[i] / weight) % base]] = a[i];
        }

        // Return values in each bucket back to array a, one by one
        for(int i = 0; (++num_Comp) && (i < n); i++)
            a[i] = p[i];
        
        weight = weight * base; // Next weight 
    }

    delete[] p;
}
//----------------------------------------------//
//8. ShakerSort
//this implementation was inspired by: https://www.geeksforgeeks.org/cocktail-sort/
void ShakerSort(int* a, int n, unsigned long long &num_Comp)
{
    num_Comp = 0;

	int left = 0;
	int right = n;

	while ((++num_Comp) && (left < right))
	{
		bool sorted = true;
		right--;
		for (int i = left; (++num_Comp) && (i < right); i++)
		{
			if ((++num_Comp) && (a[i] > a[i + 1]))
			{
				int tmp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = tmp;
				sorted = false;
			}
		}

		if ((++num_Comp) && (sorted)) 
            break;

		left++;
		sorted = true;
		for (int i = right - 1; (++num_Comp) && (i >= left); i--)
		{
			if ((++num_Comp) && (a[i] < a[i - 1]))
			{
				int tmp = a[i];
				a[i] = a[i - 1];
				a[i - 1] = tmp;
				sorted = false;
			}
		}
        
		if ((++num_Comp) && (sorted)) 
            break;
	}
}

//----------------------------------------------//
//9. ShellSort
//the idea for ShellSort was refered from: https://www.geeksforgeeks.org/shellsort/
void ShellSort(int* a, int n, unsigned long long &num_Comp)
{
    num_Comp = 0;

    // m is the quantity of values of array h (which contains the lengths of a gap between array a' values in each case)
    int m = 3;  
    int h[] = {1, 2, 3};

    for (int r = m - 1; (++num_Comp) && (r >= 0); r--)
    {
        int k = h[r];
        for (int i = k; (++num_Comp) && (i < n); i++)
        {
            int x = a[i];
            int j = i - k;
            bool cont = true;
            while ((++num_Comp) && (j >= 0) && cont)
            {
                if ((++num_Comp) && (a[j] > x))
                {
                    a[j + k] = a[j];
                    j = j - k;
                }
                else 
                    cont = false;
                a[j + k] = x;
            }
        }
    }
}


//----------------------------------------------//
//10. CountingSort
//this implementation was inspired by: https://www.geeksforgeeks.org/counting-sort/
void CountingSort(int* a, int n, unsigned long long &num_Comp)
{
    num_Comp = 0;

    int* tmp = new int[n];             
    int count[MAX_VAL] = { 0 };       

    for (int i = 0; (++num_Comp) && (i < n); i++) 
        ++count[a[i]];
       
    for (int i = 1; (++num_Comp) && (i < MAX_VAL); i++)
        count[i] += count[i - 1];
    
    for (int i = 0; (++num_Comp) && (i < n); i++) 
    {
        tmp[count[a[i]] - 1] = a[i];
        --count[a[i]];
    }

    for (int i = 0; (++num_Comp) && (i < n); i++) 
        a[i] = tmp[i];
}

//----------------------------------------------//
//11. FlashSort
//the idea for FlashSort was refered in the February 1998 "Dr. Dobb's Journal: The Flashsort1 Algorithm" by Karl-Dietrich Neuber 
//the implementation is largely inspired by him as well
//Learn more: https://www.drdobbs.com/database/the-flashsort1-algorithm/184410496?fbclid=IwAR3tuwTWh6Tb0tBTyCVGmaPuTuV_0zN3ylDEMwKpBvqB_YG_H3fDxWZBjUo
void FlashInsertionSort(int* a, int n, unsigned long long &num_Comp)
{
	for (int i = 1; (++num_Comp) && (i < n); ++i) 
    {
		int currentValue = a[i];
		int j;

		for (j = i; (++num_Comp) && (j > 0); --j) 
        {
			if ((++num_Comp) && (a[j - 1] <= currentValue))
				break;
			a[j] = a[j - 1];
		}

		a[j] = currentValue;
	}
}

int GetClass(int value, int minValue, int maxValue, int m, unsigned long long &num_Comp)
{
	return 1 + ((((long long)(m - 1)) * (value - minValue)) / (maxValue - minValue));
}

void ClassPermute(int* a, int n, int minValue, int maxValue, int freq[], int m, unsigned long long &num_Comp)
{
	int num_Move = 1;
	int i = 0;
	int k = m;
	int foo;
	int bar;

	while ((++num_Comp) && (num_Move <= n)) 
    {
		while ((++num_Comp) && (i > freq[k] - 1)) 
        {
			i++;
			k = GetClass(a[i], minValue, maxValue, m, num_Comp);
		}

		foo = a[i];
		while ((++num_Comp) && (i <= freq[k] - 1)) 
        {
			k = GetClass(foo, minValue, maxValue, m, num_Comp);

			bar = a[--freq[k]];
			a[freq[k]] = foo;
			foo = bar;

			num_Move++;
		}
	}
}

void ClassSort(int* a, int n, int freq[], int m, unsigned long long &num_Comp)
{
	for (int k = 2; (++num_Comp) && (k <= m); ++k)
	{
		FlashInsertionSort(a + freq[k - 1], freq[k] - freq[k - 1], num_Comp);
	}
}

void Classify(int* a, int n, int& minValue, int& maxValue, int freq[], int m, unsigned long long &num_Comp)
{
	minValue = a[0];
	maxValue = a[0];

	for (int i = 1; (++num_Comp) && (i < n); ++i) 
    {
		if ((++num_Comp) && (a[i] < minValue))
			minValue = a[i];

		if ((++num_Comp) && (a[i] > maxValue))
			maxValue = a[i];
	}

	for (int i = 0; (++num_Comp) && (i < n); ++i)
		++freq[GetClass(a[i], minValue, maxValue, m, num_Comp)];

	for (int i = 1; (++num_Comp) && (i <= m); ++i)
		freq[i] += freq[i - 1];
}

void FlashSort(int* a, int n, unsigned long long &num_Comp)
{
	num_Comp = 0;
    
	int m = (int)(0.43 * n);

	int* L = new int[m + 1];

	for (int i = 0; (++num_Comp) && (i <= m); i++)
		L[i] = 0;

	if ((++num_Comp) && (!L))
		return;

	int minValue, maxValue;

	Classify(a, n, minValue, maxValue, L, m, num_Comp);
	ClassPermute(a, n, minValue, maxValue, L, m, num_Comp);
	ClassSort(a, n, L, m, num_Comp);

	delete[] L;
}
