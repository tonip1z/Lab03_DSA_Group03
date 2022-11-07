#include <iostream>
#include <cstring>
#include "SortingAlgorithms.h"
#include "DataGenerator.h"
#include "Experiment.h"

using namespace std;

int main(int argc, char** argv)
{
	if (strcmp(argv[1], "-a") == 0)
	{
		cout << "ALGORITHM MODE\n";

		if (isMeantToBeAlgorithmName(argv[2]))
		{
			if (isValidAlgorithmName(argv[2]))
			{
				//cout << "Valid algorithm name.\n";
				
			}
			else
			{
				cout << "Invalid algorithm name.\n";
				return 1;
			}
		}
		else
		{
			cout << "[Algorithm] parameter missing or was entered with the wrong format.\n";
			return 1;
		}
	}
	else if (strcmp(argv[1], "-c") == 0)
	{
		cout << "COMPARE MODE\n";

		
	}
	else 
	{
		cout << "Invalid mode selection.\n";
		return 1;
	}
		
	return 0;
}