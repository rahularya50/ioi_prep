#include <bits/stdc++.h>

using namespace std;

const long long MODULUS = 1e9 + 7;
const long long MAX = MODULUS;

vector<vector<pair<long long, bool>>> prod_tree;
vector<vector<int>> max_tree;

vector<int> X;
vector<int> Y;

set<int> non_ones;

int N;

void update_prod_tree(int row, int i, int x, int val) {
    int step_size = 1 << (prod_tree.size() - 1 - row);
    int start_pos = i * step_size;
    int end_pos = (i + 1) * step_size;
    int mid_pos = (start_pos + end_pos) / 2;

    if (step_size == 1) {
        prod_tree[row][i] = {val, false};
    } else {
        if (x < mid_pos) {
            update_prod_tree(row + 1, 2 * i, x, val);
        } else {
            update_prod_tree(row + 1, 2 * i + 1, x, val);
        }
        prod_tree[row][i].first = prod_tree[row + 1][2 * i].first * prod_tree[row + 1][2 * i + 1].first;
        prod_tree[row][i].second = prod_tree[row + 1][2 * i].second | prod_tree[row + 1][2 * i + 1].second;
        if (prod_tree[row][i].first > MAX) prod_tree[row][i].second = true;
        prod_tree[row][i].first %= MODULUS;
    }
}

pair<long long, bool> get_prod(int row, int i, int minX, int maxX) {
    int step_size = 1 << (prod_tree.size() - 1 - row);
    int start_pos = i * step_size;
    int end_pos = (i + 1) * step_size;
    int mid_pos = (start_pos + end_pos) / 2;

    if (minX <= start_pos && end_pos <= maxX) {
        return prod_tree[row][i];
    }

    pair<long long, bool> out = {1, false};
    if (minX < mid_pos) {
        auto x = get_prod(row + 1, 2 * i, minX, min(mid_pos, maxX));
        out.first *= x.first;
        if (out.first > MAX || x.second) {
            out.second = true;
        }
        out.first %= MODULUS;
    }
    if (maxX > mid_pos) {
        auto x = get_prod(row + 1, 2 * i + 1, max(mid_pos, minX), maxX);
        out.first *= x.first;
        if (out.first > MAX || x.second) {
            out.second = true;
        }
        out.first %= MODULUS;
    }

    return out;
}

void update_max_tree(int row, int i, int x, int val) {
    int step_size = 1 << (max_tree.size() - 1 - row);
    int start_pos = i * step_size;
    int end_pos = (i + 1) * step_size;
    int mid_pos = (start_pos + end_pos) / 2;

    if (step_size == 1) {
        max_tree[row][i] = val;
    } else {
        if (x < mid_pos) {
            update_max_tree(row + 1, 2 * i, x, val);
        } else {
            update_max_tree(row + 1, 2 * i + 1, x, val);
        }
        max_tree[row][i] = max(max_tree[row + 1][2 * i], max_tree[row + 1][2 * i + 1]);
    }
}

int get_max(int row, int i, int minX, int maxX) {
    int step_size = 1 << (max_tree.size() - 1 - row);
    int start_pos = i * step_size;
    int end_pos = (i + 1) * step_size;
    int mid_pos = (start_pos + end_pos) / 2;

    if (minX <= start_pos && end_pos <= maxX) {
//        cout << "max between " << minX << " <= x < " << maxX << " via interval [" << start_pos << ", " << end_pos << ")" << " = " << max_tree[row][i] << "\n";
        return max_tree[row][i];
    }

    int out = 0;
    if (minX < mid_pos) {
        out = max(out, get_max(row + 1, 2 * i, minX, min(mid_pos, maxX)));
    }
    if (maxX > mid_pos) {
        out = max(out, get_max(row + 1, 2 * i + 1, max(minX, mid_pos), maxX));
    }

//    cout << "max between " << minX << " <= x < " << maxX << " via interval [" << start_pos << ", " << end_pos << ")" << " = " << out << "\n";
    return out;
}

