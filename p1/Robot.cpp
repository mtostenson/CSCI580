#include "Robot.h"

Robot::Robot(char* fileName, char* error) {
	sensory_error = atof(error);
	buildGrid(fileName);
}

void Robot::buildGrid(char* fileName) {
	string line;
	ifstream file;
	file.open(fileName);	
	while(getline(file, line)) {
		vector<int> vec;				
		stringstream ss(line);
		string value;
		while(ss >> value) {
			vec.push_back(atoi(value.c_str()));			
		}		
		grid.push_back(vec);
	}
	file.close();
	cout << endl;
    printGrid();
    cout << endl;
	int dimen = grid.size() * grid[0].size();
	float matrix[dimen][dimen];
	for(int i = 0; i < dimen; i++) {
		int x = i / grid[0].size();
		int y = i % grid[0].size();
		int cell_value = grid[x][y];
		int neighbors = getBitsDifference(cell_value, 15);
		fprintf(stdout, "cell[%d][%d] has %d nieghbors\n", x, y, neighbors);
		string walls = intToBinary(cell_value);		
	
		// N
		if(walls[0] == '0') {
			matrix[grid[0].size() - i][i] = 1 / neighbors;
		}
		
		// S
		if(walls[1] == '0') {
			matrix[grid[0].size() + i][i] = 1 / neighbors;
		}
		
		// W
		if(walls[2] == '0') {
			matrix[i - 1][i] = 1 / neighbors;
		}

		// E
		if(walls[3] == '0') {
			matrix[i + 1][i] = 1 / neighbors;
		}

		// for(int q = 0; q < dimen; q++) {
		// 	cout << matrix[q][i] << " ";
		// }
		// cout << endl;
	}		
}

void Robot::printGrid() {
	for(int i = 0; i < grid.size(); i++) {
		for(int j = 0; j < grid[i].size(); j++) {
			fprintf(stdout,"%d ", grid[i][j]);
		}
		cout << endl;
	}
}

void Robot::addObservation(string pObservation) {
	observations.push_back(pObservation);
}

int Robot::getBitsDifference(int a, int b) {
	int x = a^b;
	unsigned int y;
	for(y = 0; x; y++) {
		x &= x - 1;
	}
	return y;
}

int Robot::NSWE(string r) {
	int result = 0;
	if(inString(r, 'N')) result += 8;
	if(inString(r, 'S')) result += 4;
	if(inString(r, 'W')) result += 2;
	if(inString(r, 'E')) result += 1;	
	return result;
}

bool Robot::inString(string s, char c) {
	for(int i = 0; i < s.size(); i++) {
		if(s[i] == c) {
			return true;
		}
	}
	return false;
}

string Robot::intToBinary(int n) {
	bitset<4> bits(n);		
	return bits.to_string();
}

vector<float> Robot::calculate_diff_values(float e) {
	vector<float> result;
	for(int i = 0; i <5; i++) {
		result.push_back(pow(e, i) * pow(1 - e, 4 - i));
	}
	return result;
}