#ifndef _E_M_H_
#define _E_M_H_

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
    CEstimationMaximization(
        vector<char>*,
        vector<vector<double> >*,
        vector<vector<double> >*,
        vector<char>*,
        int);
    ~CEstimationMaximization();
    void calculateSequenceOfStates();
private:
    int charToStateInt(char&);
    
    vector<char>* pObservations;
    vector<vector<double> >* pTransition;
    vector<vector<double> >* pSensory;
    vector<char>* pOriginal;
    
    int mIterations;
    vector<double>* mState[3];
    vector<int> mBacktrack[3];
};

#endif // _E_M_H_