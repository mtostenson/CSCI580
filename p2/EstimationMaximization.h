/* ---------------------------------------------------------------------------
** EstimationMaximization.h
** Implementation class for CSCI580 Project 2.
**
** Author: Michael Tostenson
** -------------------------------------------------------------------------*/
#ifndef _E_M_H_
#define _E_M_H_

#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

#define K 1 // Laplacian smoothing value

class CEstimationMaximization
{
public:
    // Constructor, takes all initial input values
    CEstimationMaximization(
        vector<char>*,
        vector<vector<double> >*,
        vector<vector<double> >*,
        vector<char>*);
    ~CEstimationMaximization();

    // Calculates viterbi table
    void calculateViterbi();

    // Gets most probable path from backtracking table
    void getMostProbablePath();

    // Calculates curent transition and sensory data
    void calculateTransAndSens();

    // Outputs final results to stdout and file 'output.txt'
    void showResult();

private:
    // Converts char [B][L][M] to int [0][1][2] respectively
    int charToStateInt(char&);

    // Converts int [0][1][2] to char [B][L][M] respectively
    char stateIntToChar(int&);

    // Converts char [H][T] to int [0][1] respectively
    int sensoryToInt(char&);

    // Calculates total transitions between two states
    int getNumTrans(int&, int&);

    // Returns total instances of a state in the most probable path
    int numValInPath(int&);

    // Returns total matches between a given state and sensory value
    int sensoryMatches(int&, int&);

    // Returns total occurences of a state in the observation values
    int numValInObs(int&);
    
    vector<char>* pObservations;            // Stores observation values
    vector<vector<double> >* pTransition;   // Stores transition values
    vector<vector<double> >* pSensory;      // Stores sensory values
    vector<char>* pOriginal;                // Stores original values
    vector<char>* path;                     // Stores the current most probable path    
    vector<double>* mViterbi[3];            // Stores the current Viterbi table values
    vector<int>* pBacktracking[3];          // Stores the current backtracking values   
};

#endif // _E_M_H_