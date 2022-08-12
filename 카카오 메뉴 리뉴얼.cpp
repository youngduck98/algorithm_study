#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<unordered_map>

using namespace std;

bool in_string(string a, char b) {
	for (auto k : a) {
		if (b == k)
			return true;
	}
	return false;
}

bool in_vector(vector<int> a, int b) {
	int l = 0;
	int r = a.size() - 1;
	while (l < r) {
		int mid = (l + r) / 2;
		if (a[mid] == b) { return true; }
		else if (a[mid] > b) { r = mid - 1; }
		else { l = mid + 1; }
	}
	if (l == r && a[l] == b) { return true; }
	return false;
}

void combination(string order, int num, int index, string comb, unordered_map<string, int>& save) {
	//종료 조건
	if (num == comb.length()) {
		//입력을 알파벳 순서로 안 하는 주문도 있음.
		sort(comb.begin(), comb.end());
		if (save.count(comb)) { save[comb]++; }
		else { save.insert({ comb, 1 }); }
		return;
	}
	else if (index >= order.length()) {
		return;
	}

	//해당 index를 선택하지 않음
	combination(order, num, index + 1, comb, save);
	//해당 index를 선택
	comb.push_back(order[index]);
	combination(order, num, index + 1, comb, save);
}


vector<string> solution(vector<string> orders, vector<int> course) {
	vector<string> answer;
	unordered_map<string, int> save_comb;
	//길이별 나누어서 계산(주문 길이: 2~ 10)
	vector<vector<pair<string, int>>> before_answer(11, vector<pair<string, int>>());
	sort(orders.begin(), orders.end());
	for (auto k : orders) {
		for (int i = 2; i <= k.length(); i++) {
			combination(k, i, 0, "", save_comb);
		}
	}

	for (auto k : save_comb) {
		//조합이 2번 이상 주문되었고 course에서 말한 주문길이에 해당할 경우
		if (k.second >= 2 && in_vector(course, k.first.length())) {
			//해당 길이에 아무것도 들어 있지 않은 경우
			if (before_answer[k.first.length()].size() == 0) {
				before_answer[k.first.length()].push_back(k);
			}
			// 해당 길이에 들어있는 값의 주문횟수와 새로 들어오는 값의 주문횟수가 같은 경우
			else if (before_answer[k.first.length()][0].second == k.second) {
				before_answer[k.first.length()].push_back(k);
			}
			//새로 들어오는 값의 주문횟수가 큰 경우
			else if (before_answer[k.first.length()][0].second < k.second) {
				//메모리 누수 없애는 방법 아시는 분?(vector erase함수 제외 - 시간 복잡도 큼)
				vector<pair<string, int>> new_vec(0);
				new_vec.push_back(k);
				before_answer[k.first.length()] = new_vec;
			}
		}
	}

	//before_answer의 값 -> answer
	for (auto a : before_answer) {
		for (auto b : a) {
			answer.push_back(b.first);
		}
	}

	//오름 차순으로 달라고 했으므로
	sort(answer.begin(), answer.end());
	return answer;
}

int main() {
	vector<string> orders = { "ABCDE", "AB", "CD", "ADE", "XYZ", "XYZ", "ACD" };
	vector<int> course = { 2, 3, 4 };
	vector<string> answer = solution(orders, course);
	for (auto s : answer) {
		cout << s << " ";
	}
	cout << endl;
}