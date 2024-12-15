#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

void calculateEquation(const vector<long>& equation, int index, long result, vector<long>& results, int numberOfOperator) {
    if (index == equation.size()) {
        results.push_back(result);
        return;
    }

    //Part 1
    calculateEquation(equation, index + 1, result + equation[index], results, numberOfOperator);
    calculateEquation(equation, index + 1, result * equation[index], results, numberOfOperator);

    //Part 2
    if(numberOfOperator == 3){
        int digits = static_cast<int>(log10(equation[index])) + 1;
        result = result * static_cast<long>(pow(10, digits)); 
        calculateEquation(equation, index + 1, result + equation[index], results, numberOfOperator);
    } 
}

long calibrateEquations(vector<vector<long>> equations, int numberOfOperator) {
    long totalCalibrationResult = 0;

    for(int i = 0; i < equations.size(); i++){
        if(equations[i].size() < 3) continue;

        vector<long> results;
        calculateEquation(equations[i], 2, equations[i][1], results, numberOfOperator);
    
        if (find(results.begin(), results.end(), equations[i][0]) != results.end()) {
            totalCalibrationResult += equations[i][0];
        } 
    }

    return totalCalibrationResult;
}

int main() {
    cout << "Advent of Code 2024" << endl;
    cout << "Day 7: Bridge Repair" << endl;
    cout << endl;

    fstream newfile;

    string fileName = "example.txt";

    newfile.open("./" + fileName, ios::in);

    if (!newfile.is_open()) {
        cerr << "Error: unable to open file " << fileName << endl;
        return 1;
    }

    // Init variables
    string line;
    long puzzleAnswer1 = 0, puzzleAnswer2 = 0;

    vector<vector<long>> equations;

    while (getline(newfile, line)) {
        vector<long> equation;
        stringstream ss(line);
        string token;
        while (getline(ss, token, ' ')) {
            equation.push_back(std::stoll(token));
        }
        equations.push_back(equation);
    }
    newfile.close();

    // Processing
    puzzleAnswer1 = calibrateEquations(equations, 2);
    puzzleAnswer2 = calibrateEquations(equations, 3);

    //Show answers
    cout << "Puzzle answer 1 : " << puzzleAnswer1 << endl;
    cout << "Puzzle answer 2 : " << puzzleAnswer2 << endl;

    return 0;
}
