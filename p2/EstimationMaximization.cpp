#include "StdAfx.h"
#include "EstimationMaximization.h"


CEstimationMaximization::CEstimationMaximization()
{	
	vector<double> vec;
	vector<char> vec2;
	readFile(new string("transition_10.txt"), &vec);
	readFile(new string("original_10.txt"), &vec2);
	printVector(&vec);
	printVector(&vec2);
}


CEstimationMaximization::~CEstimationMaximization()
{
}
	
void CEstimationMaximization::readFile(string* pFilename, vector<char>* pDestination)
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

void CEstimationMaximization::readFile(string* pFilename, vector<double>* pDestination)
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

template <typename T> void CEstimationMaximization::printVector(vector<T>* pVector)
{
	for(T t : *pVector)
	{
		cout << t << endl;
	}
}