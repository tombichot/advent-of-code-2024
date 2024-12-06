#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

bool findNextLetter(const string& word, const vector<string>& lines, int index, const vector<int>& position, const vector<int>& direction) {
    int i = position[0] + direction[0];
    int j = position[1] + direction[1];
    
    if((0 <= i < lines.size()) && (0 <= j < lines[i].length())){  
        if(lines[i][j] == word[index]){
            index++;
            if(index == word.length()){
                return true;
            }else{
                vector<int> newPosition = {i, j};
                return findNextLetter(word, lines, index, newPosition, direction);
            }
        }
        else return false;
    }
    else return false;    
}

int findXMAS(const vector<string>& lines){
    string word = "XMAS";
    int countWord = 0;

    for(int i = 0; i < lines.size(); i++){
        for(int j = 0; j < lines[i].length(); j++){
            if(lines[i][j] == word[0]){
                //Search in all directions around the letter
                for(int m = -1; m < 2; m++){
                    for(int n = -1; n < 2; n++){
                        if(m == 0 and n == 0) continue;
                        vector<int> position = {i, j};
                        vector<int> direction = {m, n};
                        if(findNextLetter(word, lines, 1, position, direction)) countWord++;
                    }
                }
            }
        }
    }

    return countWord;
}

int findShapeOfXMAS(const vector<string>& lines){
    string word = "MAS";
    int countShape = 0;

    size_t lengthWord = word.length();
    if(lengthWord < 3 || lengthWord % 2 != 1) return -1;

    //Search from center of the word
    size_t center = lengthWord / 2;

    string leftPartWord = word.substr(0, center); 
    string rightPartWord = word.substr(center + 1);

    reverse(leftPartWord.begin(), leftPartWord.end());

    for(int i = leftPartWord.length(); i < lines.size() - leftPartWord.length(); i++){
        for(int j = 0; j < lines[i].size(); j++){
            if(lines[i][j] == word[center]){
                vector<int> position = {i, j};
                vector<int> direction1 = {-1, -1};
                vector<int> direction2 = {1, 1};
                vector<int> direction3 = {1, -1};
                vector<int> direction4 = {-1, 1};
                if (((findNextLetter(leftPartWord, lines, 0, position, direction1) && findNextLetter(rightPartWord, lines, 0, position, direction2)) ||
                    (findNextLetter(rightPartWord, lines, 0, position, direction1) && findNextLetter(leftPartWord, lines, 0, position, direction2))) && 
                    ((findNextLetter(leftPartWord, lines, 0, position, direction3) && findNextLetter(rightPartWord, lines, 0, position, direction4)) ||
                    (findNextLetter(rightPartWord, lines, 0, position, direction3) && findNextLetter(leftPartWord, lines, 0, position, direction4)))){
                    countShape++;
                }
            }
        }
    }

    return countShape;                    
}

int main() {
    cout << "Advent of Code 2024" << endl;
    cout << "Day 4: Ceres Search" << endl;
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
    vector<string> lines;

    int puzzleAnswer1 = 0;
    int puzzleAnswer2 = 0;

    //Get data
    while (getline(newfile, line)) {
        lines.push_back(line);
    }
    newfile.close(); 

    //Processing
    puzzleAnswer1 = findXMAS(lines);
    puzzleAnswer2 = findShapeOfXMAS(lines);

    //Show answers
    cout << "Puzzle answer 1 : " << puzzleAnswer1 << endl;
    cout << "Puzzle answer 2 : " << puzzleAnswer2 << endl;

    return 0;
}
