#include "Robot.h"

Robot::Robot(int argc, char* argv[]) 
: possible_positions(0) {
    sensory_error = atof(argv[2]);    
    diff_values = calculate_diff_values(sensory_error);
    for(int i = 3; i < argc; i++) {
        addObservation(argv[i]);
    }
    buildGrid(argv[1]);
    printVector(diff_values, "Diffs");
    buildMatrix();
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
            int iValue = atoi(value.c_str());
            if(iValue != 15){
                possible_positions++;
            }
            vec.push_back(iValue);         
        }       
        grid.push_back(vec);
    }
    file.close();
    cout << endl;
    printGrid();    
}

void Robot::buildMatrix()
{
    int gridWidth = grid[0].size();
    int gridHeight = grid.size();
    int dimen = gridWidth * gridHeight;
    vector<vector<double> > matrix;

    // Defaults all matrix values to 0
    for(int i = 0; i < dimen; i++) {
        vector<double> row;
        for(int j = 0; j < dimen; j++) {
            row.push_back(0.0);
        }
        matrix.push_back(row);
    }
    for(int cell = 0; cell < dimen; cell++) {
        int row = cell / gridWidth; // Matrix cell (col 0) row in grid
        int col = cell % gridWidth; // Matrix cell (col 0) col in grid
        int cell_value = grid[row][col];
        int neighbors = getBitsDifference(cell_value, 15);
        // fprintf(stdout, "cell[%d][%d] has %d neighbors\n", row, col, neighbors);
        string walls = intToBinary(cell_value);
        cout << walls << " - " << neighbors << " neighbors - walls ";
    
        // N
        if(walls[0] == '0') {
            matrix[cell][cell - gridWidth] = 1.0 / neighbors;
        } else cout << "N";

        // S
        if(walls[1] == '0') {
            matrix[cell][cell + gridWidth] = 1.0 / neighbors;
        } else cout << "S";

        // W
        if(walls[2] == '0') {
            matrix[cell][cell - 1] = 1.0 / neighbors;
        } else cout << "W";

        // E
        if(walls[3] == '0') {
            matrix[cell][cell + 1] = 1.0 / neighbors;
        } else cout << "E";
        cout << endl;
    }
    cout << endl;
    printMatrix(matrix, "Transitivity Matrix");
    vector<vector<double> > matrix2 = transposeMatrix(matrix);
    printMatrix(matrix2, "Translated Transitivity Matrix");
    transitivity_matrix = matrix2;
    vector<double> j0 = initialJointPredictionMatrix(grid);
    printVector(j0, "JO");    
    vector<double> j1 = multiply(transitivity_matrix, j0);
    printVector(j1, "J1");
    vector<vector<double> > sp0 = sensoryProbabilities(NSWE(observations[0]));
    printMatrix(sp0, "Sensory Probabilities for Observation 0");
    vector<vector<double> > Z = multiply2(matrix2, sp0);
    printMatrix(Z, "Matrix Z");
    vector<double> j2 = multiply(Z, j1);
    printVector(j2, "J2");
    vector<vector<double> > sp1 = sensoryProbabilities(NSWE(observations[1]));
    printMatrix(sp1, "Sensory Probabilities for Observation 1");
    vector<double> Z2 = multiply(sp1, j2);
    printVector(Z2, "Matrix Z");
    answer = sumVector(Z2);
    cout << "\nSum: " << answer << endl;
    vector<double> normal = normalize(Z2);
    printVector(normal, "Result");
    showAnswer(normal);
}

void Robot::printGrid() {
    fprintf(stdout, "Grid:\n");
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[i].size(); j++) {
            if(grid[i][j] < 10) cout << 0;
            fprintf(stdout,"%d ", grid[i][j]);
        }
        cout << endl;
    }
    cout << endl;
    cout << "Possible positions: " << possible_positions << endl;
    cout << "\nObservations:\n";
    for(int i = 0; i < observations.size(); i++) {
        cout << observations[i] << " ";
    }
    cout << endl << endl;
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

