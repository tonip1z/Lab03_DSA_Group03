#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono> //we chose chrono library over time.h because it provides a high resolution clock which help measuring run time more accurate
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
    ofstream Efout;
    Efout.open("ExperimentResult.txt");
    if (Efout.is_open())
    {
        long long num_Comp; //used to count number of comparison operation used in an algorithm
        
        //for each Data Order
        for (int DataOrder = 1; DataOrder < 2; DataOrder++)
        {
            Efout << "\nDATA ORDER: " << getInputOrder(DataOrder) << "\n";
            //for each Data Size
            for (int size_id = 0; size_id < 6; size_id++)
            {
                //create and generate data for a dynamic array of size DATA_SIZE[size_id] and of corresponding data order type 
                int* dataSet = new int[DATA_SIZE[size_id]];
                GenerateData(dataSet, DATA_SIZE[size_id], DataOrder);

                Efout << "----DATA SIZE: " << DATA_SIZE[size_id] << "\n";
                
                //for each sorting algorithm (11 in total)
                for (int algo_id = 0; algo_id < 11; algo_id++)
                {
                    //every sorting algorithm uses the same data set so we have to form a copy from the original set for each algorithm
                    int* a = copyFromDataSet(dataSet, DATA_SIZE[size_id]);

                    //method used for getting runtime was refered from: https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/
                    auto start_time = chrono::high_resolution_clock::now();
                    (*SORT_ALGO[algo_id])(a, DATA_SIZE[size_id], num_Comp);
                    auto end_time = chrono::high_resolution_clock::now();    

                    double run_time_micro = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
                    double run_time_milli = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
                    
                    Efout << "_________Algorithm: " << getAlgoName(algo_id) << "\n";
                    Efout << "               Runtime (in microseconds): " << fixed << setprecision(5) << run_time_micro << "\n";
                    Efout << "               Runtime (in milliseconds): " << fixed << setprecision(5) << run_time_milli << "\n";
                    Efout << "               Comparisons: " << num_Comp << "\n";       

                    Efout.flush();
                    delete[] a;
                }

                delete[] dataSet;
            }
        }

        Efout.close();
    }
    else
        cout << "Cannot open 'ExperimentResult.txt'.\n";

    cout << "Experimenting finished!\n";
}

//This TestAlgorithm() function is used to test the correctness of the implementation for each algorithm 
//(ie. the sort result is in ascending order or not)
//This test function uses data set of 100 randomized integers
//return true if the implementation PASSED the test, otherwise return false - the implementation FAILED the test
bool TestAlgorithm(int algo_id)
{
    int* testDataSet = new int[100];
    long long num_Comp;
    bool PASSED = true;

    GenerateRandomData(testDataSet, 100);

    (*SORT_ALGO[algo_id])(testDataSet, 100, num_Comp);

    for (int i = 1; i < 100; i++)
        if (testDataSet[i] < testDataSet[i - 1])
        {
            PASSED = false;
            break;
        }

    delete[] testDataSet;
    return PASSED;
}

//Command line function definitions
void Command_1(char* algo_name, char* input_filename, char* output_param)
{
    int algo_id = getAlgoId(algo_name);

    cout << "Algorithm: " << getAlgoName(algo_id) << "\n";
    cout << "Input file: " << input_filename << "\n";

    ifstream fin;
    fin.open(input_filename);
    if (fin.is_open())
    {
        int n;
        int* a;
        long long num_Comp;

        fin >> n;
        cout << "Input size: " << n << "\n";
        cout << "-------------------------\n";
        a = new int[n];

        for (int i = 0; i < n; i++)
            fin >> a[i];

        auto start_time = chrono::high_resolution_clock::now();
        (*SORT_ALGO[algo_id])(a, n, num_Comp);
        auto end_time = chrono::high_resolution_clock::now();

        if (strcmp(output_param, "-both") == 0)
        {
            double time_taken_micro = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
            cout << "Running time: " << fixed << setprecision(5) << time_taken_micro / 1000 << " ms\n";
            cout << "Comparisons: " << num_Comp << "\n";
        }
        else if (strcmp(output_param, "-time") == 0)
        {
            double time_taken_micro = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
            cout << "Running time: " << fixed << setprecision(5) << time_taken_micro / 1000 << " ms\n";
        }
        else if (strcmp(output_param, "-comp") == 0)
        {
            cout << "Comparisons: " << num_Comp << "\n";
        }

        cout << "\n";

        //Writing results to "output.txt"
        ofstream fout;
        fout.open("output.txt");
        if (fout.is_open())
        {
            fout << n << "\n";
            for (int i = 0; i < n; i++)
                fout << a[i] << " ";

            fout.close();
        }
        else
            cout << "Cannot open 'output.txt'.\n";
        delete[] a;
        fin.close();
    }
    else
        cout << "Cannot open '" << input_filename << "'.\n";
}

