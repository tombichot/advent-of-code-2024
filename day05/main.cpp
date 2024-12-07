#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool findRule(int X, int Y, const vector<vector<int>>& rules){
    for (const auto& rule : rules) {
        if (rule.size() == 2 && rule[0] == X && rule[1] == Y) {
            return true;
        }
    }
    return false; 
}

vector<vector<int>> findCorrectUpdates(const vector<vector<int>>& rules, const vector<vector<int>>& updates){
    vector<vector<int>> correctUpdates;

    for(int i = 0; i < updates.size(); i++){
        bool isCorrect = true;
        for(int j = 0; j < updates[i].size() - 1; j++){
            if(!findRule(updates[i][j], updates[i][j+1], rules)){
                isCorrect = false;
                break;
            }
        }
        if(isCorrect) correctUpdates.push_back(updates[i]);
    }
    return correctUpdates;
}

vector<vector<int>> findIncorrectUpdates(const vector<vector<int>>& rules, const vector<vector<int>> updates){
    vector<vector<int>> incorrectUpdates;

    for(int i = 0; i < updates.size(); i++){
        bool isCorrect = true;
        for(int j = 0; j < updates[i].size() - 1; j++){
            if(!findRule(updates[i][j], updates[i][j+1], rules)){
                isCorrect = false;
            }
        }
        if(!isCorrect) incorrectUpdates.push_back(updates[i]);
    }
    return incorrectUpdates;
}

void reorderUpdates(const vector<vector<int>>& rules, vector<vector<int>>& updates){
    for(int i = 0; i < updates.size(); i++){
        //Tri à bulle
        bool swapped;
        do{
            swapped = false;
            for(int j = 0; j < updates[i].size() - 1; j++){
                if(!findRule(updates[i][j], updates[i][j+1], rules)){
                    swap(updates[i][j], updates[i][j+1]);
                    swapped = true;
                }
            }
        } while(swapped); 
    }
}

int addMiddlePageNumberUpdates(const vector<vector<int>>& updates){
    int count = 0;

    for(int i = 0; i < updates.size(); i++){
        size_t size = updates[i].size();
        count += updates[i][size/2];
    }

    return count;
}

int main() {
    cout << "Advent of Code 2024" << endl;
    cout << "Day 5: Print Queue" << endl;
    cout << endl;

    fstream newfile;

    string fileName = "example.txt";

    newfile.open("./" + fileName, ios::in);

    if (!newfile.is_open()) {
        cerr << "Error: unable to open file " << fileName << endl;
        return 1;
    }

    //Init variables
    string line;

    vector<vector<int>> rules;
    vector<vector<int>> updates;

    int puzzleAnswer1 = 0;
    int puzzleAnswer2 = 0;

    char separator = '|';

    //Get data
    while (getline(newfile, line)) {
        if (line.empty()) {
            separator = ',';
            continue; 
        }

        stringstream ss(line);
        string token;
        vector<int> data;
        while (getline(ss, token, separator)) {
            data.push_back(std::stoi(token));
        }

        if(separator == '|'){
            rules.push_back(data);
        }else{
            updates.push_back(data);
        }
    }

    newfile.close();

    //Processing
    vector<vector<int>> correctUpdates = findCorrectUpdates(rules, updates);
    puzzleAnswer1 = addMiddlePageNumberUpdates(correctUpdates);

    vector<vector<int>> incorrectUpdates = findIncorrectUpdates(rules, updates);
    reorderUpdates(rules, incorrectUpdates);
    puzzleAnswer2 = addMiddlePageNumberUpdates(incorrectUpdates);

    //Show answers
    cout << "Puzzle answer 1 : " << puzzleAnswer1 << endl;
    cout << "Puzzle answer 2 : " << puzzleAnswer2 << endl;

    return 0;
}