vector<double> Robot::calculate_diff_values(double e) {
    vector<double> result;
    for(int i = 0; i <5; i++) {
        result.push_back(pow(e, i) * pow(1 - e, 4 - i));
    }
    return result;
}

vector<vector<double> > Robot::transposeMatrix(vector<vector<double> > matrix1) {
    int size = matrix1.size(); 
    vector<vector<double> > matrix2;
    for(int i = 0; i < size; i++) {
        vector<double> col;
        for(int j = 0; j < size; j++) {
            col.push_back(matrix1[j][i]);
        }
        matrix2.push_back(col);
    }
    return matrix2;
}

vector<double> Robot::initialJointPredictionMatrix(vector<vector<int> > grid) {    
    vector<double> result;
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[0].size(); j++) {
            vector<double> single;
            if(grid[i][j] != 15) {
                result.push_back(1.0 / possible_positions);
            } else {
                result.push_back(0.0);
            }
        }        
    }
    return result;    
}

void Robot::printMatrix(vector<vector<double> > matrix, string title) {
    cout << title << ":\n";
    int dimen = matrix.size();
    for(int i = 0; i < dimen; i++) {
        for(int j = 0; j < dimen; j++) {
            double val = matrix[i][j];
            cout << "[" << val;
            if(val == 0.0 || val == 1.0) cout << ".0";
            cout << "] ";
        }
        cout << endl;
    }
    cout << endl;
}

void Robot::printVector(vector<double> matrix, string title) {
    fprintf(stdout, "%s:\n", title.c_str());
    for(int i =0; i < matrix.size(); i++) {
        fprintf(stdout, "[%f]\n", matrix[i]);
    }
    cout << endl;
}

vector<double> Robot::multiply(vector<vector<double> > T, vector<double> J) {
    vector<double> result;
    for(int i = 0; i < T.size(); i++) {
        double sum = 0;
        for(int j = 0; j < T[i].size(); j++) {            
            sum += (T[i][j]*J[j]);
        }
        result.push_back(sum);
    }
    return result;
}

vector<int> Robot::inlineGrid() {
    vector<int> result;
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[i].size(); j++) {
            result.push_back(grid[i][j]);
        }
    }
    return result;
}

vector<vector<double> > Robot::sensoryProbabilities(int observation) {
    vector<int> g = inlineGrid();
    vector<vector<double> > result;
    for(int i = 0; i < g.size(); i++) {
        vector<double> row;
        for(int j = 0; j < i; j++) {
            row.push_back(0.0);
        }
        row.push_back(diff_values[getBitsDifference(g[i], observation)]);    
        for(int j = 0; j < g.size() - i; j++) {
            row.push_back(0.0);
        }
        result.push_back(row);
    }
    return result;
}

vector<vector<double> > Robot::multiply2(vector<vector<double> > T, vector<vector<double> > O) {
    vector<vector<double> > result = T;    
    for(int i = 0; i < O.size(); i++) {
        for(int j = 0; j < T[i].size(); j++) {
            result[i][j] = T[i][j] * O[j][j];
        }
    }
    return result;
}

double Robot::sumVector(vector<double> input) {
    double sum = 0.0;
    for(int i = 0; i < input.size(); i++) {
        sum += input[i];
    }
    return sum;
}

vector<double> Robot::normalize(vector<double> input) {
    vector<double> result;
    double sum = sumVector(input);
    for(int i = 0; i < input.size(); i++) {
        result.push_back(input[i]/sum);
    }
    return result;
}

void Robot::showAnswer(vector<double> normalized) {
    double largest = 0.0;
    int largest_index;
    for(int i = 0; i < normalized.size(); i++) {
        if(normalized[i] > largest) {
            largest = normalized[i];
            largest_index = i;
        }
    }
    int gridWidth = grid[0].size();
    cout << "(" << largest_index / gridWidth << ", " << largest_index % gridWidth<< ") " << largest << endl;
}