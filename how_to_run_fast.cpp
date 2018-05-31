#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long N, M;
    cin >> N >> M;

    vector<vector<pair<int, int>>> graph(N);
    for (int i = 0; i != M; ++i) {
        long long u, v, t;
        cin >> u >> v >> t;
        graph[u - 1].push_back({t, v - 1});
        graph[v - 1].push_back({t, u - 1});
    }

    vector<long long> num_fast(N, 0);
    vector<long long> dist(N, -1);
    vector<long long> best_in_queue(N, 0);
    vector<long long> num_in_queue(N, 0);
    num_fast[0] = 1;
    num_in_queue[0] = 1;

    using X = pair<long long, pair<long long, long long>>; // {net_dist, {origin, dest}}
    priority_queue<X, vector<X>, greater<X>> toexplore;
    toexplore.push({0, {0, 0}});
    while (toexplore.size() > 0) {
        auto a = toexplore.top();
        auto d = a.first;
        auto origin = a.second.first;
        auto dest = a.second.second;
        toexplore.pop();

        if (dist[dest] == -1 || d < dist[dest] ) {
            dist[dest] = d;
            num_fast[dest] = 0;
        }

        if (d == dist[dest]) {
//            cout << "Reading dest=" << dest << " with net_dist=" << d << " coming from " << origin << "\n";
            num_fast[dest] += num_fast[origin];
//            cout << "Setting num_fast[" << dest << "] = " << num_fast[dest] << "\n";
            if (dest == 0) {
                num_fast[dest] = 1;
            }
            --num_in_queue[dest];
            if (num_in_queue[dest] == 0) {
//                cout << "Finalizing " << dest << "\n";
                for (auto x : graph[dest]) {
                    if (num_in_queue[x.second] == 0 || d + x.first < best_in_queue[x.second]) {
                        best_in_queue[x.second] = d + x.first;
                        num_in_queue[x.second] = 1;
                        toexplore.push({d + x.first, {dest, x.second}});
                    } else if (d + x.first == best_in_queue[x.second]) {
                        ++num_in_queue[x.second];
                        toexplore.push({d + x.first, {dest, x.second}});
                    }
                }
            }

        } else {
            continue;
        }

        num_fast[dest] %= 1000000007;
    }

    for (int i = 1; i != N; ++i) {
        cout << num_fast[i] << " ";
    }

}
