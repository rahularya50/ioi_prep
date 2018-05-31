#include <bits/stdc++.h>

using namespace std;

struct node {
    int best_left;
    int best_right;
    int best;
    int sum;
};

int log2(int N) {
    int out = 1;
    while (N >>= 1) {
        ++out;
    }
//    cout << "log 2 = " << out << "\n";
    return out;
}

int main() {
    int N, Q;
    cin >> N >> Q;

    vector<vector<node>> segment_tree(log2(N) + 1);
    segment_tree.back() = vector<node>(1 << log2(N));
    for (int i = 0; i != N; ++i) {
        int A;
        cin >> A;
        segment_tree.back()[i] = {max(0, A), max(0, A), max(0, A), A};
        auto node = segment_tree.back()[i];
//        cout << "(" << node.best_left << " " << node.best_right << " " << node.best << " " << node.sum << "), ";
    }

//    cout << "\n";

    for (int row = log2(N) - 1; row >= 0; --row) {
        for (int i = 0; i != (1 << row); ++i) {
            auto a = segment_tree[row + 1][2 * i];
            auto b = segment_tree[row + 1][2 * i + 1];
            segment_tree[row].push_back({
                                        max(a.best_left, a.sum + b.best_left),
                                        max(b.best_right, b.sum + a.best_right),
                                        max({a.best, b.best, a.best_right + b.best_left}),
                                        a.sum + b.sum
                                    });
//            auto node = segment_tree[row].back();
//            cout << "(" << node.best_left << " " << node.best_right << " " << node.best << " " << node.sum << "), ";
        }
//        cout << "\n";
    }

    cout << segment_tree.front().front().best << "\n";

    for (int i = 0; i != Q; ++i) {
        int x, k;
        cin >> x >> k;
        --x;
        segment_tree[log2(N)][x] = {max(0, k), max(0, k), max(0, k), k};
//        auto node = segment_tree[log2(N)][x];
//        cout << "(" << node.best_left << " " << node.best_right << " " << node.best << " " << node.sum << "), ";

        for (int row = log2(N) - 1; row >= 0; --row) {
            x /= 2;
            auto a = segment_tree[row + 1][2 * x];
            auto b = segment_tree[row + 1][2 * x + 1];
            segment_tree[row][x] = {max(a.best_left, a.sum + b.best_left),
                                    max(b.best_right, b.sum + a.best_right),
                                    max({a.best, b.best, a.best_right + b.best_left}),
                                    a.sum + b.sum};
//            auto node = segment_tree[row][x];
//            cout << "(" << node.best_left << " " << node.best_right << " " << node.best << " " << node.sum << "), ";

        }

        cout << segment_tree.front().front().best << "\n";
    }
}
