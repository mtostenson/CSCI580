#pragma once
#include <string>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <fstream>
using namespace std;

class FileIO
{
public:    

    // Returns a 2d double vector ptr from input file
    static vector<vector<double>* >* fileToVec2(char*);

    // Returns a 1d double vector ptr from input file
    static vector<int>* fileToVec(char *);
};


