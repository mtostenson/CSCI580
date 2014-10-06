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
	Robot(char*, char*);

	// Reads file and populates grid vector	
	void buildGrid(char*);

	// Displays the grid for debugging
	void printGrid();

	// Observation helper to add values
	void addObservation(string);

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

private:

	// Holds robots world grid values
	vector<vector<int> > grid;

	// Sensory error of inputs
	float sensory_error;

	// All observations specified by the user at runtime
	vector<string> observations;

	// Need a more descriptive name
	float diff_values[5];

};

int main(int argc, char* argv[]) {	
	Robot robot(argv[1], argv[2]);
	for(int i = 3; i < argc; i++) {
		robot.addObservation(argv[i]);
	}
	// cout << robot.getBitsDifference(15, 0) << endl;
	// cout << robot.NSWE("NS") << endl;
	// cout << robot.intToBinary(11) << endl;    		
	// vector<float> diffs = robot.calculate_diff_values(robot.getError());
	// for(int i = 0; i < diffs.size(); i++) {
	// 	fprintf(stdout, "[%d]: %f\n", i, diffs[i]);
	// }
}

#endif