#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<long long, long long>>> graph;
vector<long long> furthest_child;
vector<long long> d;
vector<long long> furthest_above;
vector<long long> parent;
vector<long long> parent_dist;

long long dfs(long long i) {
    if (furthest_child[i] != -1) {
        return furthest_child[i];
    }
//    cout << "dfsing " << i << "!\n";
    furthest_child[i] = 0;
    for (auto x : graph[i]) {
        if (x.first == parent[i]) {
            continue;
        }
//        cout << "dfsing A\n";
        furthest_child[i] = max(furthest_child[i], x.second + dfs(x.first));
    }
    return furthest_child[i];
}

vector<long long> lookup;
vector<pair<long long, long long>> ordering;

long long cnt = 0;

long long dfs_2(long long i) {
//    cout << "dfsing " << i << " parent = " << parent[i] << "\n";
    long long pre = cnt;
    ++cnt;
    ordering.push_back({pre, i});
    lookup[i] = ordering.size() - 1;
    for (auto x : graph[i]) {
        if (x.first == parent[i]) {
            continue;
        }
        parent[x.first] = i;
        parent_dist[x.first] = x.second;
        dfs_2(x.first);
        ordering.push_back({pre, i});
    }
}

long long dfs_3(long long i) {
//    e[i] = max(furthest_child[i], furthest_above[i]);
    for (auto x : graph[i]) {
        if (x.first == parent[i]) {
            continue;
        }
        furthest_above[x.first] = max(d[x.first], furthest_above[i]) + x.second;
//        cout << "furthest_above[" << x.first << "] = " << furthest_above[x.first] << "\n";
        dfs_3(x.first);
    }
}

int main() {
    ios::sync_with_stdio(false);
//    cin.tie(0);
    long long N, Q;
    cin >> N >> Q;
    graph = vector<vector<pair<long long, long long>>>(N);
    for (long long i = 0; i != N - 1; ++i) {
        long long a, b, l;
        cin >> a >> b >> l;
        graph[a - 1].push_back({b - 1, l});
        graph[b - 1].push_back({a - 1, l});
    }

    furthest_child = vector<long long>(N, -1);
    furthest_above = vector<long long>(N);
    parent = vector<long long>(N, -1);
    parent_dist = vector<long long>(N, -1);
    lookup = vector<long long>(N);
    dfs_2(0);
    dfs(0);

    vector<array<long long, 3>> bests(N);
    for (long long i = 0; i != N; ++i) {
        priority_queue<long long> best;
        for (auto x : graph[i]) {
            if (x.first == parent[i]) {
                continue;
            }
            best.push(furthest_child[x.first] + x.second);
        }
        for (long long j = 0; j != 3; ++j) {
            bests[i][j] = -1;
        }
        for (long long j = 0; j != 3 && best.size() != 0; ++j) {
            bests[i][j] = best.top();
            best.pop();
//            cout << "Best #" << j << " of " << i << " = " << bests[i][j] << "\n";
        }
    }

    d = vector<long long>(N);
    for (int i = 1; i != N; ++i) {
        auto x = parent_dist[i] + furthest_child[i];
        bool valid = true;
        for (int j = 0; j != 3; ++j) {
            if (valid && bests[parent[i]][j] == x) {
                valid = false;
            } else {
                d[i] = bests[parent[i]][j];
                break;
            }
        }
    }

    dfs_3(0);

    vector<vector<pair<long long, long long>>> lca_table;
    lca_table.push_back(ordering);
    vector<vector<long long>> d_table = {{}};
    for (auto x : ordering) {
//        cout << "{" << x.first << ", " << x.second + 1 << "}, ";
        d_table.back().push_back(d[x.second]);
    }
    for (long long row = 1; (1 << row) <= ordering.size(); ++row) {
        lca_table.push_back({});
        d_table.push_back({});
        long long stride = (1 << row);
        for (long long i = 0; i + stride != ordering.size(); ++i) {
            lca_table.back().push_back(min(lca_table[row - 1][i], lca_table[row - 1][i + stride / 2]));
            d_table.back().push_back(max(d_table[row - 1][i], d_table[row - 1][i + stride / 2]));
        }
    }

//    cout << "reading queries\n";

    for (long long q = 0; q != Q; ++q) {
        long long u, v;
        cin >> u >> v;
        --u;
        --v;
        long long start_index = min(lookup[u], lookup[v]);
        long long end_index = max(lookup[u], lookup[v]) + 1;
        long long row = log2(end_index - start_index);
        auto lca = min(lca_table[row][start_index], lca_table[row][end_index - (1 << row)]).second;

        long long out = 0;
        if (u != lca) {
            out = max(out, furthest_child[u]);
        }
        if (v != lca) {
            out = max(out, furthest_child[v]);
        }

//        cout << "furthest_above[" << lca << "] = " << furthest_above[lca] << "\n";
        out = max(out, furthest_above[lca]);

        array<bool, 3> valid = {true, true, true};

        for (auto e : {u, v}) {
//            cout << "e = " << e << "\n";
            long long target_pre = ordering[lookup[e]].first;
//            cout << "target_pre = " << target_pre << "\n";
            if (lca == e) {
                continue;
            }
            auto desc_1 = (*next(upper_bound(graph[lca].begin(), graph[lca].end(), target_pre, [&](long long a, pair<long long, long long> b) { return a < ordering[lookup[b.first]].first; }), -1));
//            cout << "d1 = " << desc_1.first << "\n";

            for (long long p = 0; p != 3; ++p) {
                if (valid[p] && furthest_child[desc_1.first] + desc_1.second == bests[lca][p]) {
                    valid[p] = false;
                    break;
                }
            }
            if (desc_1.first == e) {
                continue;
            }
            auto desc_2 = (*next(upper_bound(graph[desc_1.first].begin(), graph[desc_1.first].end(), target_pre, [&](long long a, pair<long long, long long> b) { return a < ordering[lookup[b.first]].first; }), -1)).first;
//            cout << "d2 = " << desc_2 << "\n";

            long long start_index = min(lookup[e], lookup[desc_2]);
            long long end_index = max(lookup[e], lookup[desc_2]) + 1;
            long long row = log2(end_index - start_index);
            out = max(out, max(d_table[row][start_index], d_table[row][end_index - (1 << row)]));
        }

        long long p;
        for (long long i = 0; i != 3; ++i) {
            if (valid[i]) {
                p = i;
                break;
            }
        }
        out = max(out, bests[lca][p]);

        cout << out << "\n";
    }
}
