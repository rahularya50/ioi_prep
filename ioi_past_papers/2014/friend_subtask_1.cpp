#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> confidence(N);
    for (int i = 0; i != N; ++i) {
        int x;
        cin >> x;
        confidence[i] = x;
    }
    vector<vector<int>> graph(N);
    for (int i = 0; i != N - 1; ++i) {
        int host, protocol;
        int next = i + 1;
        cin >> host >> protocol;
        if (protocol >= 1) {
            for (auto x : graph[host]) {
                graph[x].push_back(next);
                graph[next].push_back(x);
            }
        }
        if (protocol != 1) {
            graph[host].push_back(next);
            graph[next].push_back(host);
        }
    }
    int best = 0;
    for (int perm = 0; perm != (1 << N); ++perm) {
        bool fail = false;
        int curr = 0;
        for (int i = 0; i != N; ++i) {
            if (!(perm & (1 << i))) {
                continue;
            }
            for (auto x : graph[i]) {
                if (perm & (1 << x)) {
                    fail = true;
                    break;
                }
            }
            if (fail) {
                break;
            }
            curr += confidence[i];
        }
        if (fail) {
            continue;
        }
        best = max(curr, best);
    }
    cout << best << "\n";
}
