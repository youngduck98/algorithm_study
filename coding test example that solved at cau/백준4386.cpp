#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<cmath>

using namespace std;

float cal_dist(vector<float> a, vector<float> b) {
	return sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2));
}

int main() {
	int n;
	cin >> n;
	vector<vector<float>> star(n, vector<float>(2));
	for (auto& k : star) {
		cin >> k[0] >> k[1];
	}

	set<int>visited;
	set<int>unvisited;
	for (int i = 0; i < n; i++) {
		unvisited.insert(i);
	}
	
	vector<vector<float>> graph(n, vector<float>(n, 0));
	for (int i = 0; i < n; i++) {
		graph[i][i] = 0;
		for (int d = i + 1; d < n; d++) {
			float dist = cal_dist(star[i], star[d]);
			graph[i][d] = dist;
			graph[d][i] = dist;
		}
	}

	float answer = 0;
	visited.insert(0);
	unvisited.erase(0);

	while(!unvisited.empty()) {
		float min_dist = INT_MAX;
		int min_star = 0;
		
		for (auto v : visited) {
			for (auto u : unvisited) {
				if (graph[v][u] < min_dist) {
					min_star = u;
					min_dist = graph[v][u];
				}
			}
		}

		answer += min_dist;
		visited.insert(min_star);
		unvisited.erase(min_star);
	}

	cout << answer << endl;
}