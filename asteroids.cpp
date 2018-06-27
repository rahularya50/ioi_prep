#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    vector<vector<int>> graph(N + N + 2);
    for (int i = 0; i != K; ++i) {
        int R, C;
        cin >> R >> C;
        --R;
        --C;
        graph[R].push_back(N + C);
    }
    const int SOURCE = 2*N;
    const int SINK = 2*N + 1;
    for (int i = 0; i != N; ++i) {
        graph[SOURCE].push_back(i);
    }
    for (int i = N; i != 2*N; ++i) {
        graph[i].push_back(SINK);
    }
    int out = 0;
    while (true) {
        vector<int> prev(N + N + 2, -1);
        deque<pair<int, int>> todo = {{SOURCE, -1}};
        while (todo.size() > 0) {
            auto x = todo.front();
            todo.pop_front();
            if (prev[x.first] != -1) {
                continue;
            }
            prev[x.first] = x.second;
            if (x.first == SINK) {
                break;
            }
            for (auto y : graph[x.first]) {
                todo.push_back({y, x.first});
            }
        }
        if (prev[SINK] == -1) {
            break;
        }
        ++out;
//        cout << "Path found: ";
        int pos = SINK;
        while (pos != SOURCE) {
//            cout << pos << " -> ";
            graph[prev[pos]].erase(find(graph[prev[pos]].begin(), graph[prev[pos]].end(), pos));
            graph[pos].push_back(prev[pos]);
            pos = prev[pos];
        }
//        cout << "SOURCE \n";
    }

    cout << out;
}
