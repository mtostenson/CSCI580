#include <stdio.h>
#include <vector>

#include "FileIO.h"
#include "ANN.h"

using namespace std;

int main(int argc, char* argv[]) 
{   
    // Validate # of params
    if(argc < 7)
    {
        printf("[!] Not enough arguments\n");
    }    
    
    ANN ann;

    // train_input
    ann.setTrainInput(FileIO::fileToVec2(argv[1]));

    // train_output
    ann.setTrainOutput(FileIO::fileToVec(argv[2]));

    // test_input
    ann.setTestInput(FileIO::fileToVec2(argv[3]));

    // test_output.txt
    ann.setTestOutput(FileIO::fileToVec(argv[4]));

    // structure.txt
    ann.setStructure(FileIO::fileToVec(argv[5]));

    // weights.txt
    ann.setWeights(FileIO::fileToVec2(argv[6]));

    // k
    ann.setK(atoi(argv[7]));    

    // Set output encoding
    vector<vector<double> > encoding = 
    { 
        { 0.1, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9 },
        { 0.9, 0.1, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9 },
        { 0.9, 0.9, 0.1, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9 },
        { 0.9, 0.9, 0.9, 0.1, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9 },
        { 0.9, 0.9, 0.9, 0.9, 0.1, 0.9, 0.9, 0.9, 0.9, 0.9 },
        { 0.9, 0.9, 0.9, 0.9, 0.9, 0.1, 0.9, 0.9, 0.9, 0.9 },
        { 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.1, 0.9, 0.9, 0.9 },
        { 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.1, 0.9, 0.9 },
        { 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.1, 0.9 },
        { 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.1 }
    };
    ann.setOutputEncoding(encoding);

    // Set first layer
    ann.run();

    // Exit
    return 0;

}