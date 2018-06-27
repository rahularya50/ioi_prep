#include <bits/stdc++.h>

using namespace std;

struct edge {
    int dest;
    int a;
    int b;
};

int main() {
    int N, M;
    cin >> N >> M;
    vector<vector<edge>> graph(N);
    for (int i = 0; i != M; ++i) {
        int x, y, a, b;
        cin >> x >> y >> a>> b;
        --x;
        --y;
        graph[x].push_back({y, a, b});
        graph[y].push_back({x, a, b});
    }
    int low = 0;
    int high = 50001;
    int best = numeric_limits<int>::max();
    while (low + 1 < high) {
//        cout << low << " <= best_a_lim < " << high << "\n";
        int a_limit = (low + high) / 2;
//        cout << "a_limit = " << a_limit << "\n";
        priority_queue<pair<int, int>> todo;
        todo.push({0, 0});
        vector<int> dist(N, -1);
        while (todo.size() > 0) {
            auto n = todo.top();
            todo.pop();
            if (dist[n.second] != -1) {
                continue;
            }
            dist[n.second] = -n.first;
            if (n.second == N - 1) {
                break;
            }
            for (auto x : graph[n.second]) {
                if (x.a > a_limit) {
                    continue;
                }
                todo.push({-max(-n.first, x.b), x.dest});
            }
        }
//        cout << "b_dist = " << dist[N - 1] << "\n";
        if (dist[N - 1] == -1) {
            low = a_limit + 1;
            continue;
        }
        best = min(best, a_limit + dist[N - 1]);
        if (dist[N - 1] < a_limit) {
            high = a_limit;
        } else {
            low = a_limit + 1;
        }
    }

    if (best == numeric_limits<int>::max()) {
        best = -1;
    }
    cout << best << "\n";
}
