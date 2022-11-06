#include <iostream>
#include "SortingAlgorithms.h"
#include "DataGenerator.h"
#include "Experiment.h"

using namespace std;

int main()
{
	//testing sorting algorithms
	//if you wanna test your sorting functions do it right here
	for (int algo_id = 0; algo_id < 11; algo_id++)
	{
		cout << getAlgoName(algo_id) << ": ";
		if (algo_id != 6 && TestAlgorithm(algo_id))
			cout << "PASSED\n";
		else
			cout << "FAILED\n";
	}
	return 0;
}