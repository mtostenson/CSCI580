#ifndef _E_M_H_
#define _E_M_H_

#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#define K 1

using namespace std;

class CEstimationMaximization
{
public:
    CEstimationMaximization(
        vector<char>*,
        vector<vector<double> >*,
        vector<vector<double> >*,
        vector<char>*,
        int);
    ~CEstimationMaximization();
    void calculateViterbi();
    void getMostProbablePath();
private:

    int charToStateInt(char&);
    char stateIntToChar(int&);

    vector<char>* pObservations;
    vector<vector<double> >* pTransition;
    vector<vector<double> >* pSensory;
    vector<char>* pOriginal;
    
    int mIterations;
    vector<int>* minpath;
    vector<double>* mViterbi[3];
    vector<int>* pBacktracking[3];
    vector<int>* minPath();
    
    vector<char>* path;
};

#endif // _E_M_H_