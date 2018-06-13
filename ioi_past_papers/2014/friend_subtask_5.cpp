#include <bits/stdc++.h>

using namespace std;

int main() {
    long long N;
    cin >> N;
    vector<long long> confidence(N);
    for (long long i = 0; i != N; ++i) {
        long long x;
        cin >> x;
        confidence[i] = x;
    }
    vector<vector<long long>> graph(N);
    vector<bool> isSource(N, true);
    for (long long i = 0; i != N - 1; ++i) {
        long long host, protocol;
        long long next = i + 1;
        cin >> host >> protocol;
        if (protocol == 0) {
            isSource[next] = !isSource[host];
            graph[host].push_back(next);
            graph[next].push_back(host);
        } else {
            isSource[next] = isSource[host];
            for (auto x : graph[host]) {
                graph[next].push_back(x);
                graph[x].push_back(next);
            }
        }
    }

    const long long ROOT = N;
    const long long DEST = N + 1;

    vector<vector<long long>> residuals(N + 2);

    for (long long i = 0; i != N; ++i) {
        if (isSource[i]) {
            residuals[ROOT].push_back(i);
        } else {
            residuals[i].push_back(DEST);
        }
    }

    for (int i = 0; i != N; ++i) {
        if (!isSource[i]) {
            continue;
        }
        residuals[i] = graph[i];
    }

//    for (int i = 0; i <= DEST; ++i) {
//        cout << i << ": {";
//        for (auto x : residuals[i]) {
//            cout << x << ", ";
//        }
//        cout << "}\n";
//    }

    long long curr = 0;
    while (true) {
        // bfs from root to dest
//        cout << "new bfs\n";
        deque<long long> todo = {ROOT};
        vector<long long> prev(N + 2, -1);
        while (todo.size() > 0) {
            auto n = todo.front();
            todo.pop_front();
//            cout << "exploring " << n << "\n";
            if (n == DEST) {
                break;
            }
            for (auto x : residuals[n]) {
//                cout << n << " -> " << x << "\n";
                if (prev[x] == -1) {
                    prev[x] = n;
                    todo.push_back(x);
                }
            }
        }
        if (prev[DEST] == -1) {
            // fail
            break;
        }
        ++curr;
        auto x = DEST;
        while (x != ROOT) {
//            cout << x << "\n";
            residuals[x].push_back(prev[x]);
            residuals[prev[x]].erase(std::remove(residuals[prev[x]].begin(), residuals[prev[x]].end(), x), residuals[prev[x]].end());
            x = prev[x];
        }
    }
    cout << N - curr << "\n";
}

