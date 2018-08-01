#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int>>> graph;
vector<int> parent;
vector<int> parent_dist;
vector<int> furthest_child;
vector<int> furthest_node;

int dfs_furthest_child(int i) {
    if (furthest_child[i] != -1) {
        return furthest_child[i];
    }
    int best = 0;
    for (auto x : graph[i]) {
        if (x.first == parent[i]) {
            continue;
        }
        best = max(best, x.second + dfs_furthest_child(x.first));
    }
    furthest_child[i] = best;
    return furthest_child[i];
}

int dfs_furthest_node(int i, int pardist) {
    if (furthest_node[i] != -1) {
        return furthest_node[i];
    }
    furthest_node[i] = max(pardist, furthest_child[i]);

    int deepest_child = -1;
    int second_deepest_child = -1;
    for (auto x : graph[i]) {
        if (x.first == parent[i]) {
            continue;
        }
        if (deepest_child == -1 || parent_dist[x.first] + furthest_child[x.first] > parent_dist[deepest_child] + furthest_child[deepest_child]) {
            second_deepest_child = deepest_child;
            deepest_child = x.first;
        } else if (second_deepest_child == -1
                   || parent_dist[x.first] + furthest_child[x.first] > parent_dist[second_deepest_child] + furthest_child[second_deepest_child]) {
            second_deepest_child = x.first;
        }
    }

    for (auto x : graph[i]) {
        if (x.first == parent[i]) {
            continue;
        }
        if (x.first == deepest_child) {
            if (second_deepest_child == -1) {
                dfs_furthest_node(x.first, x.second + pardist);
            } else {
                dfs_furthest_node(x.first, x.second + max(pardist, parent_dist[second_deepest_child] + furthest_child[second_deepest_child]));
            }
        } else {
            if (deepest_child == -1) {
                dfs_furthest_node(x.first, x.second + pardist);
            } else {
                dfs_furthest_node(x.first, x.second + max(pardist, parent_dist[deepest_child] + furthest_child[deepest_child]));
            }
        }
    }

    return furthest_node[i];
}

int main() {
    int N, M, L;
    cin >> N >> M >> L;

    graph = vector<vector<pair<int, int>>>(N);

    for (int i = 0; i != M; ++i) {
        int A, B, T;
        cin >> A >> B >> T;
        graph[A].push_back({B, T});
        graph[B].push_back({A, T});
    }

    vector<int> roots(N, -1);
    vector<int> rootlist;
    parent = vector<int>(N, -1);
    parent_dist = vector<int>(N);

    for (int i = 0; i != N; ++i) {
        if (roots[i] != -1) {
            continue;
        }
        roots[i] = rootlist.size();
        rootlist.push_back(i);
        vector<int> todo = {i};
        while (todo.size() > 0) {
            auto n = todo.back();
            todo.pop_back();
            roots[n] = roots[i];
            for (auto x : graph[n]) {
                if (x.first == parent[n]) {
                    continue;
                }
                parent[x.first] = n;
                parent_dist[x.first] = x.second;
                todo.push_back(x.first);
            }
        }
    }

    furthest_child = vector<int>(N, -1);
    for (auto x : rootlist) {
        dfs_furthest_child(x);
    }

    furthest_node = vector<int>(N, -1);
    for (auto x : rootlist) {
        dfs_furthest_node(x, 0);
    }

    vector<int> furthest_subtree(rootlist.size(), numeric_limits<int>::max());
    for (int i = 0; i != N; ++i) {
        furthest_subtree[roots[i]] = min(furthest_subtree[roots[i]], furthest_node[i]);
    }
//
//    for (auto x : roots) {
//        cout << x << ", ";
//    }
//    cout << "\n";

    int center = -1;
    for (int i = 0; i != furthest_subtree.size(); ++i) {
        if (center == -1 || furthest_subtree[i] > furthest_subtree[center]) {
            center = i;
        }
    }

    int largest_node = -1;
    for (int i = 0; i != furthest_subtree.size(); ++i) {
        if (i == center) {
            continue;
        }
        if (largest_node == -1 || furthest_subtree[i] > furthest_subtree[largest_node]) {
            largest_node = i;
        }
    }

    int second_largest_node = -1;
    for (int i = 0; i != furthest_subtree.size(); ++i) {
        if (i == center || i == largest_node) {
            continue;
        }
        if (second_largest_node == -1 || furthest_subtree[i] > furthest_subtree[second_largest_node]) {
            second_largest_node = i;
        }
    }

    auto out = *max_element(furthest_node.begin(), furthest_node.end());
//    cout << out << "\n";
    if (largest_node != -1) {
        out = max(out, furthest_subtree[center] + L + furthest_subtree[largest_node]);
    }
//    cout << out << "\n";
    if (second_largest_node != -1) {
        out = max(out, furthest_subtree[second_largest_node] + 2 * L + furthest_subtree[largest_node]);
    }

    cout << out;

}
