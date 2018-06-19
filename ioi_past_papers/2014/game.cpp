#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> counts;
vector<pair<int, int>> root; // {val, size}

int N;

void initialize(int n) {
    N = n;
    counts = vector<vector<int>>(N, vector<int>(N, 1));
    for (int i = 0; i != N; ++i) {
        counts[i][i] = 0;
    }
    root = vector<pair<int, int>>(N);
    for (int i = 0; i != N; ++i) {
        root[i] = {i, 1};
    }
}

int getRoot(int i) {
    if (root[i].first == i) {
        return i;
    }
    return getRoot(root[i].first);
}

int hasEdge(int u, int v) {
    --counts[getRoot(u)][getRoot(v)];
    if (counts[getRoot(u)][getRoot(v)] == 0) {
        // merge u, v
        int small, big;
        if (root[getRoot(u)].second < root[getRoot(v)].second) {
            small = getRoot(u);
            big = getRoot(v);
        } else {
            small = getRoot(v);
            big = getRoot(u);
        }
        root[small].first = big;
        for (int i = 0; i != N; ++i) {
            counts[big][i] += counts[small][i];
            counts[small][i] = 0;
        }
        for (int i = 0; i != N; ++i) {
            counts[i][big] += counts[i][small];
            counts[i][small] = 0;
        }
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int n;
    cin >> n;
    initialize(n);
    while (true) {
        int x, y;
        cin >> x >> y;
        cout << hasEdge(x, y) << "\n";
    }
}
