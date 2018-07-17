#include <bits/stdc++.h>

using namespace std;

struct node {
    int cnt;
    pair<int, int> best;
};

vector<vector<node>> tree;
vector<vector<int>> table;

int find_max(int a, int b) { // a <= x < b
    int stride = (1 << (int)log2(b - a));
    int row = table.size() - (int)log2(b - a) - 1;
//    cout << "row = " << row << ", " << "stride = " << stride << "\n";
    return max(table[row][a], table[row][b - stride]);
}

int find_kth(int row, int i, int k) { // k is 0 indexed
    int step_size = 1 << (tree.size() - row - 1);
    int start_pos = step_size * i;
    int end_pos = step_size * (i + 1);
    int mid_pos = (start_pos + end_pos) / 2;

    if (step_size == 1) {
//        cout << start_pos << "\n";
        return start_pos;
    }

    if (tree[row + 1][2 * i].cnt <= k) {
        return find_kth(row + 1, 2 * i + 1, k - tree[row + 1][2 * i].cnt);
    } else {
        return find_kth(row + 1, 2 * i, k);
    }
}

void zero(int row, int i, int a, int b) {
    int step_size = 1 << (tree.size() - row - 1);
    int start_pos = step_size * i;
    int end_pos = step_size * (i + 1);
    int mid_pos = (start_pos + end_pos) / 2;

    if (a <= start_pos && b >= end_pos) {
//        cout << "zeroing " << start_pos << " <= x < " << end_pos << "\n";
        tree[row][i].cnt = 0;
        return;
    }

    if (a < mid_pos) {
        zero(row + 1, 2 * i, a, min(mid_pos, b));
    }
    if (b > mid_pos) {
        zero(row + 1, 2 * i + 1, max(mid_pos, a), b);
    }

    tree[row][i].cnt = tree[row + 1][2 * i].cnt + tree[row + 1][2 * i + 1].cnt;
}

pair<int, int> find_best(int row, int i, int a, int b) {
    int step_size = 1 << (tree.size() - row - 1);
    int start_pos = step_size * i;
    int end_pos = step_size * (i + 1);
    int mid_pos = (start_pos + end_pos) / 2;

    if (a <= start_pos && b >= end_pos) {
        return tree[row][i].best;
    }

    pair<int, int> best = {0, 0};
    if (a < mid_pos) {
        best = max(best, find_best(row + 1, 2 * i, a, min(mid_pos, b)));
    }
    if (b > mid_pos) {
        best = max(best, find_best(row + 1, 2 * i + 1, max(mid_pos, a), b));
    }

    return best;
}

void set_best(int row, int i, int x, pair<int, int> val) {
    int step_size = 1 << (tree.size() - row - 1);
    int start_pos = step_size * i;
    int end_pos = step_size * (i + 1);
    int mid_pos = (start_pos + end_pos) / 2;

    if (step_size == 1) {
        tree[row][i].best = val;
        return;
    }

    if (x < mid_pos) {
        set_best(row + 1, 2 * i, x, val);
    } else {
        set_best(row + 1, 2 * i + 1, x, val);
    }

    tree[row][i].best = max(tree[row + 1][2 * i].best, tree[row + 1][2 * i + 1].best);

    return;
}

int main() {
    int N, C, R;
    cin >> N >> C >> R;
    vector<int> ranks(N - 1);
    for (auto& x : ranks) {
        cin >> x;
    }
    vector<pair<int, int>> rounds(C);
    for (auto& x : rounds) {
        cin >> x.first >> x.second;
    }

    int rows = log2(N - 1) + 2;
    table = vector<vector<int>>(rows);
    table[rows - 1] = vector<int>(1 << (rows - 1));
    for (int i = 0; i != N - 1; ++i) {
        table.back()[i] = ranks[i];
    }
    for (int i = N - 1; i != (1 << (rows - 1)); ++i) {
        table.back()[i] = 0;
    }

    for (int row = (rows - 2); row >= 0; --row) {
        int stride = 1 << (rows - row - 1);
        for (int i = 0; i + stride <= (1 << (rows - 1)); ++i) {
            table[row].push_back(max(table[row + 1][i], table[row + 1][i + stride / 2]));
        }
    }
//    for (auto x : table) {
//        for (auto y : x) {
//            cout << y << ", ";
//        }
//        cout << "\n";
//    }
    tree = vector<vector<node>>(rows);
    tree[rows - 1] = vector<node>(1 << (rows - 1));
    for (int i = 0; i != N; ++i) {
        tree[rows - 1][i] = {1, {1, -i}};
    }
    for (int i = N; i != (1 << (rows - 1)); ++i) {
        tree[rows - 1][i] = {0, {1, -i}};
    }
    for (int row = (rows - 2); row >= 0; --row) {
        tree[row] = vector<node>(1 << row);
        for (int i = 0; i != (1 << row); ++i) {
            tree[row][i].cnt = tree[row + 1][2 * i].cnt + tree[row + 1][2 * i + 1].cnt;
            tree[row][i].best = max(tree[row + 1][2 * i].best, tree[row + 1][2 * i + 1].best);
        }
    }
//    cout << "Tree: \n";
//    for (auto x : tree) {
//        for (auto y : x) {
//            cout << "{" << y.cnt << ", " << "{" << y.best.first << ", " << y.best.second << "}" << "}" << ", ";
//        }
//        cout << "\n";
//    }


    for (int i = 0; i != C; ++i) {
//        cout << rounds[i].first << "th = ";
        int leftpos = find_kth(0, 0, rounds[i].first);
//        cout << rounds[i].second << "th = ";
        int rightpos = find_kth(0, 0, rounds[i].second + 1);
        int best = find_max(leftpos, rightpos - 1);
//        cout << leftpos << " <= x < " << rightpos-1 << " -> " << best << "\n";
        if (best < R) {
            auto q = find_best(0, 0, leftpos, rightpos);
            ++q.first;
            set_best(0, 0, leftpos, q);
        }
        zero(0, 0, leftpos + 1, rightpos);
//        cout << "Tree: \n";
//        for (auto x : tree) {
//            for (auto y : x) {
//                cout << "{" << y.cnt << ", " << "{" << y.best.first << ", " << y.best.second << "}" << "}" << ", ";
//            }
//            cout << "\n";
//        }
    }

    pair<int, int> best = {0, 0};
    for (auto x : tree.back()) {
        best = max(best, x.best);
    }
    cout << -best.second << "\n";

}

