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

    // Access method for error float value
    float getError() { return sensory_error; }

    // Calculates number of differing binary bits between ints
    int getBitsDifference(int, int);

    // Converts observation string to integer value
    int NSWE(string);

    // Helper that finds characters in strings
    bool inString(string, char);

    // Converts int to binary string
    string intToBinary(int);

    // Calculate difference values
    vector<float> calculate_diff_values(float);

    // Transpose matrix
    vector<vector<float> > transposeMatrix(vector<vector<float> >);

    // Joint prediction matrix
    vector<float> initialJointPredictionMatrix(vector<vector<int> >);

    // Print matrix
    void printMatrix(vector<vector<float> >, string);

    void printVector(vector<float>, string);

    vector<float> multiply(vector<vector<float> >, vector<float>);

    vector<int> inlineGrid();

    vector<vector<float> > sensoryProbabilities(int);

    vector<vector<float> > multiply2(vector<vector<float> >, vector<vector<float> >);

private:

    // Holds robots world grid values
    vector<vector<int> > grid;

    vector<vector<float> > transitivity_matrix;

    // Sensory error of inputs
    float sensory_error;

    // All observations specified by the user at runtime
    vector<string> observations;

    // Need a more descriptive name
    vector<float> diff_values;

    // Possible cell locations for the robot
    int possible_positions;
};

int main(int argc, char* argv[]) {  
    Robot robot(argc, argv);
    // cout << robot.getBitsDifference(15, 0) << endl;
    // cout << robot.NSWE("NS") << endl;
    // cout << robot.intToBinary(11) << endl;           
    // vector<float> diffs = robot.calculate_diff_values(robot.getError());
    // for(int i = 0; i < diffs.size(); i++) {
    //  fprintf(stdout, "[%d]: %f\n", i, diffs[i]);
    // }
}

#endif