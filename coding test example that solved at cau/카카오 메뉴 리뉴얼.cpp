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
	//���� ����
	if (num == comb.length()) {
		//�Է��� ���ĺ� ������ �� �ϴ� �ֹ��� ����.
		sort(comb.begin(), comb.end());
		if (save.count(comb)) { save[comb]++; }
		else { save.insert({ comb, 1 }); }
		return;
	}
	else if (index >= order.length()) {
		return;
	}

	//�ش� index�� �������� ����
	combination(order, num, index + 1, comb, save);
	//�ش� index�� ����
	comb.push_back(order[index]);
	combination(order, num, index + 1, comb, save);
}


vector<string> solution(vector<string> orders, vector<int> course) {
	vector<string> answer;
	unordered_map<string, int> save_comb;
	//���̺� ����� ���(�ֹ� ����: 2~ 10)
	vector<vector<pair<string, int>>> before_answer(11, vector<pair<string, int>>());
	sort(orders.begin(), orders.end());
	for (auto k : orders) {
		for (int i = 2; i <= k.length(); i++) {
			combination(k, i, 0, "", save_comb);
		}
	}

	for (auto k : save_comb) {
		//������ 2�� �̻� �ֹ��Ǿ��� course���� ���� �ֹ����̿� �ش��� ���
		if (k.second >= 2 && in_vector(course, k.first.length())) {
			//�ش� ���̿� �ƹ��͵� ��� ���� ���� ���
			if (before_answer[k.first.length()].size() == 0) {
				before_answer[k.first.length()].push_back(k);
			}
			// �ش� ���̿� ����ִ� ���� �ֹ�Ƚ���� ���� ������ ���� �ֹ�Ƚ���� ���� ���
			else if (before_answer[k.first.length()][0].second == k.second) {
				before_answer[k.first.length()].push_back(k);
			}
			//���� ������ ���� �ֹ�Ƚ���� ū ���
			else if (before_answer[k.first.length()][0].second < k.second) {
				//�޸� ���� ���ִ� ��� �ƽô� ��?(vector erase�Լ� ���� - �ð� ���⵵ ŭ)
				vector<pair<string, int>> new_vec(0);
				new_vec.push_back(k);
				before_answer[k.first.length()] = new_vec;
			}
		}
	}

	//before_answer�� �� -> answer
	for (auto a : before_answer) {
		for (auto b : a) {
			answer.push_back(b.first);
		}
	}

	//���� �������� �޶�� �����Ƿ�
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