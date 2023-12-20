#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

bool cmp(int a, int b) {
    return a < b;
}

int solution(vector<int> people, int limit) {
    int answer = 0;
    sort(people.begin(), people.end(), cmp);

    int r = people.size() - 1;
    int l = 0;

    while (r >= l) {
        if (r == l) {
            answer++;
            break;
        }
        else if (people[r] + people[l] <= limit) {
            r--;
            l++;
            answer++;
        }
        else if (people[r] + people[l] > limit) {
            r--;
            answer++;
        }
    }

    return answer;
}