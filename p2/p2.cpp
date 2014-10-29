// p2.cpp : Defines the entry point for the console application.
//

#include "StdAfx.h"
#include "EstimationMaximization.h"

double logspace(double value)
{
    return log2(value)*(-1);
}

// Read a file of characters from a single line to a vector
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

// Read a file of double values to a vector
void readSensoryFile(string* pFilename, vector<vector<double> >* pDestination)
{
    ifstream file;
    file.open(*pFilename);
    string value;
    while(getline(file, value))
    {
        vector<double> row;
        row.push_back(logspace(atof(value.c_str())));
        row.push_back(logspace(1.0 - atof(value.c_str())));
        pDestination->push_back(row);
    }
}

// Read a file of double values to a 2D vector
void readFile(string* pFilename, vector<vector<double> >* pDestination)
{
    ifstream file;
    file.open(*pFilename);
    string input;
    while(getline(file, input))
    {
        vector<double> row;
        stringstream ss(input);
        string value;
        while(ss >> value)
        {
            row.push_back(logspace(atof(value.c_str())));
        }
        pDestination->push_back(row);
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    // Declare vectors to hold input values
    vector<char> observations;
    vector<vector<double> > transition;
    vector<vector<double> > sensory;
    vector<char> original;

    // Collect input from files and store in vectors
    readFile(new string(argv[1]), &observations);
    readFile(new string(argv[2]), &transition);
    readSensoryFile(new string(argv[3]), &sensory);
    readFile(new string(argv[4]), &original);

    // Begin
    CEstimationMaximization EM(&observations, &transition, &sensory, &original, atoi(argv[5]));
    EM.process();

    system("PAUSE");
    return 0;
}

