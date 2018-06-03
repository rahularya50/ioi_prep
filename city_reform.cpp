#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int>>> graph;
vector<int> furthest_child;

int main() {
    int N, Q;
    cin >> N >> Q;
    graph = vector<vector<pair<int, int>>>(N);
    for (int i = 0; i != N; ++i) {
        int a, b, l;
        cin >> a >> b >> l;
        graph[a - 1].push_back({b - 1, l});
        graph[b - 1].push_back({a - 1, l});
    }
    furthest_child = vector<int>(N);

}
