#include <bits/stdc++.h>

using namespace std;

const int INF = 10000000;

struct edge {
    int dest;
    int len;
};

vector<vector<edge>> graph;

int N, K;

vector<int> dp;

// len_delta, num_delta
pair<int, int> dfs_go(int i, int prev, map<int, int>& dest) {
    vector<map<int, int>> child_trees(graph[i].size() - 1 + (prev == -1));
    int j = 0;
    int maxSize = 0;
    int hostIndex = 0;
    vector<int> len_delta(child_trees.size());
    vector<int> num_delta(child_trees.size());
    for (auto x : graph[i]) {
        if (x.dest == prev) {
            continue;
        }
        auto y = dfs_go(x.dest, i, child_trees[j]);
        len_delta[j] = y.first + x.len;
        num_delta[j] = y.second + 1;
        if (child_trees[j].size() >= maxSize) {
            hostIndex = j;
        }
        ++j;
    }
    if (child_trees.size() == 0) {
        dest[0] = 0;
        dp[i] = INF;
        return {0, 0};
    }
    child_trees[hostIndex][-len_delta[hostIndex]] = -num_delta[hostIndex];
//    cout << "Processing i = " << i << "\n";
//    cout << "hostIndex = " << hostIndex << "\n";
    int best = INF;
    if (child_trees[hostIndex].find(K - len_delta[hostIndex]) != child_trees[hostIndex].end()) {
        best = child_trees[hostIndex][K - len_delta[hostIndex]] + num_delta[hostIndex];
    }
    for (int j = 0; j != child_trees.size(); ++j) {
        if (j == hostIndex) {
            continue;
        }
        for (auto x : child_trees[j]) {
            int len = x.first + len_delta[j];
            int num = x.second + num_delta[j];
//            cout << "Considering (len, num) = (" << len << ", " << num << ")\n";
            auto iter = child_trees[hostIndex].find(K - len - len_delta[hostIndex]);
            if (iter != child_trees[hostIndex].end()) {
                int val = iter->second + num + num_delta[hostIndex];
                if (val < best) {
                    best = val;
                }
            }
        }
        for (auto x : child_trees[j]) {
            if (child_trees[hostIndex].find(x.first + len_delta[j] - len_delta[hostIndex]) == child_trees[hostIndex].end()) {
                child_trees[hostIndex][x.first + len_delta[j] - len_delta[hostIndex]] = x.second + num_delta[j] - num_delta[hostIndex];
            } else {
                child_trees[hostIndex][x.first + len_delta[j] - len_delta[hostIndex]] = min(
                    child_trees[hostIndex][x.first + len_delta[j] - len_delta[hostIndex]],
                    x.second + num_delta[j] - num_delta[hostIndex]
                );
            }
        }
    }
    swap(dest, child_trees[hostIndex]);
//    cout << i << ": {";
//    for (auto x : dest) {
//        cout << "(" << x.first + len_delta[hostIndex] << ", " << x.second + num_delta[hostIndex] << "), ";
//    }
//    cout << "}\n";
    dp[i] = best;
    return {len_delta[hostIndex], num_delta[hostIndex]};
}

int main() {
    cin >> N >> K;
    graph = vector<vector<edge>>(N);
    for (int i = 1; i != N; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        graph[x].push_back({y, z});
        graph[y].push_back({x, z});
    }

    dp = vector<int>(N);
    map<int, int> dest;
    dfs_go(0, -1, dest);
    auto out = *min_element(dp.begin(), dp.end());
    if (out == INF) {
        cout << -1;
    } else {
        cout << out;
    }
}
