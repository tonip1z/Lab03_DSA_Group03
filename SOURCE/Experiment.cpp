#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <time.h>
#include "DataGenerator.h"
#include "SortingAlgorithms.h"
#include "Experiment.h"

using namespace std;

//supporting function prototypes
string getAlgoName(int algo_id);
string getDataOrder(int DataOrder);

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

//Special thanks to Mr. Pham Nguyen Son Tung for introducing us to function pointers
void (*SORT_ALGO[11])(int* a, int n, long long &num_Comp) = {SelectionSort, InsertionSort, BubbleSort, HeapSort, MergeSort, QuickSort, RadixSort, ShakerSort, ShellSort, CountingSort, FlashSort};

//DATA_SIZE definition:
//      DATA_SIZE[0] = 10000
//      DATA_SIZE[1] = 30000
//      DATA_SIZE[2] = 50000
//      DATA_SIZE[3] = 100000
//      DATA_SIZE[4] = 300000
//      DATA_SIZE[5] = 500000

//the definition itself is in "Experiment.h"

void Experiment()
{
    //The experiment result will be exported to the file "ExperimentResult.txt" in the project directory
    ofstream fout;
    fout.open("ExperimentResult.txt");
    if (fout.is_open())
    {
        long long num_Comp; //used to count number of comparison operation used in an algorithm
        clock_t start_time, end_time; //used to calculate runtime of an algorithm
        
        //for each Data Order
        for (int DataOrder = 0; DataOrder < 4; DataOrder++)
        {
            fout << "\nDATA ORDER: " << getDataOrder(DataOrder) << "\n";
            //for each Data Size
            for (int size_id = 0; size_id < 6; size_id++)
            {
                //create and generate data for a dynamic array of size DATA_SIZE[size_id] and of corresponding data order type 
                int* a = new int[DATA_SIZE[size_id]];
                GenerateData(a, DATA_SIZE[size_id], DataOrder);

                fout << "   DATA SIZE: " << DATA_SIZE[size_id] << "\n";
                //every sorting algorithm uses the same data set
                //for each sorting algorithm
                for (int algo_id = 0; algo_id < 11; algo_id++)
                {
                    //method used for getting runtime was suggested by stackoverflow user Thomas Pornin in the thread: https://stackoverflow.com/questions/5248915/execution-time-of-c-program
                    start_time = clock();
                    (*SORT_ALGO[algo_id])(a, DATA_SIZE[size_id], num_Comp);
                    end_time = clock();

                    fout << "       Algorithm: " << getAlgoName(algo_id) << "\n";
                    fout << "               Runtime (in millisecond): " << fixed << setprecision(6) << (double(end_time - start_time)) / CLOCKS_PER_SEC * 1000 << "\n";
                    fout << "               Comparisons: " << num_Comp << "\n";
                }

                delete[] a;
            }
        }
        fout.close();
    }
    else
        cout << "Cannot open 'ExperimentResult.txt'.\n";

    
}

string getAlgoName(int algo_id)
{
    switch (algo_id)
    {
        case 0:
            return "SelectionSort";
            break;
        case 1:
            return "InsertionSort";
            break;
        case 2:
            return "BubbleSort";
            break;
        case 3:
            return "HeapSort";
            break;
        case 4:
            return "MergeSort";
            break;
        case 5:
            return "QuickSort";
            break;
        case 6:
            return "RadixSort";
            break;
        case 7:
            return "ShakerSort";
            break;
        case 8:
            return "ShellSort";
            break;
        case 9:
            return "CountingSort";
            break;
        case 10:
            return "FlashSort";
            break;
        default:
            return "invalid algo_id";
            break;
    }
}

string getDataOrder(int DataOrder)
{
    switch (DataOrder)
    {
        case 0:
            return "Randomized";
            break;
        case 1:
            return "Sorted";
            break;
        case 2:
            return "Reversely sorted";
            break;
        case 3:
            return "Nearly sorted";
            break;
        default:
            return "invalid DataOrder_id";
            break;
    }
}