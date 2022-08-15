#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
#include<set>

using namespace std;

int set_num = 0;

void BFS(int row, int col, vector<vector<int>> land, int height, vector<vector<int>>& BFS_visited, vector<int>& parent) {
    queue<pair<int, int>>  Q;
    Q.push(make_pair(row, col));
    BFS_visited[row][col] = ++set_num;;
    int draw[4] = { -1, 1, 0, 0 };
    int dcol[4] = { 0, 0 ,-1, 1 };
    parent.push_back(set_num);
    //cout << set_num << ": " << row << " " << col << endl;
    while (!Q.empty()) {
        int now_raw = Q.front().first;
        int now_col = Q.front().second;
        Q.pop();

        for (int i = 0; i < 4; i++) {
            int new_raw = now_raw + draw[i];
            int new_col = now_col + dcol[i];
            if (new_raw >= 0 && new_raw < land.size() && new_col >= 0 && new_col < land.size()) {
                if (BFS_visited[new_raw][new_col] == 0 && abs(land[now_raw][now_col] - land[new_raw][new_col]) <= height) {
                    //cout << set_num << ": " << new_raw << " " << new_col << endl;
                    Q.push(make_pair(new_raw, new_col));
                    BFS_visited[new_raw][new_col] = set_num;
                }
            }
        }
    }
}

void make_group(vector<vector<int>> land, int height, vector<vector<int>>& BFS_visited, vector<int>&parent) {
    for (int raw = 0; raw < land.size(); raw++) {
        for (int col = 0; col < land[raw].size(); col++) {
            if (BFS_visited[raw][col] == 0) {
                BFS(raw, col, land, height, BFS_visited, parent);
            }
        }
    }
}

class graph_edge {
public:
    int start_set;
    int end_set;
    int cost;
    graph_edge(int, int, int);
};

graph_edge::graph_edge(int start_set, int end_set, int cost) {
    this->start_set = start_set;
    this->end_set = end_set;
    this->cost = cost;
}

vector<graph_edge> cal_set_edge(vector<vector<int>> land, int height, vector<vector<int>>& BFS_visited) {
    vector<pair<int, int>> v = { make_pair(1,0), make_pair(0,1) };
    vector<graph_edge> graph;
    for (int raw = 0; raw < land.size(); raw++) {
        for (int col = 0; col < land[raw].size(); col++) {
            for (auto k : v) {
                int new_raw = raw + k.first;
                int new_col = col + k.second;
                if (new_raw >= 0 && new_raw < land.size() && new_col >= 0 && new_col < land.size()) {
                    if (BFS_visited[raw][col] != BFS_visited[new_raw][new_col]) {
                        //cout << "BFS" << raw << col << new_raw << new_col <<abs(land[new_raw][new_col] - land[raw][col]) << endl;
                        graph.push_back(graph_edge(BFS_visited[raw][col], BFS_visited[new_raw][new_col], abs(land[new_raw][new_col] - land[raw][col])));
                        graph.push_back(graph_edge(BFS_visited[new_raw][new_col], BFS_visited[raw][col], abs(land[new_raw][new_col] - land[raw][col])));
                    }
                }
            }
        }
    }
    return graph;
}

int find_parent(int set_num, vector<int>& parent) {
    if (parent[set_num] == set_num) {
        return set_num;
    }
    else {
        parent[set_num] = find_parent(parent[set_num], parent);
        return parent[set_num];
    }
}

bool cmp(graph_edge a, graph_edge b) {
    return a.cost < b.cost;
}

int solution(vector<vector<int>> land, int height) {
    //BFS를 통한 해당 정점 포함하는 그룹 묶기
    //각 set을 정점으로 보고 각 set간의 최소 edge 찾기
    //크루스칼 알고리즘에 대입
    //정답 도출
    vector<vector<int>> BFS_visited(land.size(), vector<int>(land[0].size(), 0));
    vector<int> parent(1, 0);
    make_group(land, height, BFS_visited, parent);

    vector<graph_edge> graph = cal_set_edge(land, height, BFS_visited);

    sort(graph.begin(), graph.end(), cmp);

    int answer = 0;

    for (int i = 0; i < graph.size(); i++) {
        int start_set = find_parent(graph[i].start_set, parent);
        int end_set = find_parent(graph[i].end_set, parent);
        int cost = graph[i].cost;

        if (start_set != end_set) {
            //cout << start_set << end_set << cost << endl;
            answer += cost;
            parent[end_set] = parent[start_set];
        }
    }

    return answer;
}

int main() {
    vector<vector<int>> land = { {1, 4, 8, 10} ,{5, 5, 5, 5},{10, 10, 10, 10},{10, 10, 10, 20} };
    cout << solution(land, 3) << endl;
}