void Command_2(char* algo_name, int size, char* input_order, char* output_param)
{
    int algo_id = getAlgoId(algo_name);

    cout << "Algorithm: " << getAlgoName(algo_id) << "\n";
    cout << "Input size: " << size << "\n";
    cout << "Input order: " << getInputOrder(input_order) << "\n";
    cout << "-------------------------\n";

    int* a = new int[size];
    long long num_Comp;

    if (strcmp(input_order, "-rand") == 0)
        GenerateRandomData(a, size);
    else if (strcmp(input_order, "-sorted") == 0)
        GenerateSortedData(a, size);
    else if (strcmp(input_order, "-nsorted") == 0)
        GenerateNearlySortedData(a, size);
    else if (strcmp(input_order, "-rev") == 0)
        GenerateReverseData(a, size);
    
    //Write generated data set to "input.txt"
    ofstream fout;
    fout.open("input.txt");
    if (fout.is_open())
    {
        fout << size << "\n";
        for (int i = 0; i < size; i++)
            fout << a[i] << " ";

        fout.close();
    }
    else
        cout << "Cannot open 'input.txt'.\n";

    auto start_time = chrono::high_resolution_clock::now();
    (*SORT_ALGO[algo_id])(a, size, num_Comp);
    auto end_time = chrono::high_resolution_clock::now();

    if (strcmp(output_param, "-both") == 0)
    {
        double time_taken_micro = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        cout << "Running time: " << fixed << setprecision(5) << time_taken_micro / 1000 << " ms\n";
        cout << "Comparisons: " << num_Comp << "\n";
    }
    else if (strcmp(output_param, "-time") == 0)
    {
        double time_taken_micro = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        cout << "Running time: " << fixed << setprecision(5) << time_taken_micro / 1000 << " ms\n";
    }
    else if (strcmp(output_param, "-comp") == 0)
        cout << "Comparisons: " << num_Comp << "\n";
    
    cout << "\n";

    fout.open("output.txt");
    if (fout.is_open())
    {
        fout << size << "\n";
        for (int i = 0; i < size; i++)
            fout << a[i] << " ";

        fout.close();
    }
    else
         cout << "Cannot open 'output.txt'.\n";

    delete[] a;
}

void Command_3(char* algo_name, int size, char* output_param)
{
    int algo_id = getAlgoId(algo_name);

    cout << "Algorithm: " << getAlgoName(algo_id) << "\n";
    cout << "Input size: " << size << "\n\n";
    
    Command_3_InputOrder(algo_id, size, 0, output_param); //Input order: Randomized
    Command_3_InputOrder(algo_id, size, 3, output_param); //Input order: Nearly sorted
    Command_3_InputOrder(algo_id, size, 1, output_param); //Input order: Sorted
    Command_3_InputOrder(algo_id, size, 2, output_param); //Input order: Reversely sorted
}

void Command_4(char* algo1_name, char* algo2_name, char* input_filename)
{
    int algo1_id = getAlgoId(algo1_name);
    int algo2_id = getAlgoId(algo2_name);

    cout << "Algorithm: " << getAlgoName(algo1_id) << " | " << getAlgoName(algo2_id) << "\n";
    cout << "Input file: " << input_filename << "\n";
    
    ifstream fin;
    fin.open(input_filename);
    if (fin.is_open())
    {
        int n;
        int* dataSet;
        long long num_Comp_1, num_Comp_2;

        fin >> n;
        cout << "Input size: " << n << "\n";
        cout << "-------------------------\n";
        dataSet = new int[n];

        for (int i = 0; i < n; i++)
            fin >> dataSet[i];

        int* a = copyFromDataSet(dataSet, n);
        int* b = copyFromDataSet(dataSet, n);
        
        auto start_time = chrono::high_resolution_clock::now();
        (*SORT_ALGO[algo1_id])(a, n, num_Comp_1);
        auto end_time = chrono::high_resolution_clock::now();

        double run_time_1 = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

        start_time = chrono::high_resolution_clock::now();
        (*SORT_ALGO[algo2_id])(b, n, num_Comp_2);
        end_time = chrono::high_resolution_clock::now();

        double run_time_2 = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

        cout << "Running time: " << fixed << setprecision(5) << run_time_1 / 1000 << " ms | " << run_time_2 / 1000 << " ms\n";
        cout << "Comparisons: " << num_Comp_1 << " | " << num_Comp_2 << "\n";

        delete[] a;
        delete[] b;
        delete[] dataSet;
        fin.close();
    }
    else
        cout << "Cannot open '" << input_filename << "'.\n";
}

