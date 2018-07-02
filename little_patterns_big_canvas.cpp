#include <bits/stdc++.h>

using namespace std;

struct edge {
    long long dest;
    long long cap;
};

long long INF = numeric_limits<int>::max();

int main() {
//    while (true) {
    long long N;
    cin >> N;
    vector<long long> p(N);
    vector<bool> parity(N);
    for (long long i = 0; i != N; ++i) {
        cin >> p[i];
        --p[i];
        if (p[i] != -1) {
            parity[i] = !parity[p[i]];
        }
    }
    vector<long long> s(N, 1);
    for (auto& x : s) {
        cin >> x;
    }
    vector<vector<edge>> graph(N + 2);
    long long SOURCE = N;
    long long SINK = N + 1;

    for (long long i = 0; i != N; ++i) {
        if (parity[i]) {
            graph[SOURCE].push_back({i, s[i]});
        } else {
            graph[i].push_back({SINK, s[i]});
        }
    }

    for (long long i = 0; i != N; ++i) {
        if (p[i] == -1) {
            continue;
        }
        if (parity[i]) {
            graph[i].push_back({p[i], INF});
        } else {
            graph[p[i]].push_back({i, INF});
        }
    }

//    for (int i = 0; i <= SINK; ++i) {
//        cout << i << " (parity = " << parity[i] << ") : ";
//        for (auto x : graph[i]) {
//            cout << "(" << x.dest << ", " << x.cap << "), ";
//        }
//        cout << "\n";
//    }

    // maxflow!!!

    long long out = 0;
    while (true) {
        vector<long long> prev(N + 2, -1);
        vector<long long> flow(N + 2, 0);
        flow[SOURCE] = INF;
        deque<long long> todo = {SOURCE};
        while (todo.size() > 0) {
            auto n = todo.front();
            todo.pop_front();
            if (n == SINK) {
                break;
            }
            for (auto x : graph[n]) {
                if (prev[x.dest] != -1 || x.dest == SOURCE) {
                    continue;
                }
                prev[x.dest] = n;
                flow[x.dest] = min(flow[n], x.cap);
                todo.push_back(x.dest);
            }
        }
        if (prev[SINK] == -1) {
            break;
        }
        out += flow[SINK];
//        while (flow[SINK] == INF) { }
        long long pos = SINK;
        while (pos != SOURCE) {
            bool flag = false;
            for (long long i = 0; i != graph[pos].size(); ++i) {
                if (graph[pos][i].dest == prev[pos]) {
                    if (graph[pos][i].cap != INF) {
                        graph[pos][i].cap += flow[SINK];
                    }
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                graph[pos].push_back({prev[pos], flow[SINK]});
            }
            for (long long i = 0; i != graph[prev[pos]].size(); ++i) {
                if (graph[prev[pos]][i].dest == pos) {
                    if (graph[prev[pos]][i].cap != INF) {
                        graph[prev[pos]][i].cap -= flow[SINK];
                        if (graph[prev[pos]][i].cap == 0) {
                            graph[prev[pos]].erase(graph[prev[pos]].begin() + i);
                        }
                    }
                    break;
                }
            }
            pos = prev[pos];
        }
    }

//    cout << "flow = " << out << "\n";

    cout << (accumulate(s.begin(), s.end(), 0LL) - out) << "\n";
//    }
}
