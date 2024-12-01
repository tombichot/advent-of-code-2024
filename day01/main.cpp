#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>

using namespace std;

/*
* Get total distance between the left list and the right list by adding up the distances between all of the pairs.
*/
int getTotalDistance(const std::list<int>& leftList, const std::list<int>& rightList)
{
    int distance = 0;

    auto it1 = leftList.begin();
    auto it2 = rightList.begin();

    while (it1 != leftList.end() && it2 != rightList.end()) {
        distance += std::abs(*it1 - *it2);
        ++it1;
        ++it2;
    }

    return distance;
}

/*
* Get total similarity score by adding up each number in the left list after multiplying it by the number of times that number appears in the right list.
*/
int getSimilarityScore(const std::list<int>& leftList, const std::list<int>& rightList){
    
    int similarityScore = 0;

    auto it2 = rightList.begin();

    int lastID = 0;
    int lastScore = 0;

    for (auto it1 = leftList.begin(); it1 != leftList.end(); ++it1) {
        if(lastID != *it1){
             
            lastID = *it1;
            int count = 0;

            while (*it2 <= *it1 && it2 != rightList.end()) {
                if(*it2 == *it1) ++count;
                ++it2;
            }

            lastScore = lastID * count;
         }

        similarityScore += lastScore;
    }

    return similarityScore;
}

int main() {
    cout << "Advent of Code 2024" << endl;
    cout << "Day 1: Historian Hysteria" << endl;
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
    int num1, num2;

    list<int> leftList;
    list<int> rightList;

    int puzzleAnswer1 = 0;
    int puzzleAnswer2 = 0;

    while (getline(newfile, line)) { 
        std::istringstream iss(line);
        if (iss >> num1 >> num2) {   
            leftList.push_back(num1);
            rightList.push_back(num2);
        }
    }

    newfile.close(); 

    leftList.sort();
    rightList.sort();

    puzzleAnswer1 = getTotalDistance(leftList, rightList);
    puzzleAnswer2 = getSimilarityScore(leftList, rightList);

    //Answers
    cout << "Puzzle answer 1 : " << puzzleAnswer1 << endl;
    cout << "Puzzle answer 2 : " << puzzleAnswer2 << endl;

    return 0;
}