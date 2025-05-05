#include<iostream>
#include<vector>
#include<queue> 
#include<cmath>
#include<algorithm>
#include<unordered_set>
#include<unordered_map>

using namespace std;

const int N = 3;

struct PuzzleState{
    int puzzle[N][N];
    int zeroRow, zeroCol;
    int g;
    int h;

    bool operator<(const PuzzleState &other) const{
        return (g+h) > (other.g +  other.h);
    }   
};

void printPuzzle(const PuzzleState &state){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cout << state.puzzle[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-----\n";
}

bool isEqual(const PuzzleState &state1, const PuzzleState &state2){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (state1.puzzle[i][j] != state2.puzzle[i][j])
                return false;
        }
    }
    return true;
}

int calcManhattanDistance(const PuzzleState &state, const PuzzleState &goalState){
    int distance = 0;
    unordered_map<int, pair<int, int>> goalPosition;

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            goalPosition[goalState.puzzle[i][j]] = {i, j};
        }
    }

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            int val = state.puzzle[i][j];
            if (val != 0){
                auto [goalRow, goalCol] = goalPosition[val];
                distance += abs(i - goalRow) + abs(j - goalCol);
            }
        }
    }
    return distance;
}

bool isValid(int row, int col){
    return (row >= 0 && row < N && col >= 0 && col < N);
}

vector<PuzzleState> generateNextStates(const PuzzleState &currentState, const PuzzleState &goalState){
    vector<PuzzleState> nextStates;
    const int dr[] = {-1, 1, 0, 0};
    const int dc[] = {0, 0, -1, 1};  
    int zeroRow = currentState.zeroRow;
    int zeroCol = currentState.zeroCol;
    for(int i = 0; i < 4; i++){
        int newRow = zeroRow + dr[i];
        int newCol = zeroCol + dc[i];
        if(isValid(newRow, newCol)){
            PuzzleState nextState = currentState;
            swap(nextState.puzzle[zeroRow][zeroCol], nextState.puzzle[newRow][newCol]);
            nextState.zeroRow = newRow;
            nextState.zeroCol = newCol;
            nextState.g = currentState.g + 1;
            nextState.h = calcManhattanDistance(nextState, goalState);  
            nextStates.push_back(nextState);    
        }
    }
    return nextStates;
}

PuzzleState getPuzzleState(const string &msg, const PuzzleState &goal, bool isGoal = false) {
    PuzzleState state;
    cout << msg << " (0 = empty tile):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << "Enter value at (" << i << ", " << j << "): ";
            cin >> state.puzzle[i][j];
            if (state.puzzle[i][j] == 0) {
                state.zeroRow = i;
                state.zeroCol = j;
            }
        }
    }
    state.g = 0;
    if (isGoal) {
        state.h = 0;
    } else {
        state.h = calcManhattanDistance(state, goal);
    }
    return state;
}

void aStarSearch(const PuzzleState &initialState, const PuzzleState &goalState) {
    priority_queue<PuzzleState> pq;
    unordered_set<int> visited;
    pq.push(initialState);
    visited.insert(0); 
        
    while(!pq.empty()) {
        PuzzleState current = pq.top();
        pq.pop();
        
        cout << "Current State:\n";
        printPuzzle(current);
        
        if (isEqual(current, goalState)) {
            cout << "Goal state reached in " << current.g << " moves.\n";
            return;
        }
        
        vector<PuzzleState> nextStates = generateNextStates(current, goalState);
        
        for (const PuzzleState &nextState : nextStates) {
            int hash = 0;
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    hash = hash * 10 + nextState.puzzle[i][j];
            
            if (visited.find(hash) == visited.end()) {
                pq.push(nextState);
                visited.insert(hash);
            }
        }
    }
}

int main() {
    PuzzleState goal = getPuzzleState("Enter Goal State", PuzzleState(), true);
    PuzzleState initial = getPuzzleState("Enter Initial State", goal, false);   
    cout << "Initial State:\n";
    printPuzzle(initial);   
    cout << "Goal State:\n";
    printPuzzle(goal);
    aStarSearch(initial, goal);
    cout << "A* Search completed.\n";
    return 0;
}
    