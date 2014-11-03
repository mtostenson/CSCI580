// hw7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define ALPHA 0.01f

// Helper methods
double dotProduct(vector<int>& a, vector<double>& b)
{
    double result = 0;
    for(int i = 0; i < a.size(); i++)
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
    for(int i = 0; i < input.size(); i++)
    {
        input[i].insert(input[i].begin(), 1);
    }

    // Set initial weights
    vector<vector<double> > w(input.size());
    for(int i = 0; i < input.size(); i++)
    {
        for(int j = 0; j < 4; j++)
        {
            w[i].push_back(1);
        }
    }

    // Loop 10 times    
    vector<double> h(input.size());
    for (int i = 0; i < 10; i++)
    {
        for(int j = 0; j < input.size(); j++)
        {
            h[j] = 1 / (1 + exp(-dotProduct(input[j], w[j])));

            for(int k = 0; k < input[0].size(); k++)
            {
                w[j][k] = w[j][k] + ALPHA * (input[j].back() - h[j]) * h[j] * (1 - h[j]) * input[j][k];
            }
        }       
        
    }

    // Print output

	return 0;
}
