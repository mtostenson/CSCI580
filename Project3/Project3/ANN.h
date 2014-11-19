#pragma once

#include <vector>
#include <stdio.h>
#include <math.h>

using namespace std;

#define ALPHA = 0.1

class ANN
{
public:    

    void run();

    // Setters
    void setTrainInput(vector<vector<double> >* pVec) { train_input = pVec; }
    void setTrainOutput(vector<int>* pVec) { train_output = pVec; }
    void setTestInput(vector<vector<double> >* pVec) { test_input = pVec; }
    void setTestOutput(vector<int>* pVec) { test_output = pVec; }
    void setStructure(vector<int>* pVec) { structure = pVec; }
    void setWeights(vector<vector<double> >* pVec) { weights = pVec; }
    void setK(int pK) { k = pK; }
    void setOutputEncoding(vector<vector<double> > pVec) { output_encoding = pVec; }

private:    

    void prepareNN();

    // Set up input layer
    void setInputLayer(int, vector<vector<double> >*);

    // Activation function
    double activation(int&, int&);

    // Data structures
    vector<vector<double> >* train_input;
    vector<int>*             train_output;
    vector<vector<double> >* test_input;
    vector<int>*             test_output;
    vector<int>*             structure;
    vector<vector<double> >* weights;
    int                      k;
    vector<vector<double> >  output_encoding;

    // Holder of array values
    vector<vector<double> > neural_network;

    // Error vector
    vector<vector<double> > error;
};

