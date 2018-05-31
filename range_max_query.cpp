#include <bits/stdc++.h>

using namespace std;

int intlog(int x) {
    int out = 0;
    while (x >>= 1) {
        ++out;
    }
    return out;
}

pair<int, int> getInterval(int pos, int maxdepth) {
    int row = intlog(pos + 1);
    int delta = 1 << (maxdepth - row);
    int index = pos ? (pos - (1 << (row - 1))) : 0;
    return {delta * index, delta * (index + 1)};
}

int go(int pos, int a, int b, const vector<int>& seg_tree, int maxdepth) {
    auto interval = getInterval(pos, maxdepth);

    cout << pos << ": " << interval.first << " to " << interval.second << " = " << seg_tree[pos] << "\n";

    if (a <= interval.first && b >= interval.second) {
        return seg_tree[pos];
    }

    if (a == b) {
        return 0;
    }

    int mid = (interval.first + interval.second) / 2;

    int out = -1;

    if (a <= mid && b >= interval.first) {
        cout << "go_left" << "\n";
        out = max(out, go(pos * 2 + 1, a, b, seg_tree, maxdepth));
    }

    if (b > mid && a < interval.second) {
        cout << "go_right" << "\n";
        out = max(out, go(pos * 2 + 2, a, b, seg_tree, maxdepth));
    }

    return out;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> A;
    for (int i = 0; i != n; ++i) {
        int temp;
        cin >> temp;
        A.push_back(temp);
    }

    int targetlevel = intlog(n - 1) + 1;

    int target_n = 1 << targetlevel;

    vector<int> seg_tree(2 * target_n - 1, -1);
    for (int i = 0; i != target_n; ++i) {
        seg_tree[target_n + i - 1] = (i >= n) ? -1 : A[i];
    }

    for (int row = targetlevel - 1; row >= 0; --row) {
        for (int i = 0; i != 1 << row; ++i) {
            int pos = (1 << row) + i - 1;
            seg_tree[pos] = max(seg_tree[pos * 2 + 1], seg_tree[pos * 2 + 2]);
        }
    }

    for (auto x : seg_tree) {
        cout << x << " ";
    }
    cout << "\n";

    for (int i = 0; i != m; ++ i) {
        int a, b;
        cin >> a >> b;
        --a;
        cout << go(0, a, b, seg_tree, targetlevel) << "\n";
    }
}
