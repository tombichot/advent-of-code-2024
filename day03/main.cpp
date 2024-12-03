#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

vector<std::vector<int>> findMulExpressionsPart2(const string& input) {
    vector<std::vector<int>> multiplications;

    bool enable = true;

    std::regex mulRegex(R"(mul\((-?\d+),(-?\d+)\))");
    std::regex doRegex(R"(do\(\))");
    std::regex dontRegex(R"(don't\(\))");

    std::regex globalRegex(R"(do\(\)|don't\(\)|mul\((-?\d+),(-?\d+)\))");
    auto matchesBegin = std::sregex_iterator(input.begin(), input.end(), globalRegex);
    auto matchesEnd = std::sregex_iterator();

    for (auto it = matchesBegin; it != matchesEnd; ++it) {
        std::smatch match = *it;
        std::string matchedStr = match.str();

        if (std::regex_match(matchedStr, doRegex)) {
            enable = true; 
        } else if (std::regex_match(matchedStr, dontRegex)) {
            enable = false;
        } else if (std::regex_match(matchedStr, mulRegex) && enable) {
            int x = std::stoi(match[1].str());
            int y = std::stoi(match[2].str());
            multiplications.push_back({x, y});
        }
    }

    return multiplications;
}  

vector<vector<int>> findMulExpressionsPart1(const string& input) {
    vector<vector<int>> multiplications;
    cout << input << endl;

    std::regex mulRegex(R"(mul\((-?\d+),(-?\d+)\))");

    auto matchesBegin = std::sregex_iterator(input.begin(), input.end(), mulRegex);
    auto matchesEnd = std::sregex_iterator();

    for (auto it = matchesBegin; it != matchesEnd; ++it) {
        std::smatch match = *it;

        int x = std::stoi(match[1].str());
        int y = std::stoi(match[2].str()); 

        multiplications.push_back({x, y});
    }

    return multiplications;
}

int getResultOfAllMultiplications(const string& program, const int part){
    int result = 0;

    vector<vector<int>> multiplications = part == 1 ? findMulExpressionsPart1(program) : findMulExpressionsPart2(program);

    for(int i = 0; i < multiplications.size(); i++){
        result += multiplications[i][0] * multiplications[i][1];
    }

    return result;
}

int main() {
    cout << "Advent of Code 2024" << endl;
    cout << "Day 3: Mull It Over" << endl;
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
    int num;

    int puzzleAnswer1 = 0;
    int puzzleAnswer2 = 0;

    string program;

    //Get data

    std::ostringstream buffer; 
    buffer << newfile.rdbuf();
    program = buffer.str();

    newfile.close(); 

    puzzleAnswer1 = getResultOfAllMultiplications(program,1);
    puzzleAnswer2 = getResultOfAllMultiplications(program,2);

    //Show answers
    cout << "Puzzle answer 1 : " << puzzleAnswer1 << endl;
    cout << "Puzzle answer 2 : " << puzzleAnswer2 << endl;

    return 0;
}
