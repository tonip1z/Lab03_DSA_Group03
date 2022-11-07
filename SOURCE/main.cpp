#include <iostream>
#include <cstring>
#include "SortingAlgorithms.h"
#include "DataGenerator.h"
#include "Experiment.h"

using namespace std;

//Command line argument implementation was refered from: https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/
int main(int argc, char** argv)
{
	//for a better visualization of how we implemented this code (it's really a mess!), please visit: Command line implementation routing tree in "report.pdf"
	if (strcmp(argv[1], "-a") == 0)
	{
		cout << "ALGORITHM MODE\n";

		if (isMeantToBeAlgorithmName(argv[2]))
		{
			if (isValidAlgorithmName(argv[2]))
			{
				if (isMeantToBeGivenInputFile(argv[3]))
				{
					if (argc == 5) //if there is still 1 more argument passed in, check if this is [Output parameter(s)]
					{
						if (isMeantToBeOutputParam(argv[4]))
						{
							//All conditions met. Execute command 1 with ouput parameter
							Command_1(argv[2], argv[3], argv[4]);
						}
						else
						{
							cout << "Unregconized or was wrongly formatted 4th argument. Please enter [Output parameter(s)] or leave blank (for command 1).\n";
							return 1;
						}
					}
					else
					{
						//Execute command 1 without output parameter
						char* dummy = new char[4];
						strcpy(dummy, "-no");

						Command_1(argv[2], argv[3], dummy);

						delete dummy;
					}
				}
				else if (isMeantToBeInputSize(argv[3]))
				{
					int size = getSize(argv[3]);
					if (isValidInputSize(size))
					{
						if (argc == 4) //i.e no more argument was passed in, this means that we have to run command 3 with no output parameter
						{
							//Execute command 3 without output parameter
							char* dummy = new char[4];
							strcpy(dummy, "-no");

							Command_3(argv[2], size, dummy);

							delete dummy;
						}
						else if (argc > 4)
						{
							if (isMeantToBeInputOrder(argv[4]))
							{
								if (argc == 6) //if there is still 1 more argument passed in, check if this is [Output parameter(s)]
								{
									if (isMeantToBeOutputParam(argv[5]))
									{
										//All conditions met. Execute command 2 with output parameter
										Command_2(argv[2], size, argv[4], argv[5]);
									}
									else
									{
										cout << "Unregconized or was wrongly formatted 5th argument. Please enter [Output parameter(s)] or leave blank (for command 2).\n";
										return 1;
									}
								}
								else 
								{
									//Execute command 2 without output parameter
									char* dummy = new char[4];
									strcpy(dummy, "-no");

									Command_2(argv[2], size, argv[4], dummy);

									delete dummy;
								}
							}
							else if (isMeantToBeOutputParam(argv[4])) //i.e run command 3 with output parameter
							{
								//Execute command 3 with output parameter
								Command_3(argv[2], size, argv[4]);
							}
							else
							{
								cout << "Unregconized or was wrongly formatted 4th argument. Please enter either [Input order] (for command 2) or [Output parameter(s)/leave blank] (for command 3).\n";
								return 1;
							}
						}
					}
					else
					{
						cout << "Invalid input size. Please enter a integer ranging from 1 to 1,000,000.\n";
						return 1;
					}
				}
				else
				{
					cout << "Unregconized or was wrongly formatted 3rd argument. Please enter either [Given input] (for command 1) or [Input size] (for command 2).\n";
					return 1;
				}
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

		if (isMeantToBeAlgorithmName(argv[2]))
		{
			if (isValidAlgorithmName(argv[2]))
			{
				if (isMeantToBeAlgorithmName(argv[3]))
				{
					if (isValidAlgorithmName(argv[3]))
					{
						if (isMeantToBeGivenInputFile(argv[4]))
						{
							//Execute command 4
							Command_4(argv[2], argv[3], argv[4]);
						}
						else if (isMeantToBeInputSize(argv[4]))
						{
							int size = getSize(argv[4]);
							if (isValidInputSize(size))
							{
								if ((argc == 6) && (isMeantToBeInputOrder(argv[5])))
								{
									//Execute command 5
									Command_5(argv[2], argv[3], size, argv[5]);
								}
								else
								{
									cout << "[Input order] (for command 5) parameter missing or was entered with the wrong format.\n";	
									return 1;
								}
							}
							else
							{
								cout << "Invalid input size. Please enter a integer ranging from 1 to 1,000,000.\n";
								return 1;
							}
						}
						else
						{
							cout << "Unregconized or was wrongly formatted 4th argument. Please enter [Given input] (for command 4) or [Input size] (for command 5).\n";
							return 1;
						}
					}
					else
					{
						cout << "Invalid algorithm 2 name.\n";
						return 1;
					}
				}
				else
				{
					cout << "[Algorithm 2] parameter missing or was entered with the wrong format.\n";
					return 1;
				}
			}
			else
			{
				cout << "Invalid algorithm 1 name.\n";
				return 1;
			}
		}
		else
		{
			cout << "[Algorithm 1] parameter missing or was entered with the wrong format.\n";
			return 1;
		}
	}
	else if (strcmp(argv[1], "-t") == 0)
	{
		cout << "TESTING MODE\n\n";
		for (int algo_id = 0; algo_id < 11; algo_id++)
		{
			cout << getAlgoName(algo_id) << ": ";
			if (TestAlgorithm(algo_id))
				cout << "PASSED\n";
			else
				cout << "FAILED\n";
		}
	}
	else if (strcmp(argv[1], "-e") == 0)
	{
		cout << "EXPERIMENT MODE\n\n";
		Experiment();
	}
	else
	{
		cout << "Invalid mode selection.\n";
		return 1;
	}
		
	return 0;
}