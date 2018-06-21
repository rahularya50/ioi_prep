#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> graph;
vector<vector<int>> dp;
vector<int> P;

int go(int i, int j) {
    if (dp[i][j] != -1) {
        return dp[i][j];
    }
    int dest = graph[i][j];
    int out = P[dest];
    for (int k = 0; k != graph[dest].size(); ++k) {
        if (graph[dest][k] == i) {
            continue;
        }
        out += go(dest, k);
    }
    dp[i][j] = out;
    return out;
}

int main() {
    int N;
    cin >> N;
    P = vector<int>(N);
    for (auto& x : P) {
        cin >> x;
    }
    graph = vector<vector<int>>(N);
    dp = vector<vector<int>>(N);
    for (int i = 0; i != N - 1; ++i) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
        dp[x].push_back(-1);
        dp[y].push_back(-1);
    }
    int out;
    int max_cong = numeric_limits<int>::max();
    for (int i = 0; i != N; ++i) {
        int a = 0;
        for (int j = 0; j != graph[i].size(); ++j) {
            a = max(a, go(i, j));
        }
        if (a <= max_cong) {
            out = i;
            max_cong = a;
        }
    }
    cout << out;
}
