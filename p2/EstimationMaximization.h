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
	CEstimationMaximization();
	~CEstimationMaximization();
private:
	void readFile(string*, vector<char>*);
	void readFile(string*, vector<double>*);
	void test();
	template <typename T> void printVector(vector<T>*);
};

