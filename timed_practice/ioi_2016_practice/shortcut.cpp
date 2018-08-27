#include "bits/stdc++.h"

using namespace std;

struct edge {
    int dest;
    int len;
};

vector<long long> furthest_child;

long long dfs_furthest_child(int i, vector<vector<edge>>& tree) {
    cout << "Trying i = " << i << "\n";
    if (furthest_child[i] != -1) {
        return furthest_child[i];
    }
    long long out = 0;
    for (auto x : tree[i]) {
        out = max(out, x.len + dfs_furthest_child(x.dest, tree));
    }
    furthest_child[i] = out;
    cout << "furthest_child[" << i << "] = " << out << "\n";
    return out;
}

long long dfs_furthest_pair_in_subtree(int i, vector<vector<edge>>& tree) {
    long long out = 0;
    long long f_1 = -1;
    long long f_2 = -1;
    for (auto x : tree[i]) {
        out = max(out, dfs_furthest_pair_in_subtree(x.dest, tree));
        auto newlen = furthest_child[x.dest] + x.len;
        if (newlen > f_1) {
            f_2 = f_1;
            f_1 = newlen;
        } else if (newlen > f_2) {
            f_2 = newlen;
        }
    }
    if (f_2 != -1) {
        out = max(out, f_1 + f_2);
    }
    cout << "furthest_pair[" << i << "] = " << out << "\n";
    return out;
}

long long solve(vector<edge>& parent, vector<vector<edge>>& tree, vector<int>& cycle, int a, int b, int a_i, int b_i) {
    for (int i = 0; i != parent.size(); ++i) {
        cout << "parent[" << i << "] = " << parent[i].dest << "\n";
    }
    for (int i = 0; i != cycle.size(); ++i) {
        cout << "cycle[" << i << "] = " << cycle[i] << "\n";
    }
    for (int i = 0; i != tree.size(); ++i) {
        cout << "tree[" << i << "] = {";
        for (auto x : tree[i]) {
            cout << "(" << x.dest << ", " << x.len << "), ";
        }
        cout << "}\n";
    }

    cout << "preparing dfs" << "\n";
    long long out = 0;

    furthest_child = vector<long long>(parent.size(), -1);

    auto furthest_a = dfs_furthest_child(a, tree);
    auto furthest_b = dfs_furthest_child(b, tree);

    out = max(out, dfs_furthest_pair_in_subtree(a, tree));
    out = max(out, dfs_furthest_pair_in_subtree(b, tree));

    int net_dist = accumulate(cycle.begin(), cycle.end(), 0);
    auto a_to_b = accumulate(cycle.begin() + a_i, cycle.begin() + b_i, 0);
    a_to_b = min(a_to_b, net_dist - a_to_b);

    vector<int> a_right_cycle_dist(cycle.size());
    for (int i = (a + 1) % cycle.size(); i != a; i = (i + 1) % cycle.size()) {
        auto prev = (i + cycle.size() - 1) % cycle.size();
        a_right_cycle_dist[i] = a_right_cycle_dist[prev] + cycle[prev];
    }
    vector<int> a_left_cycle_dist(cycle.size());
    for (int i = (a + cycle.size() - 1) % cycle.size(); i != a; i = (i + cycle.size() - 1) % cycle.size()) {
        a_left_cycle_dist[i] = a_left_cycle_dist[i] + cycle[i];
    }

    vector<int> b_right_cycle_dist(cycle.size());
    for (int i = (b + 1) % cycle.size(); i != b; i = (i + 1) % cycle.size()) {
        auto prev = (i + cycle.size() - 1) % cycle.size();
        b_right_cycle_dist[i] = b_right_cycle_dist[prev] + cycle[prev];
    }
    vector<int> b_left_cycle_dist(cycle.size());
    for (int i = (b + cycle.size() - 1) % cycle.size(); i != b; i = (i + cycle.size() - 1) % cycle.size()) {
        b_left_cycle_dist[i] = b_left_cycle_dist[i] + cycle[i];
    }

    vector<int> a_cycle_dist(cycle.size());
    for (int i = 0; i != cycle.size(); ++i) {
        a_cycle_dist[i] = min(a_left_cycle_dist[i], a_right_cycle_dist[i]);
    }

    vector<int> b_cycle_dist(cycle.size());
    for (int i = 0; i != cycle.size(); ++i) {
        b_cycle_dist[i] = min(b_left_cycle_dist[i], b_right_cycle_dist[i]);
    }

    int furthest_from_a = *max_element(a_cycle_dist.begin(), a_cycle_dist.end());
    int furthest_from_b = *max_element(b_cycle_dist.begin(), b_cycle_dist.end());

    out = max(out, furthest_a + furthest_from_a);
    out = max(out, furthest_b + furthest_from_b);
    out = max(out, furthest_a + furthest_b + a_to_b);

    int x = 0;
    long long dist = 0;

    for (int i = 0; i != cycle.size(); ++i) {
        while (dist + cycle[x] <= net_dist / 2) {
            ++x;
            x %= cycle.size();
            dist += cycle[x];
        }
        out = max(out, dist);
        dist -= cycle[i];
    }

    cout << "furthest = " << out << "\n";

    return out;
}

long long find_shortcut(int N, vector<int> L, vector<int> D, int C) {
    cout << "Starting..." << "\n";
    cout << "Trying L -> L" << "\n";
    long long out = numeric_limits<long long>::max();
    for (int a = 0; a != N; ++a) {
        for (int b = a + 1; b != N; ++b) {
            cout << "a = " << a << ", b = " << b << "\n";
            // make edge between L[a] and L[b];
            vector<edge> parent(2*N);
            vector<vector<edge>> tree_children(2*N);
            for (int i = 0; i <= a; ++i) {
                if (i != a) {
                    parent[i] = {i + 1, L[i]};
                    tree_children[i + 1].push_back({i, L[i]});
                }
                if (D[i] != 0) {
                    parent[N + i] = {i, D[i]};
                    tree_children[i].push_back({N + i, D[i]});
                }
            }
            for (int i = b; i != N; ++i) {
                if (i != b) {
                    parent[i] = {i - 1, L[i - 1]};
                    tree_children[i - 1].push_back({i, L[i - 1]});
                }
                cout << "cat i = " << i << "D[i] = " << D[i] << "\n";
                if (D[i] != 0) {
                    parent[N + i] = {i, D[i]};
                    tree_children[i].push_back({N + i, D[i]});
                }
            }
            vector<int> cycle_lens(b - a + 1);
            for (int i = 0; i != b - a; ++i) {
                cycle_lens[i] = L[a + i];
            }
            cycle_lens.back() = C;
            out = min(solve(parent, tree_children, cycle_lens, a, b, 0, b - a), out);
        }
    }
    cout << "out = " << out << "\n";
    return out;
}

int main() {
    int n, c;
    cin >> n >> c;
    vector<int> l(n - 1);
    for (auto& x : l) {
        cin >> x;
    }
    vector<int> d(n);
    for (auto& x : d) {
        cin >> x;
    }
    cout << find_shortcut(n, l, d, c) << "\n";
}
