#pragma once
#include <string>
#include <cstring>

using namespace std;

const int DATA_SIZE[6] = {10000, 30000, 50000, 100000, 300000, 500000};

//Functions for experimenting
void Experiment();
bool TestAlgorithm(int algo_id);

//Command line functions
void Command_1(char* algo_name, char* input_filename, char* output_param);
void Command_2(char* algo_name, int size, char* input_order, char* output_param);
void Command_3(char* algo_name, int size, char* output_param);

//supporting function prototypes
string getAlgoName(int algo_id);
string getDataOrder(int DataOrder);
int* copyFromDataSet(int* a, int size);
int getAlgoId(char* algo_name);
string getInputOrder(char* input_order);
string getInputOrder(int input_order);
void Command_3_InputOrder(int algo_id, int size, int input_order, char* output_param);

//used in main.cpp for condition checking - command line arguments
bool isValidAlgorithmName(char* algo_name);
bool isMeantToBeAlgorithmName(char* algo_name);
bool isMeantToBeGivenInputFile(char* filename);
bool endingWithdotTxt(char* filename);
bool noIllegalCharacterInFileName(char* filename);
bool isMeantToBeInputSize(char* filename);
int getSize(char* input_size);
bool isValidInputSize(int size);
bool isMeantToBeOutputParam(char* output_param);
bool isMeantToBeInputOrder(char* input_order);