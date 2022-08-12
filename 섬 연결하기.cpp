#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

bool cmp_vector(vector<int> a, vector<int> b) {
    return a[2] < b[2];
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    sort(costs.begin(), costs.end(), cmp_vector);

    //index -> serial of island, value -> set_num 
    vector<int> check_cycle(n);
    for (int i = 0; i < n; i++) {
        check_cycle[i] = i;
    }
   
    for (auto k : costs) {
        if (check_cycle[k[0]] == check_cycle[k[1]]) { continue; }
        else {
            if (k[0] > k[1]) {
                int a = check_cycle[k[0]];
                check_cycle[k[0]] = check_cycle[k[1]];
                for (int i = 0; i < n; i++) {
                    if (check_cycle[i] == a) {
                        check_cycle[i] = check_cycle[k[1]];
                    }
                }
            }
            else {
                int a = check_cycle[k[1]];
                check_cycle[k[1]] = check_cycle[k[0]];
                for (int i = 0; i < n; i++) {
                    if (check_cycle[i] == a) {
                        check_cycle[i] = check_cycle[k[0]];
                    }
                }
            }

            answer += k[2];
        }
    }

    return answer;
}

int main() {
    vector<vector<int>> cost = { {0, 1, 1} ,{0, 2, 2},{1, 2, 5},{1, 3, 1},{2, 3, 8} };
    int answer = solution(5, cost);
    cout << answer << endl;
}