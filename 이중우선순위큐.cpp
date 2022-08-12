#include <string>
#include <vector>
#include<queue>
#include <iostream>
#include <set>

struct cmp_u {
    bool operator()(int a, int b) {
        return a < b;
    }
};

struct cmp_d {
    bool operator()(int a, int b) {
        return a > b;
    }
};


using namespace std;

void get_command(priority_queue<int, vector<int>, cmp_u>& max, priority_queue<int, vector<int>, cmp_d>& min, string command, int& size) {
    if (size == 0) {
        max = {};
        min = {};
    }
    if (command == "D 1") {
        if (size == 0) { return; }
        else {
            max.pop();
            size--;
        }
    }
    else if (command == "D -1") {
        if (size == 0) { return; }
        else {
            min.pop();
            size--;
        }
    }
    else {
        size++;
        int a = stoi(command.substr(1));
        max.push(a);
        min.push(a);
    }
}

vector<int> solution(vector<string> operations) {
    priority_queue<int, vector<int>, cmp_u> max;
    priority_queue<int, vector<int>, cmp_d> min;
    int size = 0;

    for (auto k : operations) {
        get_command(max, min, k, size);
    }

    vector<int> answer(0);
    vector<int> zero = { 0,0 };

    if (size == 0) {
         answer = zero;
    }
    else {
        answer.push_back(max.top());
        answer.push_back(min.top());
    }

    cout << size << endl;

    return answer;
}

vector<int> solution1(vector<string> arguments) {
    vector<int> answer;
    multiset<int> que;
    multiset<int>::iterator iter;
    string sub;

    for (auto s : arguments) {
        sub = s.substr(0, 2);
        if (sub == "I ") que.insert(stoi(s.substr(2)));
        else if (s.substr(2, 1) == "1" && que.size() > 0) { que.erase(--que.end()); }
        else if (que.size() > 0) { que.erase(que.begin()); }
    }

    if (que.size() == 0) { answer.push_back(0); answer.push_back(0); }
    else {
        iter = --que.end(); answer.push_back(*iter);
        iter = que.begin(); answer.push_back(*iter);
    }

    return answer;
}

int main() {
   vector<string> operations = { "I 4", "I 3", "I 2", "I 1", "D 1", "D 1", "D -1", "I 5", "I 6", "D -1"};
   vector<int> answer = solution(operations);
   for (auto k : answer) {
       cout << k;
   }
   cout << endl;
}
//4321 -> 21 -> 2 -> 256 -> 56 -> 65