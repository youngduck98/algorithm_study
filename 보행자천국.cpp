#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

int MOD = 20170805;
/*
* in map, we move from (0,0) to (m-1, n-1). calculate the number of way.
* 0-> any way, 1-> maintain direction, 2-> can't go
* DP? how to make this small one?
* 2*2
* 01
* 00
* -> just one way
* need to store every root
* 4 way -> (+-1, 0), (0, +-1)
* in this way if we want to move then we must know before move direction
* direction 1(1, 0), 2(-1,0), 3(0,1), 4(0,-1)
* class attribute -> position info, direction
* que -> 1. store calss, 2. pick one, 3. input can move all direction(with compare destination) 4. go to 2)
*/
// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.

class que_element {
public:
    pair<int, int> position;
    int direction;
    que_element(pair<int, int> position, int direction);
};
que_element::que_element(pair<int, int> position, int direction) {
    this->position = position;
    this->direction = direction;
}

int solution(int m, int n, vector<vector<int>> city_map) {
    int answer = 0;
    queue<que_element> position_que;
    position_que.push(que_element(make_pair(0, 0), 0));

    while (!position_que.empty()) {
        que_element now = position_que.front();
        position_que.pop();

        int f_row = now.position.first;
        int f_col = now.position.second;

        if ((now.position.first == m - 2 && now.position.second == n - 1) || (now.position.first == m - 1 && now.position.second == n - 2)) {
            answer++;
            continue;
        }
        else if (now.direction == 0 || city_map[now.position.first][now.position.second] == 0) {
            if (now.direction == 0) {

            }
            if (now.direction == 1) {
                if (f_row + 1 < m - 1 && city_map[f_row + 1][f_col] != 2) {
                    position_que.push(que_element(make_pair(f_row + 1, f_col), 1));
                }
                if (f_col + 1 < n - 1 && city_map[f_row + 1][f_col] != 2) {
                    position_que.push(que_element(make_pair(f_row, f_col + 1), 3));
                }
                if (f_row - 1 >= 0 && city_map[f_row + 1][f_col] != 2) {
                    position_que.push(que_element(make_pair(f_row + 1, f_col - 1), 4));
                }
            }
            else if (now.direction == 2 && f_row - 1 >= 0 && city_map[f_row + 1][f_col] != 2) {
                if (f_row - 1 >= 0 && city_map[f_row + 1][f_col] != 2) {
                    position_que.push(que_element(make_pair(f_row - 1, f_col), 2));
                }
                if (f_col + 1 < n - 1 && city_map[f_row + 1][f_col] != 2) {
                    position_que.push(que_element(make_pair(f_row, f_col + 1), 3));
                }
                if (f_row - 1 >= 0 && city_map[f_row + 1][f_col] != 2) {
                    position_que.push(que_element(make_pair(f_row + 1, f_col - 1), 4));
                }
            }
            else if (now.direction == 3 && f_col + 1 < n - 1 && city_map[f_row + 1][f_col] != 2) {
                if (f_row + 1 < m - 1 && city_map[f_row + 1][f_col] != 2) {
                    position_que.push(que_element(make_pair(f_row + 1, f_col), 1));
                }
                if (f_row - 1 >= 0 && city_map[f_row + 1][f_col] != 2) {
                    position_que.push(que_element(make_pair(f_row - 1, f_col), 2));
                }
                if (f_col + 1 < n - 1 && city_map[f_row + 1][f_col] != 2) {
                    position_que.push(que_element(make_pair(f_row, f_col + 1), 3));
                }
            }
            else if (now.direction == 4 && f_col - 1 >= 0 && city_map[f_row + 1][f_col] != 2) {
                if (f_row + 1 < m - 1 && city_map[f_row + 1][f_col] != 2) {
                    position_que.push(que_element(make_pair(f_row + 1, f_col), 1));
                }
                if (f_row - 1 >= 0 && city_map[f_row + 1][f_col] != 2) {
                    position_que.push(que_element(make_pair(f_row - 1, f_col), 2));
                }
                if (f_row - 1 >= 0 && city_map[f_row + 1][f_col] != 2) {
                    position_que.push(que_element(make_pair(f_row + 1, f_col - 1), 4));
                }
            }
        }
        else if (city_map[now.position.first][now.position.second] == 1) {
            if (now.direction == 1 && f_row + 1 < m - 1 && city_map[f_row + 1][f_col] != 2) {
                position_que.push(que_element(make_pair(f_row + 1, f_col), 1));
            }
            else if (now.direction == 2 && f_row - 1 >= 0 && city_map[f_row + 1][f_col] != 2) {
                position_que.push(que_element(make_pair(f_row - 1, f_col), 2));
            }
            else if (now.direction == 3 && f_col + 1 < n - 1 && city_map[f_row + 1][f_col] != 2) {
                position_que.push(que_element(make_pair(f_row, f_col + 1), 3));
            }
            else if (now.direction == 4 && f_col - 1 >= 0 && city_map[f_row + 1][f_col] != 2) {
                position_que.push(que_element(make_pair(f_row, f_col - 1), 4));
            }
        }
    }
    return answer % MOD;
}