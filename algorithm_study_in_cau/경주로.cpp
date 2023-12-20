#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

bool in_vector(vector<pair<int, int>> record, int x, int y) {
    for (auto k : record) {
        if (k.first == x && k.second == y) {return true;}
    }
    return false;
}

void dfs(vector<vector<int>> board, int a, int b, int& answer, vector<pair<int, int>> record) {
   //padding
    vector<int> front_back(board.size() + 2, 1);
    board.push_back(front_back);
    board.insert(board.begin(), front_back);
    for (auto& i1 : board) {
        i1.insert(i1.begin(), 1);
        i1.push_back(1);
    }
    
    vector<pair<int, int>> dir;
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            if (x == 0 && y == 0) { continue; }
            dir.push_back(make_pair(x, y));
        }
    }

    for (auto k : dir) {
        int x = k.first + a;
        int y = k.second + b;
        if (board[x][y] == 0 && !in_vector(record, x, y)) { 
            dfs(board, x, y, answer, record);

        }
    }
}

int solution(vector<vector<int>> board) {
    int answer = INT_MAX;


    return answer;
}

int main() {

}