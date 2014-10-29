#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class CEstimationMaximization
{
public:
	CEstimationMaximization(vector<char>*, vector<vector<double> >*, vector<double>*, vector<char>*);
	~CEstimationMaximization();
private:
	vector<char>* pObservations;
	vector<vector<double> >* pTransition;
	vector<double>* pSensory;
	vector<char>* pOriginal;
};

