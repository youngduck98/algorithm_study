#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int min(int a, int b) {
    if (a > b) {
        return b;
    }
    return a;
}
int dfs(int now, int visited, const vector<vector<int>> &cost, vector<vector<int>>& DP) {
    if (visited == (1 << cost.size()) - 1) { return 0; }
    if (DP[now][visited] != -1) { return DP[now][visited]; }
    DP[now][visited] = 200000;
    for (int i = 0; i < cost.size(); i++) {
        if (visited & (1 << i)) { continue; }
        DP[now][visited] = min(DP[now][visited],
            dfs(now + 1, visited | (1 << i), cost, DP) + cost[now][i]);
    }
    return DP[now][visited];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<vector<int>> D(n, vector<int>(n, 0));
    vector<vector<int>> DP(n, vector<int>(1<<21, -1));
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cin >> D[r][c];
        }
    }
    cout << dfs(0, 0, D, DP) << '\n';
    return 0;
}
