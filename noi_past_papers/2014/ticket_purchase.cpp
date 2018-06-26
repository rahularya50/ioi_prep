#include <bits/stdc++.h>

using namespace std;

struct edge {
    int dest;
    int len;
};

int main() {
    int N, T;
    cin >> N >> T;
    vector<int> parent(N, -1);
    vector<int> parent_lens(N, 0);
    vector<int> p(N, -1);
    vector<int> q(N, -1);
    vector<vector<edge>> children;
    for (int i = 1; i != N; ++i) {
        cin >> parent[i];
        --parent[i];
        cin >> parent_lens[i];
        children[parent[i]].push_back({i, parent_lens[i]});
        cin >>
    }
}
