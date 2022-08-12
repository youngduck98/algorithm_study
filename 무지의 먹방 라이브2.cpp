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

    //�Դµ� ���� �ɸ��� ���� ���� ������Ƿ�
    sort(new_food_times.begin(), new_food_times.end(), compare);


    int num = new_food_times.size();
    int zero_count = 0;
    int before_add = 0;
    for (int i = 0; i < num; i++) {
        int add = new_food_times[i]- before_add;
        //���� ���� ����.
        if (add <= 0) {
            zero_count++;
            continue; 
        }
        //�� ũ��.
        else {
            long long count = 1ll*add * (num - i);
            //�ش� ���� 0�� ���� ��ŭ �� �� �ִ�.
            if (time >= count) {
                time -= count;
                before_add += add;
                zero_count++;
            }
            // �׷��� �ʴ�.
            else {
                //������� ������ �����Ƿ�
                time %= (num - zero_count);
                break;
            }
        }
    }

    //food_times���� �� ���� ������ 0���Ϸ� �����.
    minusv(food_times, before_add);

    if (zero_count >= num)
        return -1;

    //�پ�� k�� Ȱ���Ͽ� ���(������ ����)
    int now = 0;
    for (int i = 0; i < time; i++, now = (now + 1) % food_times.size()) {
        if (food_times[now] <= 0)
            i--;
    }

    //���� ������ ���� �����̿��� ���
    while (food_times[now] <= 0) {
        //���� ���� ���� ����
        now = (now + 1) % food_times.size();
    }

    //���� now�� index�̹Ƿ�
    return now + 1;
}

int main() {
    vector<int> food_times = { 3,1,5,7,9,3,4,6,7,9 };
    std::cout << solution(food_times, 31) << endl;
}