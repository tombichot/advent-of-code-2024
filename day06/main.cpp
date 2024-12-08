#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <set>


using namespace std;
using namespace std::chrono;

struct GuardState {
    pair<int, int> position;
    int direction;

    bool operator<(const GuardState& other) const {
        if (position != other.position) {
            return position < other.position;
        }
        return direction < other.direction;
    }
};

void printMap(const vector<string>& map){
    for(int k = 0; k < map.size(); k++){
        cout << map[k] << endl;
    }
    cout << "----------------" << endl;
}

GuardState getGuardInitialState(const vector<string>& map) {
    vector<char> guardSymbols = {'^', '>', 'v', '<'};

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].length(); j++) {
            for (int k = 0; k < guardSymbols.size(); k++) {
                if (map[i][j] == guardSymbols[k]) {
                    return {{i, j}, k};
                }
            }
        }
    }
    return {{-1, -1}, -1};
}

int countGardDistinctPosition(vector<string> map) {
    vector<pair<int, int>> guardDirections = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    GuardState initialState = getGuardInitialState(map);

    if (initialState.direction == -1) {
        cerr << "Error: unable to find guard initial state" << endl;
        return -1;
    }

    GuardState state = initialState;

    int countDistinctGuardPosition = 1;
    map[initialState.position.first][initialState.position.second] = 'X';

    //Move guard
    do {
        pair<int, int> newPosition = {state.position.first + guardDirections[state.direction].first, state.position.second + guardDirections[state.direction].second};
        if(newPosition.first < 0 || newPosition.first >= map.size() ||
             newPosition.second < 0 || newPosition.second >= map[newPosition.first].length()) break;

        if(map[newPosition.first][newPosition.second] != '#'){
            if(map[newPosition.first][newPosition.second] == '.'){
                //Count position
                map[newPosition.first][newPosition.second] = 'X';
                countDistinctGuardPosition++;
            } 
            state.position = newPosition;
        }else{
            //Turn right
            state.direction++;
            if(state.direction == 4) state.direction = 0;
        }

    } while (true);

    return countDistinctGuardPosition;
}

bool isLooping(const vector<string>& map, const GuardState& initialState){
    vector<pair<int, int>> guardDirections = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    GuardState state = initialState;
    set<GuardState> guardStates;

    //Move guard
    do {
        pair<int, int> newPosition = {state.position.first + guardDirections[state.direction].first, state.position.second + guardDirections[state.direction].second};
        if(newPosition.first < 0 || newPosition.first >= map.size() ||
             newPosition.second < 0 || newPosition.second >= map[newPosition.first].length()) break;

        if(map[newPosition.first][newPosition.second] != '#'){
            state.position = newPosition;
            //Check if guard is looping
            if(!guardStates.insert(state).second) return true;
        }else{
            //Turn right
            state.direction++;
            if(state.direction == 4) state.direction = 0;
        }

    } while (true);

    return false;
}

int countPossibleObstacle(vector<string> map) {
    vector<pair<int, int>> guardDirections = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    GuardState initialState = getGuardInitialState(map);

    if (initialState.direction == -1) {
        cerr << "Error: unable to find guard initial state" << endl;
        return -1;
    }

    GuardState state = initialState;

    map[initialState.position.first][initialState.position.second] = 'X';
    int countPossibleObstacle = 0;

    //Move guard
    do {
        pair<int, int> newPosition = {state.position.first + guardDirections[state.direction].first, state.position.second + guardDirections[state.direction].second};
        if(newPosition.first < 0 || newPosition.first >= map.size() ||
             newPosition.second < 0 || newPosition.second >= map[newPosition.first].length()) break;

        if(map[newPosition.first][newPosition.second] != '#'){
            state.position = newPosition;
            if(map[newPosition.first][newPosition.second] != 'O'){
                vector<string> newMap = map;
                newMap[newPosition.first][newPosition.second] = '#';
                if(isLooping(newMap, initialState)){
                    countPossibleObstacle++;
                    map[newPosition.first][newPosition.second] = 'O';
                }
            }
        }else{
            //Turn right
            state.direction++;
            if(state.direction == 4) state.direction = 0;
        }

    } while (true);

    return countPossibleObstacle;
}

int main() {
    cout << "Advent of Code 2024" << endl;
    cout << "Day 6: Guard Gallivant" << endl;
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
    vector<string> map;

    while (getline(newfile, line)) {
        map.push_back(line);
    }
    newfile.close();

    // Processing
    auto start = high_resolution_clock::now();

    int puzzleAnswer1 = countGardDistinctPosition(map);
    int puzzleAnswer2 = countPossibleObstacle(map);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Execution time : " << duration.count() << " ms" << endl << endl;

    cout << "Puzzle answer 1 : " << puzzleAnswer1 << endl;
    cout << "Puzzle answer 2 : " << puzzleAnswer2 << endl;

    return 0;
}
