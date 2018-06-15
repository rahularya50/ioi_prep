#include <bits/stdc++.h>

using namespace std;

struct edge {
    int dest;
    long long l;
};

bool operator==(edge a, edge b) {
    return (a.dest == b.dest) && (a.l == b.l);
}

vector<vector<edge>> graph;
vector<vector<edge>> tree;
deque<int> roots;
vector<int> root;
vector<int> parent; // NOT NECESSARILY A DFS TREE
vector<long long> max_depth;
vector<long long> max_tree_path;

long long dfs_max_depth(int i) {
    if (max_depth[i] != -1) {
        return max_depth[i];
    }
    long long best = 0;
    for (auto x : tree[i]) {
        best = max(best, x.l + dfs_max_depth(x.dest));
    }
    max_depth[i] = best;
    return best;
}

long long get_max_tree_path(int i) {
    if (max_tree_path[i] != -1) {
        return max_tree_path[i];
    }
    pair<long long, long long> top_two = {0, 0};
    for (auto x : tree[i]) {
        auto val = x.l + dfs_max_depth(x.dest);
        if (val > top_two.first) {
            top_two = {val, top_two.first};
        } else if (val > top_two.second) {
            top_two = {top_two.first, val};
        }
    }
    max_tree_path[i] = top_two.first + top_two.second;
    return max_tree_path[i];
}

long long dfs_max_depth_2(int i, int block1, int block2) {
//    cout << "dfsing " << i << " avoiding " << block1 << " and " << block2 << "\n";
    long long best = 0;
    for (auto x : graph[i]) {
        if (x.dest == block1 || x.dest == block2) {
            continue;
        }
        best = max(best, dfs_max_depth_2(x.dest, i, -1) + x.l);
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    graph = vector<vector<edge>>(N);
    for (int i = 0; i != N; ++i) {
        long long x, l;
        cin >> x >> l;
        graph[i].push_back({x - 1, l});
        graph[x - 1].push_back({i, l});
    }
    tree = vector<vector<edge>>(N);
    parent = vector<int>(N, -1);
    root = vector<int>(N);
    deque<pair<int, edge>> spares;
    for (int i = 0; i != N; ++i) {
        if (parent[i] != -1) {
            continue;
        }
//        cout << "new root: " << i << "\n";
        roots.push_back(i);
        spares.push_back({-1, {-1, -1}});
        deque<long long> todo = {i};
        while (todo.size() > 0) {
            auto x = todo.back();
//            cout << "exploring " << x << "\n";
            root[x] = roots.size() - 1;
            todo.pop_back();
            for (auto y : graph[x]) {
                if (parent[y.dest] == -1 && y.dest != i) {
                    parent[y.dest] = x;
                    tree[x].push_back(y);
                    todo.push_back(y.dest);
                } else if (parent[x] != y.dest) {
                    spares.back() = {x, y};
                }
            }
        }
        if (spares.back().first == -1) {
            cout << "err";
            return 1;
        }
    }

    max_depth = vector<long long>(N, -1);
    max_tree_path = vector<long long>(N, -1);
    vector<long long> bests(roots.size());
    for (int i = 0; i != N; ++i) {
        bests[root[i]] = max(bests[root[i]], get_max_tree_path(i));
    }

    vector<pair<int, edge>> prev(N, {-1, {-1, -1}});
    for (int i = 0; i != roots.size(); ++i) {
        auto x = spares[i];
//        cout << "considering spare from " << x.first << " to " << x.second.dest << "with l = " << x.second.l << "\n";
        deque<int> todo = {x.first};
        while (todo.size() > 0) {
            auto a = todo.back();
            todo.pop_back();
//            cout << "exploring " << a << "\n";
            if (a == x.second.dest) {
                break;
            }
            bool blockSpare = false;
            for (auto y : graph[a]) {
//                cout << y.dest;
                if (y.dest == prev[a].first) {
//                    cout << " invalid\n";
                    continue;
                }
                if (!blockSpare && a == x.first && y == x.second) {
//                    cout << " invalid ONLY\n";
                    blockSpare = true;
                    continue;
                }
//                cout << " valid\n";
                prev[y.dest] = {a, y}; // edge pointing from a to y.dest
                todo.push_back(y.dest);
            }
        }
//        cout << "pathing complete\n";
        deque<pair<int, edge>> seq;
        pair<int, edge> pos = {x.second.dest, {-1, 0}};
        while (pos.first != x.first) {
            seq.push_front(pos);
            pos = prev[pos.first];
        }
        seq.push_front(pos);
        seq.pop_back();

//        cout << "seq built\n";
////getchar();
//        for (auto x : seq) {
//            cout << x.first << " -> " << x.second.dest << " ";
//        }

        vector<long long> left_dp(seq.size());
        long long dist = 0;
        long long prev = x.second.dest;
        for (long long j = 0; j < seq.size(); ++j) {
            left_dp[j] = dist + dfs_max_depth_2(seq[j].first, prev, seq[j].second.dest);
            dist += seq[j].second.l;
            prev = seq[j].first;
        }
//
//        cout << "left dp done\n";
//        for (auto x : left_dp) {
//            cout << x << ", ";
//        }
//        cout << "\n";

        vector<long long> right_dp(seq.size());
        dist = 0;
        prev = x.first;
        for (int j = seq.size() - 1; j >= 0; --j) {
            right_dp[j] = dist + dfs_max_depth_2(seq[j].second.dest, prev, seq[j].first);
            dist += seq[j].second.l;
            prev = seq[j].second.dest;
        }

//        cout << "right dp done\n";

//        for (auto x : right_dp) {
//            cout << x << ", ";
//        }
//        cout << "\n";

        vector<long long> max_rvals(seq.size());
        long long curr = 0;
        for (int j = seq.size() - 1; j >= 0; --j) {
            curr = max(curr, right_dp[j]);
            max_rvals[j] = curr;
        }
//        set<long long> rvals(right_dp.begin(), right_dp.end());
        long long best = 0;
        for (int l = 0; l < seq.size(); ++l) {
            best = max(best, left_dp[l] + max_rvals[l]);
        }

//        cout << "comp = " << i << "\n";
//        cout << "in-tree = " << bests[i] << "\n";
//        cout << "out-tree = " << best + x.second.l << "\n";
        bests[i] = max(bests[i], best + x.second.l);
    }

    cout << accumulate(bests.begin(), bests.end(), 0LL);
}
