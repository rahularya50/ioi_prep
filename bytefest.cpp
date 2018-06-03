#include <bits/stdc++.h>

using namespace std;

long long N, M;

using edge = pair<pair<long long, long long>, long long>;

vector<vector<edge>> graph;
vector<edge> parent;

vector<long long> dp;

struct data {
    long long l;
    long long path;
    long long delta;
    long long node;
};

bool operator<(data x, data y) {
    return x.l < y.l;
}

int go(long long i) {
    if (dp[i] != -1) {
        return dp[i];
    }

//    cout << "Dping " << i << "\n";

    long long X = 0;

    vector<data> deltas = {{0, -1, 0}};
    for (auto n : graph[i]) {
        if (n.second == parent[i].second) {
            continue;
        }
//        cout << "Exploring branch beginning at " << n.second << "\n";
        deltas.push_back({});
        vector<pair<long long, pair<long long, long long>>> todo = {{n.second, {n.first.first, n.first.second - go(n.second)}}}; // { {node, {dist, delta}} }
        for (auto x : graph[n.second]) {
            if (x.second == parent[n.second].second) {
                continue;
            }
            todo.back().second.second += go(x.second);
        }
        X += go(n.second);
        while (todo.size() > 0) {
            auto a = todo.back();
            todo.pop_back();
            auto b = a.first;
            data x = {a.second.first, n.second, a.second.second, b};
            deltas.push_back(x);
            for (auto c : graph[b]) {
                if (c.second == parent[b].second) {
                    continue;
                }
                auto next = c.second;
                todo.push_back({next, {x.l + c.first.first, x.delta + c.first.second - go(next)}});
                for (auto d : graph[next]) {
                    if (d.second == parent[next].second) {
                        continue;
                    }
                    todo.back().second.second += go(d.second);
                }
            }
        }
    }

    sort(deltas.begin(), deltas.end());

    long long best = 0;
    long long best_other = 0;
    long long best_curr = 0;

    for (auto n : graph[i]) {
        auto curr_path = n.second;
        long long curr_i = deltas.size() - 1;
        long long other_i = 0;
        long long best_other_delta = 0;
        bool exists = false;
        for (; curr_i >= 0; --curr_i) {
            if (deltas[curr_i].path != curr_path) {
                continue;
            }
            long long best_other_sofar = 0;
            while (other_i != deltas.size() && deltas[other_i].l + deltas[curr_i].l <= M) {
//                cout << "Distance between " << i << " and " << deltas[other_i].node << " = " << deltas[other_i].l << "\n";
//                cout << "Distance between " << i << " and " << deltas[curr_i].node << " = " << deltas[curr_i].l << "\n";
                if (deltas[other_i].path != curr_path) {
                    if (deltas[other_i].delta > best_other_delta) {
                        best_other_sofar = deltas[other_i].node;
                    }
                    best_other_delta = max(best_other_delta, deltas[other_i].delta);
                }
                exists = true;
                ++other_i;
            }
            if (deltas[curr_i].delta + best_other_delta > best) {
                best_curr = deltas[curr_i].node;
                best_other = best_other_sofar;
            }
            if (exists) {
                best = max(best, deltas[curr_i].delta + best_other_delta);
            }
        }
    }

    dp[i] = X + best;
//    cout << "dp[" << i << "] = " << dp[i] << ": " << "with path from " << best_curr << " to " << best_other << "\n";
    return dp[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M;
    graph = vector<vector<edge>>(N);
    for (long long i = 0; i != N - 1; ++i) {
        long long x, y, l, h;
        cin >> x >> y >> l >> h;
        graph[x - 1].push_back({{l, h}, y - 1});
        graph[y - 1].push_back({{l, h}, x - 1});
    }
    parent = vector<edge>(N, {{0, 0}, -1});
    vector<long long> todo = {0};
    while (todo.size() > 0) {
        auto x = todo.back();
        todo.pop_back();
        for (auto y : graph[x]) {
            auto z = y.second;
            if (z == parent[x].second) {
                continue;
            }
            parent[z] = {y.first, x};
            todo.push_back(z);
        }
    }

    dp = vector<long long>(N, -1);
    cout << go(0);
}
