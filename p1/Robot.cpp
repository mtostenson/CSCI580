#include "Robot.h"

Robot::Robot(char* fileName, char* error) {
    sensory_error = atof(error);
    buildGrid(fileName);
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
            vec.push_back(atoi(value.c_str()));         
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
    vector<vector<float> > matrix;

    // Defaults all matrix values to 0
    for(int i = 0; i < dimen; i++) {
        vector<float> row;
        for(int j = 0; j < dimen; j++) {
            row.push_back(0.0f);
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
            matrix[cell][cell - gridWidth] = 1.0f / neighbors;
        } else cout << "N";

        // S
        if(walls[1] == '0') {
            matrix[cell][cell + gridWidth] = 1.0f / neighbors;
        } else cout << "S";

        // W
        if(walls[2] == '0') {
            matrix[cell][cell - 1] = 1.0f / neighbors;
        } else cout << "W";

        // E
        if(walls[3] == '0') {
            matrix[cell][cell + 1] = 1.0f / neighbors;
        } else cout << "E";
        cout << endl << endl;
    }
    printMatrix(matrix);
    vector<vector<float> > matrix2 = transposeMatrix(matrix);
    printMatrix(matrix2);
}

void Robot::printGrid() {
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[i].size(); j++) {
            if(grid[i][j] < 10) cout << 0;
            fprintf(stdout,"%d ", grid[i][j]);
        }
        cout << endl;
    }
    cout << endl;
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

vector<vector<float> > Robot::transposeMatrix(vector<vector<float> > matrix1) {
    int size = matrix1.size(); 
    vector<vector<float> > matrix2;
    for(int i = 0; i < size; i++) {
        vector<float> col;
        for(int j = 0; j < size; j++) {
            col.push_back(matrix1[j][i]);
        }
        matrix2.push_back(col);
    }
    return matrix2;
}

void Robot::printMatrix(vector<vector<float> > matrix) {
    int dimen = matrix.size();
    for(int i = 0; i < dimen; i++) {
        for(int j = 0; j < dimen; j++) {
            float val = matrix[i][j];
            cout << "[" << val;
            if(val == 0.0f || val == 1.0f) cout << ".0";
            cout << "] ";
        }
        cout << endl;
    }
    cout << endl;
}