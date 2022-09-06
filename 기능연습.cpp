#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include<iostream>
using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    multiset<int> m_set;
    int before = 0;

    for (int i = 0; i < progresses.size(); i++){
        int term = (100-progresses[i] - 1) / speeds[i] + 1;
        if (i == 0) {
            before = term;
        }
        else if(before > term) {
            term = before;
        }
        else {
            before = term;
        }

        m_set.insert((term));
    }

    for (int i = 0; i <= before; i++) {
        if (m_set.count(i) != 0) {
            answer.push_back(m_set.count(i));
        }
    }

    return answer;
}

int main() {
    vector<int> progress = { 93, 30, 55 };
    vector<int> speed = { 1, 30, 5 };

    vector<int> answer = solution(progress, speed);
    for (auto k : answer) {
        cout << k;
    }
}