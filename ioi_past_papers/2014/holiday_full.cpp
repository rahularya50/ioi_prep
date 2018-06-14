#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int>>> tree;

void flip(int i, int row, int x, int val) {
    int step_size = 1 << (tree.size() - row - 1);
    int start_pos = step_size * i;
    int end_pos = step_size * (i + 1);
    int mid_pos = (start_pos + end_pos) / 2;

    if (step_size == 1) {
        tree[i][row] = {!tree[i][row], (!tree[i][row]) * val};
        return;
    }

    if (x < mid_pos) {
        activate(2 * i, row + 1, x, val);
    } else {
        activate(2 * i + 1, row + 1, x, val);
    }

    tree[i][row] = {tree[2 * i][row].first + tree[2 * i + 1][row].first,
                    tree[2 * i][row].second + tree[2 * i + 1][row].second};

    return;
}

int query(int i, int row, int k) {
    int step_size = 1 << (tree.size() - row - 1);
    int start_pos = step_size * i;
    int end_pos = step_size * (i + 1);
    int mid_pos = (start_pos + end_pos) / 2;

    if (step_size == 1) {
        return k * tree[i][row].second;
    }

    int mid_cnt = tree[2 * i + 1][row].first;
    if (mid_cnt >= k) {
        return query(2 * i + 1, row, k);
    } else {
        return tree[2 * i + 1][row].second + query(2 * i, row, k - mid_cnt);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, S, D;
    cin >> N >> S >> D;
    vector<int> A(N);
    for (int i = 0; i != N; ++i) {
        int x;
        cin >> x;
        A[i] = x;
    }

    vector<pair<int, int>> sorted_vals;
    for (int i = 0; i != N; ++i) {
        sorted_vals.push_back({i, A[i]});
    }

    sort(sorted_vals.begin(), sorted_vals.end(), [](pair<int, int> x, pair<int, int> y){ return x.second < y.second; });

    int rows = log2(sorted_vals.size() - 1) + 2;
    tree = vector<vector<pair<int, int>>>(rows);
    for (int row = 0; row != rows; ++row) {
        tree[row] = vector<pair<int, int>>(1 << row);
    }

    vector<int> right_scores(D + 1);

}
