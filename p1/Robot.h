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
    vector<vector<double> > buildMatrix();

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
    vector<double>* initialJointPredictionMatrix(vector<vector<int> >);

    // Print matrix
    void printMatrix(vector<vector<double> >, string);

    // Prints vector for debugging
    void printVector(vector<double>, string);

    // Multiplies 2d vector with 1d vector
    vector<double>* multiply(vector<vector<double> >, vector<double>);

    // Converts 2d grid vector to 1d vector
    vector<int> inlineGrid();

    // Returns 2d vector of sensory probabilities given sensory input
    vector<vector<double> > sensoryProbabilities(int);

    // Multiplies two 2d vectors together
    vector<vector<double> > multiply2(vector<vector<double> >, vector<vector<double> >);

    // Resturns the sum of all values in a 1d vector
    double sumVector(vector<double>);

    // Normalizes the values of a 1d vector
    vector<double> normalize(vector<double>);

    // Outputs the result
    void showAnswer(vector<double>, char*);

private:

    // Holds robots world grid values
    vector<vector<int> > grid;

    // Holds the transitivity matrix of the grid
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

// Program entry point
int main(int argc, char* argv[]) {  
    Robot robot(argc, argv);
}

#endif
