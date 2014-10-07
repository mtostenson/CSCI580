#ifndef _ROBOT_H_
#define _ROBOT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <bitset>
#include <math.h>

using namespace std;

class Robot {
public:

    // Robot constructor 
    Robot(int, char*[]);

    // Reads file and populates grid vector 
    void buildGrid(char*);

    // Displays the grid for debugging
    void printGrid();

    // Build matrix from grid
    void buildMatrix();

    // Observation helper to add values
    void addObservation(string);

    // Access method for error double value
    double getError() { return sensory_error; }

    // Calculates number of differing binary bits between ints
    int getBitsDifference(int, int);

    // Converts observation string to integer value
    int NSWE(string);

    // Helper that finds characters in strings
    bool inString(string, char);

    // Converts int to binary string
    string intToBinary(int);

    // Calculate difference values
    vector<double> calculate_diff_values(double);

    // Transpose matrix
    vector<vector<double> > transposeMatrix(vector<vector<double> >);

    // Joint prediction matrix
    vector<double> initialJointPredictionMatrix(vector<vector<int> >);

    // Print matrix
    void printMatrix(vector<vector<double> >, string);

    void printVector(vector<double>, string);

    vector<double> multiply(vector<vector<double> >, vector<double>);

    vector<int> inlineGrid();

    vector<vector<double> > sensoryProbabilities(int);

    vector<vector<double> > multiply2(vector<vector<double> >, vector<vector<double> >);

    double sumVector(vector<double>);

    vector<double> normalize(vector<double>);

    void showAnswer(vector<double>);

private:

    // Holds robots world grid values
    vector<vector<int> > grid;

    vector<vector<double> > transitivity_matrix;

    // Sensory error of inputs
    double sensory_error;

    // All observations specified by the user at runtime
    vector<string> observations;

    // Need a more descriptive name
    vector<double> diff_values;

    // Possible cell locations for the robot
    int possible_positions;

    // Probability of answer
    double answer;
};

int main(int argc, char* argv[]) {  
    Robot robot(argc, argv);
}

#endif