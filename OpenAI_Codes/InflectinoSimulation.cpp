#include<iostream>
#include<vector>
#include<queue>
using namespace std;

const int INF = 1e9 + 7;

// possible directions (up, left, right, down respectively)
const int xDir[] = {-1, 0, 0, 1};
const int yDir[] = {0, -1, 1, 0};

bool checkBound(int x, int y, int N, int M){
    return (x >= 0 && y >= 0 && x < N && y < M);
}

bool checkCell(int x, int y, int N, int M, const vector<vector<char>> &grid){
    if(!checkBound(x, y, N, M)) return 0;
    bool notImmune = (grid[x][y] != '#');
    if(!notImmune) return 0;
    return 1;
}

int minimumDaysUntilFixed(int N, int M, vector<vector<char>> &grid, int D){
    vector<vector<int>> infectedDate;
    infectedDate.resize(N);
    queue<pair<int, int>> infectedNodes;
    queue<pair<int, int>> gettingImmuned;
    for(int i = 0; i < N; i++){
        infectedDate[i].resize(M);
        for(int j = 0; j < M; j++){
            if(grid[i][j] == 'X'){// infected node at time 0
                infectedDate[i][j] = 0;
                infectedNodes.push(make_pair(i, j));
            }
            else{
                infectedDate[i][j] = INF;
            }
        }
    }
    /*
    Observation: infectedNodes and gettingImmuned will both be sorted by infected time
    */
    while(!infectedNodes.empty()){
        pair<int, int> currentCell = infectedNodes.front();
        infectedNodes.pop();
        int curX = currentCell.first, curY = currentCell.second;
        int curTime = infectedDate[curX][curY];
        // Start of immune part
        while(!gettingImmuned.empty()){
            pair<int, int> candidateCell = gettingImmuned.front();
            int canX = candidateCell.first, canY = candidateCell.second;
            if(curTime >= (infectedDate[canX][canY] + D)){
                grid[canX][canY] = '#';
                gettingImmuned.pop();
            }
            else break;
        }
        // End of immune part
        for(int i = 0; i < 4; i++){
            int newX = curX + xDir[i], newY = curY + yDir[i];
            if(!checkCell(newX, newY, N, M, grid)) continue;
            if(infectedDate[newX][newY] > (infectedDate[curX][curY] + 1)){
                infectedDate[newX][newY] = infectedDate[curX][curY] + 1;
                infectedNodes.push(make_pair(newX, newY));
                gettingImmuned.push(make_pair(newX, newY));
            }
        }
    }
    int answer = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            bool immuneFromStart = (infectedDate[i][j] == INF);
            if(immuneFromStart) continue;
            answer = max(answer, infectedDate[i][j] + D);
        }
    }
    return answer;
}

int main(){
    int N, M;
    vector<vector<char>> grid;
    int D;
    N = M = 3;
    grid = {{'X', '.', '.'}, {'.', '.', '.'}, {'.', '.', '.'}};
    D = 2;
    cout << minimumDaysUntilFixed(N, M, grid, D) << "\n";
    N = M = 3;
    grid = {{'X', '#', '.'}, {'.', '#', '.'}, {'.', '.', '#'}};
    D = 3;
    cout << minimumDaysUntilFixed(N, M, grid, D) << "\n";
}