int get_out() {
    int best_max = 0;
    long long best_prod = 1;
    int best_i;
    int prev_i = N;
    non_ones.insert(0);
    long long run_prod = 1;
    for (auto iter = non_ones.rbegin(); iter != non_ones.rend(); ++iter) {
//        auto x = get_prod(0, 0, prev_i, N);
        if (run_prod > MODULUS) {
            break;
        }
        auto y = get_max(0, 0, *iter, prev_i);
        if (best_prod * y > run_prod * best_max) {
            best_max = y;
//            cout << "max between " << *iter << " <= x < " << prev_i << " = " << best_max << "\n";
            best_prod = run_prod;
            best_i = *iter;
        }
        run_prod *= X[*iter];
        prev_i = *iter;
    }
//    cout << "best_i = " << best_i << "\n";
//    cout << "best_max = " << best_max << "\n";
    int max_earnings = (get_prod(0, 0, 0, best_i + 1).first * best_max) % MODULUS;
    return max_earnings;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N;
    X = vector<int>(N);
    for (auto& x : X) {
        cin >> x;
    }
    Y = vector<int>(N);
    for (auto& x : Y) {
        cin >> x;
    }
    int rows = ((N < 10) ? log2(N) : log2(N - 1)) + 2;
    prod_tree = vector<vector<pair<long long, bool>>>(rows);
    prod_tree.back() = vector<pair<long long, bool>>(1 << (rows - 1));
    for (int i = 0; i != N; ++i) {
        prod_tree.back()[i] = {X[i], false};
    }
    for (int i = N; i != prod_tree.back().size(); ++i) {
        prod_tree.back()[i] = {1, false};
    }
    for (int row = rows - 2; row >= 0; --row) {
        prod_tree[row] = vector<pair<long long, bool>>(1 << row);
        for (int i = 0; i != (1 << row); ++i) {
            prod_tree[row][i].first = prod_tree[row + 1][2 * i].first * prod_tree[row + 1][2 * i + 1].first;
            prod_tree[row][i].second = prod_tree[row + 1][2 * i].second | prod_tree[row + 1][2 * i + 1].second;
            if (prod_tree[row][i].first > MAX) prod_tree[row][i].second = true;
            prod_tree[row][i].first %= MODULUS;
        }
    }

//    cout << "Prod tree: \n";
//    for (auto x : prod_tree) {
//        for (auto y : x) {
//            cout << "[" << y.first << ", " << y.second << "], ";
//        }
//        cout << "\n";
//    }

    max_tree = vector<vector<int>>(rows);
    max_tree.back() = vector<int>(1 << (rows - 1));
    for (int i = 0; i != N; ++i) {
        max_tree.back()[i] = Y[i];
    }
    for (int i = N; i != max_tree.back().size(); ++i) {
        max_tree.back()[i] = 1;
    }
    for (int row = rows - 2; row >= 0; --row) {
        max_tree[row] = vector<int>(1 << row);
        for (int i = 0; i != (1 << row); ++i) {
            max_tree[row][i] = max(max_tree[row + 1][2 * i], max_tree[row + 1][2 * i + 1]);
        }
    }

//    cout << "Max tree: \n";
//    for (auto x : max_tree) {
//        for (auto y : x) {
//            cout << "[" << y << "], ";
//        }
//        cout << "\n";
//    }


    for (int i = 0; i != N; ++i) {
        if (X[i] != 1) {
            non_ones.insert(i);
        }
    }

    cout << get_out() << "\n";

    int M;
    cin >> M;
    for (int i = 0; i != M; ++i) {
        int t, p, v;
        cin >> t >> p >> v;
        if (t == 1) {
            if (X[p] != 1) {
                non_ones.erase(p);
            }
            X[p] = v;
            if (v != 1) {
                non_ones.insert(p);
            }
            update_prod_tree(0, 0, p, v);
        } else {
            update_max_tree(0, 0, p, v);
        }
        cout << get_out() << "\n";
    }
}
