#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> graph(N);
    for (int i = 0; i != M; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }

    vector<long long> depth(N, -1);
    vector<pair<int, int>> tovisit = {{0, 0}};
    while (tovisit.size() > 0) {
        auto a = tovisit.back().first;
        auto d = tovisit.back().second;
        tovisit.pop_back();
        if (depth[a] != -1) {
            continue;
        }
        depth[a] = d;
        for (auto x : graph[a]) {
            tovisit.push_back({x, d + 1});
        }
    }

    long long out = 1;
    for (int i = 0; i != N; ++i) {
        for (auto child : graph[i]) {
            if (depth[child] < depth[i] - 1) {
                out *= (depth[i] - depth[child] + 1);
                out %= 1000000007;
            }
        }
    }

    cout << out << "\n";
}
