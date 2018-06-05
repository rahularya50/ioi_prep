#include <bits/stdc++.h>

using namespace std;

struct edge{
    long long node;
    long long weight;
};

long long N, M, L;
vector<vector<edge>> graph;
vector<long long> parent;
vector<long long> parent_dist;
vector<long long> roots;

vector<array<long long, 3>> bests;
vector<long long> furthest;

vector<long long> centroid_dist;
vector<long long> diameter;

long long dfs_furthest_child(long long r) {
    if (bests[r][0] != -1) {
        return bests[r][0];
    }

    priority_queue<long long> furthests;
    for (auto x : graph[r]) {
        if (x.node == parent[r]) {
            continue;
        }
        furthests.push(dfs_furthest_child(x.node) + x.weight);
    }

    bests[r] = {0, 0, 0};
    for (long long i = 0; i != 3 && furthests.size() != 0; ++i) {
        bests[r][i] = furthests.top();
        furthests.pop();
    }

    return bests[r][0];
}

long long dfs_furthests(long long r, long long furthest_upper) {
    if (furthest[r] != -1) {
        return furthest[r];
    }
    furthest[r] = max(bests[r][0], furthest_upper);
    for (auto x : graph[r]) {
        if (x.node == parent[r]) {
            continue;
        }
        long long furthest_child = bests[r][0];
        if (furthest_child == bests[x.node][0] + x.weight) {
            furthest_child = bests[r][1];
        }
        dfs_furthests(x.node, max(furthest_child, furthest_upper) + x.weight);
    }
}

int main() {
    cin >> N >> M >> L;

    graph = vector<vector<edge>>(N);

    for (long long i = 0; i != M; ++i) {
        long long a, b, t;
        cin >> a >> b >> t;
        graph[a].push_back({b, t});
        graph[b].push_back({a, t});
    }

    parent = vector<long long>(N, -1);
    parent_dist = vector<long long>(N);

    for (long long i = 0; i != N; ++i) {
        if (parent[i] == -1) {
            roots.push_back(i);
            vector<long long> todo = {i};
            while (todo.size() > 0) {
                long long x = todo.back();
                todo.pop_back();
                for (auto y : graph[x]) {
                    if (parent[x] == y.node) {
                        continue;
                    }
                    parent[y.node] = x;
//                    cout << "assigning parent of " << y.node << " = " << x << "\n";
                    parent_dist[y.node] = y.weight;
                    todo.push_back(y.node);
                }
            }
        }
    }

    bests = vector<array<long long, 3>>(N, {-1, -1, -1});
    for (auto r : roots) {
        dfs_furthest_child(r);
    }

    furthest = vector<long long>(N, -1);
    for (auto r : roots) {
        dfs_furthests(r, 0);
    }

//    cout << "Roots: [";
//    for (auto r : roots) {
//        cout << r << ", ";
//    }
//    cout << "]\n";
//
//    for (long long i = 0; i != N; ++i) {
//        cout << "furthest_child[" << i << "] = " << bests[i][0] << "\n";
//    }
//
//    for (long long i = 0; i != N; ++i) {
//        cout << "second_furthest_child[" << i << "] = " << bests[i][1] << "\n";
//    }
//
//    for (long long i = 0; i != N; ++i) {
//        cout << "furthest[" << i << "] = " << furthest[i] << "\n";
//    }

    centroid_dist = vector<long long>(roots.size());
    diameter = vector<long long>(roots.size());
    for (long long i = 0; i != roots.size(); ++i) {
        auto r = roots[i];
//        cout << "Exploring tree rooted at " << r << "\n";
        centroid_dist[i] = furthest[r];
        vector<long long> todo = {r};
        while (todo.size() > 0) {
            long long x = todo.back();
//            cout << "exploring " << x << "\n";
            centroid_dist[i] = min(centroid_dist[i], furthest[x]);
            diameter[i] = max(diameter[i], furthest[x]);
            todo.pop_back();
            for (auto y : graph[x]) {
                if (parent[x] == y.node) {
                    continue;
                }
                todo.push_back(y.node);
            }
        }
    }
//
//    cout << "Roots: [\n";
//    for (long long i = 0; i != roots.size(); ++i) {
//        auto r = roots[i];
//        cout << r << ", cdist = " << centroid_dist[i] << "\n";;
//    }
//    cout << "]\n";

    sort(centroid_dist.begin(), centroid_dist.end());
    sort(diameter.begin(), diameter.end());
    if (roots.size() == 1) {
        cout << diameter.back();
    } else if (roots.size() == 2) {
        cout << max(L + centroid_dist.back() + centroid_dist.front(), diameter.back());
    } else {
        long long l1 = centroid_dist[roots.size() - 1];
        long long l2 = centroid_dist[roots.size() - 2];
        long long l3 = centroid_dist[roots.size() - 3];
        cout << max(max(l1 + l2 + L, l2 + l3 + 2 * L), diameter.back());
    }
}
