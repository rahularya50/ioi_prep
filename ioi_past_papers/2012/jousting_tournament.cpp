#include <bits/stdc++.h>

using namespace std;

vector<vector<long long>> cnt_tree;
vector<vector<long long>> max_table;

vector<vector<long long>> graph;
vector<vector<pair<long long, long long>>> int_lookup;
vector<pair<long long, long long>> max_depth; // {{val, source}}

void zero(long long row, long long i, long long low, long long high) {
    long long step_size = 1 << (cnt_tree.size() - row - 1);
    long long start_pos = step_size * i;
    long long end_pos = step_size * (i + 1);
    long long mid_pos = (start_pos + end_pos) / 2;
    if (cnt_tree[row][i] == 0 || low <= start_pos && high >= end_pos) {
        cnt_tree[row][i] = 0;
        return;
    }
    if (low < mid_pos) {
        zero(row + 1, 2 * i, low, min(mid_pos, high));
    }
    if (high > mid_pos) {
        zero(row + 1, 2 * i + 1, max(mid_pos, low), high);
    }
    cnt_tree[row][i] = cnt_tree[row + 1][2 * i] + cnt_tree[row + 1][2 * i + 1];
}

long long lookup(long long row, long long i, long long target) {
    long long step_size = 1 << (cnt_tree.size() - row - 1);
    long long start_pos = step_size * i;
    long long end_pos = step_size * (i + 1);
    long long mid_pos = (start_pos + end_pos) / 2;
    if (target == 0) {
        return start_pos;
    }
    if (step_size == 1) {
        return end_pos;
    }
    long long mid_count = cnt_tree[row + 1][2 * i];
    if (target <= mid_count) {
        return lookup(row + 1, 2 * i, target);
    } else {
        return lookup(row + 1, 2 * i + 1, target - mid_count);
    }
}

long long max_int(long long a, long long b) {
    long long row = max_table.size() - static_cast<long long>(log2(b - a)) - 1;
    long long stride = 1 << (max_table.size() - row - 1);
    auto out = max(max_table[row][a], max_table[row][b - stride]);
    return out;
}

void build_graph(long long start_x) {
    long long root = int_lookup[start_x].back().second;
    long long x = start_x;
    long long max_x = int_lookup[start_x].back().first;
    int_lookup[start_x].pop_back();
    while (x != max_x) {
        if (int_lookup[x].size() > 0) {
            graph[root].push_back(int_lookup[x].back().second);
            long long new_x = int_lookup[x].back().first;
            build_graph(x);
            x = new_x;
        } else {
            ++x;
        }
    }
}

pair<long long, long long> get_depth(long long i) {
    pair<long long, long long> out = {1, i};
    for (auto x : graph[i]) {
        auto y = get_depth(x);
        if (y.first + 1 > out.first) {
            out = {y.first + 1, y.second};
        }
    }
    max_depth[i] = out;
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long N, C, R;
    cin >> N >> C >> R;
    vector<long long> ranks;
    ranks.reserve(N);
    for (long long i = 0; i != N - 1; ++i) {
        long long x;
        cin >> x;
        ranks.push_back(x);
    }
    vector<pair<long long, long long>> rel_rounds; // inclusive
    rel_rounds.reserve(C);
    for (long long i = 0; i != C; ++i) {
        long long s, e;
        cin >> s >> e;
        rel_rounds.push_back({s, e});
    }
    long long rows = log2(N - 1) + 2;
    cnt_tree = vector<vector<long long>>(rows);
    for (long long row = 0; row != rows; ++row) {
        cnt_tree[row] = vector<long long>(1 << row, 1 << (rows - row - 1));
    }
    vector<pair<long long, long long>> abs_rounds;
    abs_rounds.reserve(C);
    for (auto x : rel_rounds) {
        long long s = lookup(0, 0, x.first);
        long long e = lookup(0, 0, x.second + 1);
        abs_rounds.push_back({s, e});
         if (s >= N) {
            cout << "s = " << s << " >= " << N;
            return 0;
        }
         if (e > N) {
            cout << "e = " << e << " > " << N;
            return 0;
        }
        zero(0, 0, s, e - 1);
    }
    max_table = vector<vector<long long>>(rows);
    max_table.back() = vector<long long>(1 << (rows - 1), 0);
    for (long long i = 0; i != N - 1; ++i) {
        max_table.back()[i] = ranks[i];
    }
    for (long long row = rows - 2; row >= 0; --row) {
        long long stride = 1 << (rows - row - 1);
        for (long long i = 0; i + stride <= (1 << (rows - 1)); ++i) {
            max_table[row].push_back(max(max_table[row + 1][i], max_table[row + 1][i + stride / 2]));
        }
    }
    int_lookup = vector<vector<pair<long long, long long>>>(N);
    sort(abs_rounds.begin(), abs_rounds.end());
    for (long long i = 0; i != abs_rounds.size(); ++i) {
        auto x = abs_rounds[i];
        int_lookup[x.first].push_back({x.second, i});
    }
    long long root = int_lookup[0].back().second;
    max_depth = vector<pair<long long, long long>>(C);
    graph = vector<vector<long long>>(C);
    build_graph(0);
    get_depth(root);
    long long best_depth = 0;
    long long best_int = 0;
    for (long long i = 0; i != abs_rounds.size(); ++i) {
        auto x = abs_rounds[i];
        auto out = max_int(x.first, x.second - 1);
        if (out < R && max_depth[i].first > best_depth) {
            best_depth = max_depth[i].first;
            best_int = max_depth[i].second;
        }
    }
    cout << abs_rounds[best_int].first << "\n";
}
