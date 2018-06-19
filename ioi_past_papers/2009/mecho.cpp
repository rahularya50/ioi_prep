#include <bits/stdc++.h>

using namespace std;

vector<int> latest;
vector<vector<int>> graph;

int main() {
    int N, S;
    cin >> N >> S;
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
                x = 'G'
            }
            if (x == 'H') {
                hives.push_back(i*N + j);
                x = 'G';
            }
            if (x == 'D') {
                dest == i*N + j;
                x = 'G';
            }
            m[i * N + j] = x;
        }
    }

    for (int i = 0; i != N; ++i) {
        for (int j = 0; j != N; ++j) {
            if (m[i*N+j] == 'G') {
                if (j != 0 && m[i*N + j - 1] == 'G') {
                    graph.push_back(i*N + j - 1);
                }
                if (j != N - 1 && m[i*N + j + 1] == 'G') {
                    graph.push_back(i*N + j + 1);
                }
                if (i != 0 && m[i*N - N + j] == 'G') {
                    graph.push_back(i*N - N + j);
                }
                if (i != N - 1 && m[i*N + N + j] == 'G') {
                    graph.push_back(i*N + N + j);
                }
            }
        }
    }

    latest = vector<int>(N, -1);
    priority_queue<pair<int, int>> todo; // {-latest, node}
    for (auto x : hives) {
        latest[x] = 0;
        todo.push({0, x});
    }
    while (todo.size() > 0) {
        auto x = todo.front();
        todo.pop_front();
        if (latest[x.second] != -1) {
            continue;
        }
        latest[x.second] = -x.first;
        for (auto y : graph[x]) {
            todo.push({-latest[x.second] - 1, y});
        }
    }

    vector<int> timeneeded(N*N, -1);
    todo = {};
    for (auto x : graph[dest]) {
        timeneeded[x] = 1;
        todo.push({-timeneeded[x], x});
    }
    while (todo.size() > 0) {
        auto x = todo.front();
        todo.pop_front();
        auto pos = x.second;
        auto tn = x.first;
        if (timeneeded[pos] != -1) {
            continue;
        }
        timeneeded[pos] = tn;
    }

}
