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


//----------------------------------------------//
//2. InsertionSort


//----------------------------------------------//
//3. BubbleSort


//----------------------------------------------//
//4. HeapSort


//----------------------------------------------//
//5. MergeSort


//----------------------------------------------//
//6. QuickSort


//----------------------------------------------//
//7. RadixSort
int getMax(int a[], int n) {
	int Max = a[0];

	for (int i = 1; i < n; i++) {
		if (a[i] > Max) Max = a[i];
	}
	return(Max);
}

void CountRadix(int a[], int n, int exp) {
	int* tmp = new int[n];
	int count[10] = { 0 };

	for (int i = 0; i < n; i++) {
		count[(a[i] / exp) % 10]++;
	}

	for (int i = 1; i < 10; i++) {
		count[i] += count[i - 1];
	}

	for (int i = n - 1; i >= 0; i--) {
		tmp[count[(a[i] / exp) % 10] - 1] = a[i];
		count[(a[i] / exp) % 10]--;
	}

	for (int i = 0; i < n; i++) {
		a[i] = tmp[i];
	}
}


void RadixSort(int a[], int n) {
	int m = getMax(a, n);
	int i = 1;

	while (m / i > 0) {
		CountRadix(a, n, i);
		i *= 10;
	}
}

//----------------------------------------------//
//8. ShakerSort


//----------------------------------------------//
//9. ShellSort


//----------------------------------------------//
//10. CountingSort
void CountingSort(int arr[], int n)
{
    int* tmp = new int[n];             //Tao mang de luu ket qua sau khi sap xep
    int count[MAX_VAL] = { 0 };             //Tao mang dem

    //Dem so luong cua moi phan tu trong mang
    for (int i = 0; i < n; i++) {
        ++count[arr[i]];
    }

    //Cong so luong moi phan tu de tim vi tri cua moi phan tu trong mang
    for (int i = 1; i < MAX_VAL; i++) {
        count[i] += count[i - 1];
    }

    //Gan phan tu theo thu tu vao mang ket qua
    for (int i = 0; i < n; i++) {
        tmp[count[arr[i]] - 1] = arr[i];
        --count[arr[i]];
    }

    //Gan mang goc thanh mang da sap xep
    for (int i = 0; i < n; i++) {
        arr[i] = tmp[i];
    }
}

//----------------------------------------------//
//11. FlashSort
long long InsertionSort(int a[], int n)
{
	long long nComp = 0;

	for (int i = 1; ++nComp && i < n; ++i) {
		int currentValue = a[i];
		int j;

		for (j = i; ++nComp && j > 0; --j) {
			if (++nComp && a[j - 1] <= currentValue)
				break;
			a[j] = a[j - 1];
		}

		a[j] = currentValue;
	}

	return nComp;
}

int GetClass(int value, int minValue, int maxValue, int m)
{
	return 1 + ((((long long)(m - 1)) * (value - minValue)) / (maxValue - minValue));
}

long long ClassPermute(int a[], int n, int minValue, int maxValue, int freq[], int m)
{
	long long nComp = 0;
	int nMove = 1;
	int i = 0;
	int k = m;
	int foo;
	int bar;

	while (++nComp && nMove <= n) {
		while (++nComp && i > freq[k] - 1) {
			i++;
			k = GetClass(a[i], minValue, maxValue, m);
		}

		foo = a[i];
		while (++nComp && i <= freq[k] - 1) {
			k = GetClass(foo, minValue, maxValue, m);

			bar = a[--freq[k]];
			a[freq[k]] = foo;
			foo = bar;

			nMove++;
		}
	}

	return nComp;
}

long long ClassSort(int a[], int n, int freq[], int m)
{
	long long nComp = 0;
	for (int k = 2; ++nComp && k <= m; ++k)
		nComp += InsertionSort(a + freq[k - 1], freq[k] - freq[k - 1]);

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
	long long nComp = 0;
	int m = (int)(0.43 * n);

	int* L = new int[m + 1];

	for (int i = 0; ++nComp && i <= m; i++)
		L[i] = 0;

	if (!L)
		return nComp;

	int minValue, maxValue;

	nComp += Classify(a, n, minValue, maxValue, L, m);
	nComp += ClassPermute(a, n, minValue, maxValue, L, m);
	nComp += ClassSort(a, n, L, m);

	delete[] L;

	return nComp;
}