void Command_5(char* algo1_name, char* algo2_name, int size, char* input_order)
{
    int algo1_id = getAlgoId(algo1_name);
    int algo2_id = getAlgoId(algo2_name);

    cout << "Algorithm: " << getAlgoName(algo1_id) << " | " << getAlgoName(algo2_id) << "\n";
    cout << "Input size: " << size << "\n";
    cout << "Input order: " << getInputOrder(input_order) << "\n";
    cout << "-------------------------\n";

    int* dataSet = new int[size];
    long long num_Comp_1, num_Comp_2;

    if (strcmp(input_order, "-rand") == 0)
        GenerateRandomData(dataSet, size);
    else if (strcmp(input_order, "-sorted") == 0)
        GenerateSortedData(dataSet, size);
    else if (strcmp(input_order, "-nsorted") == 0)
        GenerateNearlySortedData(dataSet, size);
    else if (strcmp(input_order, "-rev") == 0)
        GenerateReverseData(dataSet, size);

    //Write generated data to "input.txt"
    ofstream fout;
    fout.open("input.txt");
    if (fout.is_open())
    {
        fout << size << "\n";
        for (int i = 0; i < size; i++)
            fout << dataSet[i] << " ";

        fout.close();
    }
    else
        cout << "Cannot open 'input.txt'.\n";

    int* a = copyFromDataSet(dataSet, size);
    int* b = copyFromDataSet(dataSet, size);
        
    auto start_time = chrono::high_resolution_clock::now();
    (*SORT_ALGO[algo1_id])(a, size, num_Comp_1);
    auto end_time = chrono::high_resolution_clock::now();

    double run_time_1 = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

    start_time = chrono::high_resolution_clock::now();
    (*SORT_ALGO[algo2_id])(b, size, num_Comp_2);
    end_time = chrono::high_resolution_clock::now();

    double run_time_2 = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

    cout << "Running time: " << fixed << setprecision(5) << run_time_1 / 1000 << " ms | " << run_time_2 / 1000 << " ms\n";
    cout << "Comparisons: " << num_Comp_1 << " | " << num_Comp_2 << "\n";

    delete[] a;
    delete[] b;
    delete[] dataSet;
}

//support function for testing/executing command lines
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

int* copyFromDataSet(int* a, int size)
{
    int* newDataSet = new int[size];
    for (int i = 0; i < size; i++)
        newDataSet[i] = a[i];

    return newDataSet;
}

int getAlgoId(char* algo_name)
{
    if (strcmp(algo_name, "selection-sort") == 0)
        return 0;
    if (strcmp(algo_name, "insertion-sort") == 0)
        return 1;
    if (strcmp(algo_name, "bubble-sort") == 0)
        return 2;
    if (strcmp(algo_name, "heap-sort") == 0)
        return 3;
    if (strcmp(algo_name, "merge-sort") == 0)
        return 4;
    if (strcmp(algo_name, "quick-sort") == 0)
        return 5;
    if (strcmp(algo_name, "radix-sort") == 0)
        return 6;
    if (strcmp(algo_name, "shaker-sort") == 0)
        return 7;
    if (strcmp(algo_name, "shell-sort") == 0)
        return 8;
    if (strcmp(algo_name, "counting-sort") == 0)
        return 9;
    if (strcmp(algo_name, "flash-sort") == 0)
        return 10;
    
    return -1;
}

string getInputOrder(char* input_order)
{
    if (strcmp(input_order, "-rand") == 0)
        return "Randomized";
    
    if (strcmp(input_order, "-sorted") == 0)
        return "Sorted";

    if (strcmp(input_order, "-nsorted") == 0)
        return "Nearly sorted";
    
    if (strcmp(input_order, "-rev") == 0)
        return "Reversely sorted";

    return "invalid input order";
}

string getInputOrder(int input_order)
{
    if (input_order == 0)
        return "Randomized";
    
    if (input_order == 1)
        return "Sorted";

    if (input_order == 2)
        return "Reversely sorted";

    if (input_order == 3)
        return "Nearly sorted";

    return "invalid input order";
}

