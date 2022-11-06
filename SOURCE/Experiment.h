#pragma once
#include <string>

using namespace std;

const int DATA_SIZE[6] = {100, 300, 500, 1000, 3000, 5000};

void Experiment();
bool TestAlgorithm(int algo_id);

//supporting function prototypes
string getAlgoName(int algo_id);
string getDataOrder(int DataOrder);
int* copyFromDataSet(int* a, int size);