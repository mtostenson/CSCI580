// hw7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define ALPHA 0.01f

using namespace std;

// Helper methods
double dotProduct(vector<int>& a, vector<double>& b)
{
    double result = 0;
    for(int i = 0; i < a.size()-1; i++)
    {
        result += a[i]* b[i];
    }
    return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
    vector<vector<int> > input;
    vector<int> class_labels;
    ifstream file;
    string line;
    stringstream ss;

    // Read file 1
    file.open(argv[1]);
    while(getline(file, line))
    {
        ss << line;
        vector<int> row;
        string value;
        while(ss >> value)
        {
            row.push_back(atoi(value.c_str()));
        }
        input.push_back(row);
        ss.clear();
    }
    file.close();

    // Read file 2
    file.open(argv[2]);
    while(getline(file, line))
    {
        class_labels.push_back(atoi(line.c_str()));
    }
    ss.clear();
    file.close();

    // Add dummy attribute
    for(int x = 0; x < input.size(); x++)
    {
        input[x].insert(input[x].begin(), 1);
    }

    // Set initial weights
    vector<double> w({1,1,1,1});

    for(int count = 0; count < 10; count++)
    {
        for(int i = 0; i < input.size(); i++)
        {
            double hx = 1.0 / (1 + exp(-1*dotProduct(input[i], w)));

            for(int j = 0; j < 4; j++)
            {
                w[j] = w[j] + 0.1 * (input[i].back() - hx) * hx * (1 - hx) * input[i][j];
            }
        }
    }

    // Print output

	return 0;
}
