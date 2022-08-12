#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

void choose(vector<pair<int, int>> k, int i, int n, int price, int before, int& max) {
	if (i == n) {
		if (max < price) {
			max = price;
		}
		return;
	}
	else if (i > n) {
		price = price - before;
		if (max < price) {
			max = price;
		}
		return;
	}
	else {
		choose(k, i + k[i].first, n, price + k[i].second, k[i].second, max);
		choose(k, i + 1, n, price ,before, max);
	}
}

int main() {
	int n;
	cin >> n;

	vector<pair<int, int>> plan(n);
	for (int i = 0; i < n; i++) {
		int cost, price;
		cin >> cost >> price;
		plan[i] = make_pair(cost, price);
	}

	int max = 0;
	choose(plan, 0, n, 0, 0, max);
	cout << max << endl;
}