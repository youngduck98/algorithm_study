#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<map>

using namespace std;

bool compare1(pair<int, int> a, pair<int, int> b) {
    return a.first < b.first;
}

bool compare2(pair<int, int> a, pair<int, int> b) {
    return a.second < b.second;
}

bool compare(int a, int b) {
    return a < b;
}

void minusv(vector<int>& a, int b) {
    for (auto& i : a) {
        i -= b;
    }
}

int solution(vector<int> food_times, long long time) {
    int answer = 0, add = 0;
    vector<int> new_food_times;
    for (int i = 0; i < food_times.size(); i++) {
        new_food_times.push_back(food_times[i]);
    }

    //먹는데 적게 걸리는 것이 먼저 사라지므로
    sort(new_food_times.begin(), new_food_times.end(), compare);


    int num = new_food_times.size();
    int zero_count = 0;
    int before_add = 0;
    for (int i = 0; i < num; i++) {
        int add = new_food_times[i]- before_add;
        //이전 수와 같다.
        if (add <= 0) {
            zero_count++;
            continue; 
        }
        //더 크다.
        else {
            long long count = 1ll*add * (num - i);
            //해당 수를 0을 만들 만큼 돌 수 있다.
            if (time >= count) {
                time -= count;
                before_add += add;
                zero_count++;
            }
            // 그렇지 않다.
            else {
                //사라지는 음식이 없으므로
                time %= (num - zero_count);
                break;
            }
        }
    }

    //food_times에서 다 먹은 음식을 0이하로 만든다.
    minusv(food_times, before_add);

    if (zero_count >= num)
        return -1;

    //줄어든 k를 활용하여 계산(마지막 과정)
    int now = 0;
    for (int i = 0; i < time; i++, now = (now + 1) % food_times.size()) {
        if (food_times[now] <= 0)
            i--;
    }

    //다음 음식이 먹은 음식이였을 경우
    while (food_times[now] <= 0) {
        //남은 음식 까지 진행
        now = (now + 1) % food_times.size();
    }

    //현재 now는 index이므로
    return now + 1;
}

int main() {
    vector<int> food_times = { 3,1,5,7,9,3,4,6,7,9 };
    std::cout << solution(food_times, 31) << endl;
}