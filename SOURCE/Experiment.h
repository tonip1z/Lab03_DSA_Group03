#pragma once
#include <string>

using namespace std;

const int DATA_SIZE[6] = {10000, 30000, 50000, 100000, 300000, 500000};

void Experiment();
bool TestAlgorithm(int algo_id);

//supporting function prototypes
string getAlgoName(int algo_id);
string getDataOrder(int DataOrder);
int* copyFromDataSet(int* a, int size);