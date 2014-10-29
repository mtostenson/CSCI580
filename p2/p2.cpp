// p2.cpp : Defines the entry point for the console application.
//

#include "StdAfx.h"
#include "EstimationMaximization.h"

void readFile(string* pFilename, vector<char>* pDestination)
{
	ifstream file;
	file.open(*pFilename);
	string input;
	getline(file, input);
	for(char c : input)
	{
		pDestination->push_back(c);
	}
}

void readFile(string* pFilename, vector<double>* pDestination)
{
	ifstream file;
	file.open(*pFilename);
	string input;
	while(getline(file, input))
	{
		stringstream ss(input);
		string value;
		while(ss >> value)
		{
			pDestination->push_back(atof(value.c_str()));
		}
	}
}

template <typename T> void printVector(vector<T>* pVector)
{
	for(T t : *pVector)
	{
		cout << t << endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<char> observations;
	readFile(new string("observations_10.txt"), &observations);
	printVector(&observations);
	new CEstimationMaximization();
	return 0;
}

