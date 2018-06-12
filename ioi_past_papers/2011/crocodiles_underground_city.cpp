#include <bits/stdc++.h>

using namespace std;

struct edge {
    int dest;
    int len;
};

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<edge>> graph(N);
    for (int i = 0; i != M; ++i) {
        int x, y, l;
        cin >> x >> y >> l;
        graph[x].push_back({y, l});
        graph[y].push_back({x, l});
    }
    vector<int> dists(N, -1);
    vector<array<int, 2>> twobests(N, {numeric_limits<int>::max(), numeric_limits<int>::max()});
    for (int i = 0; i != K; ++i) {
        int p;
        cin >> p;
        dists[p] = 0;
        for (auto x : graph[p]) {
            if (dists[x.dest] != -1) {
                continue;
            }
            if (x.len < twobests[x.dest][0]) {
                twobests[x.dest] = {x.len, twobests[x.dest][0]};
            } else if (x.len < twobests[x.dest][1]) {
                twobests[x.dest][1] = x.len;
            }
        }
    }
    priority_queue<pair<int, int>> todo;
    for (int i = 0; i != N; ++i) {
        todo.push({-twobests[i][1], i});
    }

    while (todo.size() > 0) {
        auto next = todo.top();
        todo.pop();
        if (dists[next.second] != -1) {
            continue;
        }
//        cout << "Finalizing " << next.second << "\n";
        auto sofar = -next.first;
        dists[next.second] = sofar; // next.first == twobests[next.second][1]
        for (auto x : graph[next.second]) {
            if (dists[x.dest] != -1) {
                continue;
            }
            if (sofar + x.len < twobests[x.dest][0]) {
                twobests[x.dest] = {sofar + x.len, twobests[x.dest][0]};
                todo.push({-twobests[x.dest][1], x.dest});
            } else if (sofar + x.len < twobests[x.dest][1]) {
                twobests[x.dest][1] = sofar + x.len;
                todo.push({-twobests[x.dest][1], x.dest});
            }
        }
    }

    cout << dists[0];

}
