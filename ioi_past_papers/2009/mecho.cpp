#include <bits/stdc++.h>

using namespace std;

vector<int> latest;
vector<vector<int>> graph;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, S;
    cin >> N >> S;
//    cout << N << "\n";
    vector<char> m(N*N);
    graph = vector<vector<int>>(N*N);
    int honeypot;
    int dest;
    vector<int> hives;
    for (int i = 0; i != N; ++i) {
        for (int j = 0; j != N; ++j) {
            char x;
            cin >> x;
            if (x == 'M') {
                honeypot = i*N + j;
                x = 'G';
            }
            if (x == 'H') {
                hives.push_back(i*N + j);
                x = 'G';
            }
            if (x == 'D') {
                dest = i*N + j;
                x = 'G';
            }
            m[i * N + j] = x;
        }
    }

//    cout << "input processed\n";

    for (int i = 0; i != N; ++i) {
        for (int j = 0; j != N; ++j) {
            if (m[i*N+j] == 'G') {
                if (j != 0 && m[i*N + j - 1] == 'G') {
                    graph[i*N+j].push_back(i*N + j - 1);
                }
                if (j != N - 1 && m[i*N + j + 1] == 'G') {
                    graph[i*N+j].push_back(i*N + j + 1);
                }
                if (i != 0 && m[i*N - N + j] == 'G') {
                    graph[i*N+j].push_back(i*N - N + j);
                }
                if (i != N - 1 && m[i*N + N + j] == 'G') {
                    graph[i*N+j].push_back(i*N + N + j);
                }
            }
        }
    }

//    cout << "graph modeled\n";

    latest = vector<int>(N*N, -1);
    deque<pair<int, int>> todo; // {-latest, node}
    for (auto x : hives) {
        todo.push_back({0, x});
    }
    while (todo.size() > 0) {
        auto x = todo.front();
        todo.pop_front();
        if (latest[x.second] != -1) {
            continue;
        }
        latest[x.second] = -x.first;
        for (auto y : graph[x.second]) {
            if (y == dest) {
                continue;
            }
            todo.push_back({-latest[x.second] - 1, y});
        }
    }

//    for (int i = 0; i != N; ++i) {
//        for (int j = 0; j != N; ++j) {
//            cout << latest[i*N + j] << ", ";
//        }
//        cout << "\n";
//    }
//
//    cout << "bees propagated\n";

    int low = -1;
    int high = N*N;
    int out;
    while (high - low > 1) {
//        cout << low << " <= d_time < " << high << "\n";
        int lim = (low + high) / 2;
        vector<int> minTimeTo(N*N, -1);
        deque<pair<int, int>> todo; // {-time, node}
        todo.push_back({-lim * S, honeypot});
        while (todo.size() > 0) {
            int t = -todo.front().first;
            int n = todo.front().second;
//            cout << n << "\n";
            todo.pop_front();
            if (minTimeTo[n] != -1) {
                continue;
            }
            minTimeTo[n] = t;
//            cout << "minTimeTo[" << (n / N) << "][" << (n % N) << "] = " << minTimeTo[n] << "\n";
            if (t / S >= latest[n] && latest[n] != -1) {
                continue;
            }
//            cout << "!\n";
            for (auto x : graph[n]) {
                todo.push_back({-t - 1, x});
            }
        }
//        cout << "dest=" << dest << "\n";
//        cout << "done\n";
        if (minTimeTo[dest] == -1) {
            high = lim;
        } else {
//            cout << "success with lim=" << lim << "\n";
//            for (int i = 0; i != N; ++i) {
//                for (int j = 0; j != N; ++j) {
//                    cout << minTimeTo[i*N + j] << ", ";
//                }
//                cout << "\n";
//            }
            low = lim;
        }
    }

    if (low == -1) {
        cout << -1;
    } else {
        cout << low;
    }
}
