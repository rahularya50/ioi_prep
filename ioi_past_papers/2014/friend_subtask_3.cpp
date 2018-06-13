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
    cout << *max_element(confidence.begin(), confidence.end());
}
