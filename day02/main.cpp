#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int getNumberOfSafeReportPart1(const std::vector<vector<int>>& reports)
{
    int numberOfSafeReport = 0;

    for(int i = 0; i < reports.size(); i++) { 
        int last = -1;
        int increase = 0;
        bool safe = true;

        vector<int> report = reports[i];

        for(int j = 0; j < report.size(); j++){
            if (last != -1) {
                if (report[j] == last || abs(report[j] - last) > 3 || 
                (increase == 1 && report[j] < last) || 
                (increase == -1 && report[j] > last)) {
                    safe = false;
                    break;
                }
                if (increase == 0) {
                    increase = (report[j] > last) ? 1 : -1;
                }
            }
            last = report[j];
        }
        if (safe){
            numberOfSafeReport++;
        }
    }

    return numberOfSafeReport;
}

int getNumberOfSafeReportPart2(const std::vector<vector<int>>& reports)
{
    int numberOfSafeReport = 0;
    int removedIndex = -1;

    int i = 0;
    while(i < reports.size()) { 
        int last = -1;
        int increase = 0;
        bool safe = true;
        
        vector<int> report = reports[i];

        if(removedIndex > -1){
           report.erase(report.begin() + removedIndex);
        }

        for(int j = 0; j < report.size(); j++){
            if (last != -1) {
                if (report[j] == last || abs(report[j] - last) > 3 || 
                (increase == 1 && report[j] < last) || 
                (increase == -1 && report[j] > last)) {
                    safe = false;
                    break;
                }
                if (increase == 0) {
                    increase = (report[j] > last) ? 1 : -1;
                }
            }
            last = report[j];
        }
        if (safe){
            numberOfSafeReport++;
            removedIndex = -1;
            i++;
        }else{
            if(removedIndex == reports[i].size() - 1){
                removedIndex = -1;
                i++;                
            }else{
                removedIndex++;
            }
        }
    }

    return numberOfSafeReport;
}

int main() {
    cout << "Advent of Code 2024" << endl;
    cout << "Day 2: Red-Nosed Reports" << endl;
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

    vector<vector<int>> reports;

    //Get data
    while (getline(newfile, line)) { 
        std::stringstream ss(line);
        
        vector<int> report;
        while (ss >> num) {
            report.push_back(num);
            if (ss.peek() == ' ') {
                ss.ignore();
            }
        }
        reports.push_back(report);
    }

    newfile.close(); 

    puzzleAnswer1 = getNumberOfSafeReportPart1(reports);
    puzzleAnswer2 = getNumberOfSafeReportPart2(reports);

    //Show answers
    cout << "Puzzle answer 1 : " << puzzleAnswer1 << endl;
    cout << "Puzzle answer 2 : " << puzzleAnswer2 << endl;

    return 0;
}
