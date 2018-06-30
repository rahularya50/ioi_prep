#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, Q;
    cin >> N >> Q;

    vector<vector<pair<int, int>>> graph(N);

    for (int i = 0; i != N - 1; ++i) {
        int a, b, l;
        cin >> a >> b >> l;
        if (b == 1) {
            b = a;
            a = 1;
        }
        graph[a - 1].push_back({l, b - 1});
        graph[b - 1].push_back({l, a - 1});
    }

    for (int i = 0; i != Q; ++i) {
        int u, v;
        cin >> u >> v;
        vector<int> preds(N, -1);
        --u;
        --v;


    }
}

