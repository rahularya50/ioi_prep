#include <bits/stdc++.h>

using namespace std;

struct phase {
    int i;
    int type;
    int h;
};

bool operator<(phase a, phase b) {
    return a.i < b.i;
}

int query(int i, int row, pair<int, int> run_vals, vector<vector<pair<int, int>>>& tree) { // tree of {a, b}. Find first point where a <= b
    int step_size = 1 << (tree.size() - row - 1);
    int start_pos = i * step_size;
    int end_pos = (i + 1) * step_size;
    int mid_pos = (start_pos + end_pos) / 2;
//    cout << "considering interval " << start_pos << " <= x < " << end_pos;
//    cout << " with run_vals = {" << run_vals.first << ", " << run_vals.second << "}\n";

    if (step_size == 1) {
        auto val = tree[row][i];
        if (run_vals.first < val.first) {
            return run_vals.first;
        } else {
            return run_vals.second;
        }
    }

    pair<int, int> mid_vals = {min(run_vals.first, tree[row + 1][2 * i + 1].first),
                              max(run_vals.second, tree[row + 1][2 * i + 1].second)};

    if (mid_vals.first <= mid_vals.second) {
        return query(2 * i + 1, row + 1, run_vals, tree);
    } else {
        return query(2 * i, row + 1, mid_vals, tree);
    }
}

void update(int i, int row, int x, pair<int, int> new_vals, vector<vector<pair<int, int>>>& tree) {
    int step_size = 1 << (tree.size() - row - 1);
    int start_pos = i * step_size;
    int end_pos = (i + 1) * step_size;
    int mid_pos = (start_pos + end_pos) / 2;

//    cout << "considering interval " << start_pos << " <= x < " << end_pos << "\n";

    if (step_size == 1) {
        tree[row][i] = new_vals;
        return;
    }

    if (x >= mid_pos) {
        update(2 * i + 1, row + 1, x, new_vals, tree);
    } else {
        update(2 * i, row + 1, x, new_vals, tree);
    }

    tree[row][i].first = min(tree[row + 1][2 * i].first, tree[row + 1][2 * i + 1].first);
    tree[row][i].second = max(tree[row + 1][2 * i].second, tree[row + 1][2 * i + 1].second);
}

const int INF = 1000000;

void print_tree(vector<vector<pair<int, int>>>& tree) {
    cout << "tree = {\n";
    for (int row = 0; row != tree.size(); ++row) {
        for (auto x : tree[row]) {
            cout << "{" << x.first << ", " << x.second << "}, ";
        }
        cout << "\n";
    }
    cout << "}\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, K;
    cin >> N >> K;
    vector<pair<int, phase>> phase_start(K);
    vector<pair<int, phase>> phase_end(K);
    for (int i = 0; i != K; ++i) {
        int o, l, r, h;
        cin >> o >> l >> r >> h;
        phase_start[i] = {l, {i, o, h}};
        phase_end[i] = {r, {i, o, h}};
    }

    sort(phase_start.begin(), phase_start.end());
    sort(phase_end.begin(), phase_end.end());

    int rows = log2(K) + 2;
    vector<vector<pair<int, int>>> tree(rows); // {min_red, max_blue}
    for (int row = 0; row != rows; ++row) {
        tree[row] = vector<pair<int, int>>(1 << row, {INF, 0});
    }

    update(0, 0, 0, {0, 0}, tree);

//    cout << "tree updated\n";

//    print_tree(tree);

    int p1 = 0;
    int p2 = 0;
    int curr = 0;
    for (int x = 0; x != N; ++x) {
        bool changed = false;
        while (p2 != phase_end.size() && phase_end[p2].first < x) {
            update(0, 0, phase_end[p2].second.i + 1, {INF, 0}, tree);
            ++p2;
            changed = true;
        }
        while (p1 != phase_start.size() && phase_start[p1].first <= x) {
            if (phase_start[p1].second.type == 1) {
                update(0, 0, phase_start[p1].second.i + 1, {INF, phase_start[p1].second.h}, tree);
            } else {
                update(0, 0, phase_start[p1].second.i + 1, {phase_start[p1].second.h, 0}, tree);
            }
            ++p1;
            changed = true;
        }
//        print_tree(tree);
        if (changed) {
            curr = query(0, 0, {INF, 0}, tree);
        }
        cout << curr << "\n";
    }
}
