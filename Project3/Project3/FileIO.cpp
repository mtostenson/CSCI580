#include "FileIO.h"

vector<vector<double>* >* FileIO::fileToVec2(char* pFilename)
{
    vector<vector<double>* >* result = new vector<vector<double >* >();
    ifstream file;
    file.open(pFilename);
    string input;
    while(getline(file, input))
    {
        vector<double> row;
        stringstream ss(input);
        string value;
        while(ss >> value)
        {
            row.push_back(atof(value.c_str()));
        }
        result->push_back(&row);
    }
    file.close();
    return result;
}

vector<int>* FileIO::fileToVec(char* pFilename)
{
    vector<int>* result = new vector<int>();
    ifstream file;
    file.open(pFilename);
    string value;
    while(getline(file, value))
    {
        result->push_back(atoi(value.c_str()));        
    }
    file.close();
    return result;
}