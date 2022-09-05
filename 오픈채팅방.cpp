#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<sstream>
#include<map>

using namespace std;

vector<string> solution(vector<string> record) {
	vector<string> answer;
	vector<vector<string>> new_record(record.size(), vector<string>(3));

	int i = 0;
	//공백 구분하여 저장
	for (auto k : record) {
		stringstream cut_str(k);
		cut_str >> new_record[i][0];
		if (new_record[i][0] == "Enter" || new_record[i][0] == "Change") {
			cut_str >> new_record[i][1] >> new_record[i][2];
		}
		else if (new_record[i][0] == "Leave") {
			cut_str >> new_record[i][1];
		}
		i++;
	}

	//map 사용하여 id와 닉네임 사전 생성
	map<string, string> maps;
	for (auto k : new_record) {
		if (k[0] != "Leave") { maps[k[1]] = k[2]; }
	}

	//해당 사전 활용하여 answer생성
	for (auto k : new_record) {
		if (k[0] == "Enter") {
			answer.push_back(maps[k[1]] + "님이 들어왔습니다.");
		}
		else if (k[0] == "Leave") {
			answer.push_back(maps[k[1]] + "님이 나갔습니다.");
		}
	}
	return answer;
}

int main() {
	vector<string> record = { "Enter uid1234 Muzi", "Enter uid4567 Prodo", "Leave uid1234", "Enter uid1234 Prodo", "Change uid4567 Ryan" };
	vector<string> answer = solution(record);
	for (auto k : answer) {
		cout << k << endl;
	}
}