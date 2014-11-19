#include <stdio.h>
#include <vector>

#include "FileIO.h"

using namespace std;

int main(int argc, char* argv[]) 
{   
    // Validate # of params
    if(argc < 7)
    {
        printf("[!] Not enough arguments\n");
    }    
    
    // train_input
    vector<vector<double> >* train_input = FileIO::fileToVec2(argv[1]);

    // train_output
    vector<int>* train_output = FileIO::fileToVec(argv[2]);

    // test_input
    vector<vector<double> >* test_input = FileIO::fileToVec2(argv[3]);

    // test_output.txt
    vector<int>* test_output = FileIO::fileToVec(argv[4]);

    // structure.txt
    vector<int>* structure = FileIO::fileToVec(argv[5]);

    // weights.txt
    vector<vector<double> >* weights = FileIO::fileToVec2(argv[6]);

    // k
    int k = atoi(argv[7]);

    // Exit
    return 0;
}