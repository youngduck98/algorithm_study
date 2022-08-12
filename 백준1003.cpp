#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> answer(0);
    vector < pair<int, int>> f_answer(0);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        answer.push_back(make_pair(1, 0));
        answer.push_back(make_pair(0, 1));
        for (int i = 2; i <= k; i++) {
            answer.push_back(make_pair(answer[i - 1].first + answer[i - 2].first, answer[i-1].second + answer[i-2].second));
        }
        f_answer.push_back(answer[k]);
        answer.clear();
    }

    for (auto p1 : f_answer) {
        cout << p1.first << " " << p1.second << endl;
    }
}