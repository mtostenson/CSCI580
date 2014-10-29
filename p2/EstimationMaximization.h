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
	CEstimationMaximization(vector<char>*, vector<vector<double> >*, vector<vector<double> >*, vector<char>*);
	~CEstimationMaximization();
	void process();
private:
	double min(int);

	vector<char>* pObservations;
	vector<vector<double> >* pTransition;
	vector<vector<double> >* pSensory;
	vector<char>* pOriginal;

	double state[3];
};

