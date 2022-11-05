#include <iostream>
#include "SortingAlgorithms.h"

#define MAX_VAL 100001 //used for CountingSort

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
void SelectionSort(int a[], int n) 
{
    for (int i = 0; i < n - 1; i++)
    {
        int k_min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (a[k_min] > a[j])
            {
                k_min = j;
                swap(a[i], a[k_min]);
            }
        }
    }
}

//----------------------------------------------//
//2. InsertionSort


//----------------------------------------------//
//3. BubbleSort
void BubbleSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (a[j] < a[j - 1])
            {
                swap(a[j], a[j - 1]);
            }
        }
    }
}

void BubbleSort_with_flag(int a[], int n)
{
    int i = 0;
    bool flag;
    while (flag)
    {
        flag = false;
        for (int j = n - 1; j > i; j--)
        {
            if (a[j] < a[j - 1])
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


//----------------------------------------------//
//5. MergeSort
// Merge Sort with Recursion (using divide and conquer technique).
// Basically, the sort itself means: Array(Unsorted) = Run1(Unsorted) + Run2(Unsorted) -> Run1(Sorted) + Run2(Sorted) = Array(Sorted) 
// This is a flexible merge sort, can be used to sort all values in array a or part of it, just by changing the range p and q.

//The arguments contain array a (unsorted), array temp to store the answer, begin, pivot, end (of the sorting range).
// Using the pivot, array has splitted into two runs: the first half and the second half of the original array. 
void MergeRun(int a[], int temp[], int p, int t, int q)     
{
    int m = 0;      // starting point of array temp
    int n = t - 1;    //end point of the first run
    int i = p;
    int j = t;
    
    while ((i <= n) && (j <= q))
    {
        if(a[i] <= a[j])
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
    for (int r = i; r <= n; r++)
    {
        temp[m] = a[r];
        m++;
    }
    
    // Put the rest of the second run into array temp
    for (int r = j; r <= q; r++)
    {
        temp[m] = a[r];
        m++;
    }
}

void Sort_on_Run(int a[],int temp[],int p, int q)
{
    if (p < q)
    {
        int k = (p + q)/2; // Choosing pivot at the middle of array a
        Sort_on_Run(a, temp, p, k);
        Sort_on_Run(a, temp, k + 1, q);
        MergeRun(a, temp, p, k + 1, q);
    }
}

void MergeSort(int a[], int n)
{
    int* temp = new int[n];
    Sort_on_Run(a, temp, 0, n - 1);
}


//----------------------------------------------//
//6. QuickSort


//----------------------------------------------//
//7. RadixSort
// Least Significant Decimal Radix Sort
void RadixSort(int a[], int n)
{
    const int base = 10;     // Number of "buckets" = 10
    int bucket[base];
    int* p = new int[n];

    int max = a[0];
    for(int i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];
    int weight = 1;
    while(max/weight > 0)
    {
        // Create empty buckets (starting value of every bucket = 0) 
        for(int i = 0; i < base; i++)
            bucket[i] = 0;  // In here we use the 'bucket' array to count the number of values later on 
        
        // Count the number of values of each bucket, one by one
        for(int i = 0; i < n; i++)
            bucket[(a[i]/weight) % base]++;

        // Count the number of values that have been listed in the buckets
        for(int i = 0; i < base; i++)
            bucket[i] = bucket[i] + bucket[i-1];

        // Putting values into buckets (bucket[i] loops because bucket[i] = n, the number of values in array a.)
        for(int i = n - 1; i >= 0; i--)
        {
            bucket[(a[i]/weight) % base]--;
            p[bucket[(a[i]/weight) % base]] = a[i];
        }
        
        // Return values in each bucket back to array a, one by one
        for(int i = 0; i < n; i++)
            a[i] = p[i];

        weight  = weight * base; // Next weight 
    }
}
//----------------------------------------------//
//8. ShakerSort
void ShakerSort(int a[], int n)
{
	int left = 0;
	int right = n;

	while (left < right)
	{
		bool sorted = true;
		right--;
		for (int i = left; i < right - 1; i++)
		{
			if (a[i] > a[i + 1])
			{
				int tmp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = tmp;
				sorted = false;
			}
		}
		if (sorted) break;
		left++;
		sorted = true;
		for (int i = right - 1; i >= left; i--)
		{
			if (a[i] < a[i - 1])
			{
				int tmp = a[i];
				a[i] = a[i - 1];
				a[i - 1] = tmp;
				sorted = false;
			}
		}
		if (sorted) break;
	}
}

//----------------------------------------------//
//9. ShellSort
void ShellSort(int a[],int n)
{
    int m = 3;
    int h[] = {1, 3, 7};
    for (int r = m - 1; r >= 0; r--)
    {
        int k = h[r];
        for (int i = k; i < n; i++)
        {
            int x = a[i];
            int j = i - k;
            bool cont = true;
            while ((j >= 0) && cont)
            {
                if (a[j] > x)
                {
                    a[j + k] = a[j];
                    j = j - k;
                }
                else cont = false;
                a[j + k] = x;
            }
        }
    }
}


//----------------------------------------------//
//10. CountingSort
void CountingSort(int arr[], int n)
{
    int* tmp = new int[n];             
    int count[MAX_VAL] = { 0 };   
	int num_comp = 0;          

   
    for (int i = 0; i < n; i++, num_comp++) {
        ++count[arr[i]];
    }

    
    for (int i = 1; i < MAX_VAL; i++, num_comp++) {
        count[i] += count[i - 1];
    }

    
    for (int i = 0; i < n; i++, num_comp++) {
        tmp[count[arr[i]] - 1] = arr[i];
        --count[arr[i]];
    }

  
    for (int i = 0; i < n; i++, num_comp++) {
        arr[i] = tmp[i];
    }
}

//----------------------------------------------//
//11. FlashSort
long long FlashInsertionSort(int a[], int n, long long &num_Comp)
{
	num_Comp = 0;

	for (int i = 1; ++num_Comp && i < n; ++i) {
		int currentValue = a[i];
		int j;

		for (j = i; ++num_Comp && j > 0; --j) {
			if (++num_Comp && a[j - 1] <= currentValue)
				break;
			a[j] = a[j - 1];
		}

		a[j] = currentValue;
	}
	
	return num_Comp;
}

int GetClass(int value, int minValue, int maxValue, int m)
{
	return 1 + ((((long long)(m - 1)) * (value - minValue)) / (maxValue - minValue));
}

long long ClassPermute(int a[], int n, int minValue, int maxValue, int freq[], int m)
{
	long long num_Comp = 0;
	int num_Move = 1;
	int i = 0;
	int k = m;
	int foo;
	int bar;

	while (++num_Comp && num_Move <= n) {
		while (++num_Comp && i > freq[k] - 1) {
			i++;
			k = GetClass(a[i], minValue, maxValue, m);
		}

		foo = a[i];
		while (++num_Comp && i <= freq[k] - 1) {
			k = GetClass(foo, minValue, maxValue, m);

			bar = a[--freq[k]];
			a[freq[k]] = foo;
			foo = bar;

			num_Move++;
		}
	}

	return num_Comp;
}

long long ClassSort(int a[], int n, int freq[], int m)
{
	long long nComp = 0;
	long long dummy = 0;
	for (int k = 2; ++nComp && k <= m; ++k)
	{
		FlashInsertionSort(a + freq[k - 1], freq[k] - freq[k - 1], dummy);
		nComp += dummy;
	}
		
	return nComp;
}

long long Classify(int a[], int n, int& minValue, int& maxValue, int freq[], int m)
{
	long long nComp = 0;

	minValue = a[0];
	maxValue = a[0];

	for (int i = 1; ++nComp && i < n; ++i) {
		if (++nComp && a[i] < minValue)
			minValue = a[i];

		if (++nComp && a[i] > maxValue)
			maxValue = a[i];
	}

	for (int i = 0; ++nComp && i < n; ++i)
		++freq[GetClass(a[i], minValue, maxValue, m)];

	for (int i = 1; ++nComp && i <= m; ++i)
		freq[i] += freq[i - 1];

	return nComp;
}

long long FlashSort(int a[], int n)
{
	long long num_Comp = 0;
	int m = (int)(0.43 * n);

	int* L = new int[m + 1];

	for (int i = 0; ++num_Comp && i <= m; i++)
		L[i] = 0;

	if (!L)
		return num_Comp;

	int minValue, maxValue;

	num_Comp += Classify(a, n, minValue, maxValue, L, m);
	num_Comp += ClassPermute(a, n, minValue, maxValue, L, m);
	num_Comp += ClassSort(a, n, L, m);

	delete[] L;

	return num_Comp;
}