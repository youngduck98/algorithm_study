#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

int solution(vector<int> food_times, long long k) {
    int now = 0;
    int num_food = food_times.size();
    int zero_count = 0;
    for (long long i = 0; i < k; i++, now = (now + 1) % (num_food)) {
        if (food_times[now] != 0) {
            food_times[now]--;
            if (food_times[now] == 0) {
                zero_count++;
                if (zero_count == num_food){ return -1; }
            }
        }
        else {
            i--;
            continue;
        }
    }

    if (zero_count == num_food) {
        return -1;
    }

    else {
        while (food_times[now] == 0) {
            now = (now + 1) % (num_food);
        }
        return now + 1;
    }
}

int main() {
    vector<int> food_times = { 3,1,5,7,9,3,4,6,7,9 };
    std::cout << solution(food_times, 31) << endl;
}