void Command_3_InputOrder(int algo_id, int size, int input_order, char* output_param)
{
    cout << "Input order: " << getInputOrder(input_order) << "\n";
    cout << "-------------------------\n";

    int* a = new int[size];
    long long num_Comp;

    GenerateData(a, size, input_order);
    
    //Write generated data to corresponding files
    char* wInputTo = new char[12];
    if (input_order == 0)                   //Input order: Randomized
        strcpy(wInputTo, "input_1.txt");
    else if (input_order == 3)              //Input order: Nearly sorted
        strcpy(wInputTo, "input_2.txt");
    else if (input_order == 1)              //Input order: Sorted
        strcpy(wInputTo, "input_3.txt");
    else if (input_order == 2)              //Input order: Reversely sorted
        strcpy(wInputTo, "input_4.txt");

    ofstream fout;
    fout.open(wInputTo);
    if (fout.is_open())
    {
        fout << size << "\n";
        for (int i = 0; i < size; i++)
            fout << a[i] << " ";

        fout.close();
    }
    else
        cout << "Cannot open '" << wInputTo << "'.\n";

    auto start_time = chrono::high_resolution_clock::now();
    (*SORT_ALGO[algo_id])(a, size, num_Comp);
    auto end_time = chrono::high_resolution_clock::now();

    if (strcmp(output_param, "-both") == 0)
    {
        double time_taken_micro = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        cout << "Running time: " << fixed << setprecision(5) << time_taken_micro / 1000 << " ms\n";
        cout << "Comparisons: " << num_Comp << "\n";
    }
    else if (strcmp(output_param, "-time") == 0)
    {
        double time_taken_micro = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
        cout << "Running time: " << fixed << setprecision(5) << time_taken_micro / 1000 << " ms\n";
    }
    else if (strcmp(output_param, "-comp") == 0)
        cout << "Comparisons: " << num_Comp << "\n";
    
    cout << "\n";
    delete[] a;
}

//the functions below are for the purpose of condition checking with command line arguments
bool isValidAlgorithmName(char* algo_name)
{
    if (strcmp(algo_name, "selection-sort") == 0)
        return true;
    if (strcmp(algo_name, "insertion-sort") == 0)
        return true;
    if (strcmp(algo_name, "bubble-sort") == 0)
        return true;
    if (strcmp(algo_name, "heap-sort") == 0)
        return true;
    if (strcmp(algo_name, "merge-sort") == 0)
        return true;
    if (strcmp(algo_name, "quick-sort") == 0)
        return true;
    if (strcmp(algo_name, "radix-sort") == 0)
        return true;
    if (strcmp(algo_name, "shaker-sort") == 0)
        return true;
    if (strcmp(algo_name, "shell-sort") == 0)
        return true;
    if (strcmp(algo_name, "counting-sort") == 0)
        return true;
    if (strcmp(algo_name, "flash-sort") == 0)
        return true;

    return false;
}

bool isMeantToBeAlgorithmName(char* algo_name)
{
    char* hasSortInString = strstr(algo_name, "-sort");

    if (hasSortInString == NULL)
        return false;
    
    return true;
}

bool isMeantToBeGivenInputFile(char* filename)
{
    return ((endingWithdotTxt(filename)) && (noIllegalCharacterInFileName(filename)));
}

bool endingWithdotTxt(char* filename)
{
    int len = strlen(filename);

    if ((filename[len - 4] == '.') && (filename[len - 3] == 't') && (filename[len - 2] == 'x') && (filename[len - 1] == 't'))
        return true;
    
    return false;
}

bool noIllegalCharacterInFileName(char* filename)
{
    int len = strlen(filename);
    //illegal character in a file name was refered from: https://learn.microsoft.com/en-us/windows/win32/fileio/naming-a-file
    for (int i = 0; i < len - 4; i++)
        if (filename[i] == '<' || filename[i] == '>' || filename[i] == ':' || int(filename[i]) == 34 /*for double quote " */ || filename[i] == '/' || int(filename[i]) == 92 /*for back slash \ */ || filename[i] == '|' || filename[i] == '?' || filename[i] == '*')
            return false;
    
    return true;
}

bool isMeantToBeInputSize(char* filename)
{
    int len = strlen(filename);

    if ((int(filename[0]) < 49) || (int(filename[0]) > 57)) //i.e the first "supposedly digit" is not in the range 1 to 9
        return false;

    for (int i = 1; i < len; i++)
    {
        if ((int(filename[i]) < 48) || (int(filename[i]) > 57)) //i.e the character is not a digit in the range of 0 to 9
            return false;
    }

    return true;
}

int getSize(char* input_size)
{
    int size = int(input_size[0]) - 48;
    int len = strlen(input_size);

    for (int i = 1; i < len; i++)
        size = size * 10 + (int(input_size[i]) - 48);

    return size;
}

bool isValidInputSize(int size)
{
    if ((size >= 1) && (size <= 1000000))
        return true;
    
    return false;
}

bool isMeantToBeOutputParam(char* output_param)
{
    if (strcmp(output_param, "-time") == 0)
        return true;
    
    if (strcmp(output_param, "-comp") == 0)
        return true;

    if (strcmp(output_param, "-both") == 0)
        return true;

    return false;
}

bool isMeantToBeInputOrder(char* input_order)
{
    if (strcmp(input_order, "-rand") == 0)
        return true;

    if (strcmp(input_order, "-sorted") == 0)
        return true;

    if (strcmp(input_order, "-nsorted") == 0)
        return true;

    if (strcmp(input_order, "-rev") == 0)
        return true;

    return false;
}
