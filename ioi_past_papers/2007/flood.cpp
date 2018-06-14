#include <bits/stdc++.h>

using namespace std;

struct edge {
    int i;
    int src;
    int dest;
    int angle;
};

const int UP = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;

int leftdist(int n, int o) {
    int delta = (n - o + 4) % 4;
    int out;
    switch (delta) {
    case 0:
        out = 1;
        break;
    case 1:
        out = 2;
        break;
    case 2:
        out = 3;
        break;
    case 3:
        out = 0;
    }
//    cout << o << " to " << n << " -> " << out << "\n";
    return out;
}

bool operator<(edge a, edge b) {
    if (a.i == b.i) {
        return a.src < b.src;
    }
    return a.i < b.i;
}

int main() {
    int N;
    cin >> N;
    vector<pair<int, int>> points(N);
    for (int i = 0; i != N; ++i) {
        int x, y;
        cin >> x >> y;
        points[i] = {x, y};
    }
    int W;
    cin >> W;
    vector<vector<edge>> graph(N);
    set<edge> edges;
    for (int i = 0; i != W; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;

        int adelta;
        if (points[a].first == points[b].first) {
            adelta = (points[a].second > points[b].second) * 2;
        } else {
            adelta = (points[a].first > points[b].first) * 2 + 1;
        }
        edge e1 = {i, a, b, adelta};
//        cout << a << " -> " << b << ": " << adelta << "\n";
        edge e2 = {i, b, a, (adelta + 2) % 4};

        graph[a].push_back(e1);
        graph[b].push_back(e2);
        edges.insert(e1);
        edges.insert(e2);
    }

    vector<int> component(W, -1);
    vector<bool> visited(N, false);
    int comp = 0;
    for (int i = 0; i != N; ++i) {
        if (visited[i]) {
            continue;
        }
        vector<int> todo = {i};
        while (todo.size() > 0) {
            auto a = todo.back();
            todo.pop_back();
            if (visited[a]) {
                continue;
            }
            visited[a] = true;
            for (auto x : graph[a]) {
                component[x.i] = comp;
                todo.push_back(x.dest);
            }
        }
        ++comp;
    }

    vector<int> minX(comp, 2000000);
    vector<int> l_edges(comp, -1);
    for (auto e : edges) {
        if (e.angle == UP && points[e.src].first < minX[component[e.i]]) {
            minX[component[e.i]] = points[e.src].first;
            l_edges[component[e.i]] = e.i;
        }
    }

    vector<pair<int, int>> edge_regions(W, {-1, -1});

    vector<int> out_r;
    int cnt = 0;
    while (edges.size() > 0) {
        auto a = *edges.begin();
        edges.erase(a);
        int pos = a.dest;
        int dir = a.angle;
        if (edge_regions[a.i].first == -1) {
            edge_regions[a.i].first = cnt;
        } else {
            edge_regions[a.i].second = cnt;
        }
        if (a.i == l_edges[component[a.i]] && dir == UP) {
            out_r.push_back(cnt);
        }

        while (true) {
            edge leftmost = {-1, -1, -1, 100};
            for (auto e : graph[pos]) {
                if (leftmost.angle != 100 && leftdist(e.angle, dir) == leftdist(leftmost.angle, dir)) {
                    cout << "overlapping edges\n";
                    return 1;
                }
                if (leftmost.angle == 100 || leftdist(e.angle, dir) < leftdist(leftmost.angle, dir)) {
                    leftmost = e;
                }
            }
            if (leftmost.angle == 100) {
                cout << "err\n";
                return 1;
            }
            pos = leftmost.dest;
            dir = leftmost.angle;
            if (edge_regions[leftmost.i].first == -1) {
                edge_regions[leftmost.i].first = cnt;
            } else {
                edge_regions[leftmost.i].second = cnt;
            }
            if (leftmost.i == l_edges[component[leftmost.i]] && dir == UP) {
                out_r.push_back(cnt);
            }
            if (edges.find(leftmost) == edges.end()) {
                break;
            }
            edges.erase(leftmost);
//            cout << pos << " " << dir << "\n";
        }
        ++cnt;
    }

    vector<vector<int>> r_graph(cnt);
    for (auto x : edge_regions) {
//        cout << x.first << "\n";
        r_graph[x.first].push_back(x.second);
        r_graph[x.second].push_back(x.first);
    }

//    cout << "out_r = " << out_r << "\n";

    vector<int> bfs_depth(cnt, -1);
    deque<int> todo;
    for (auto x : out_r) {
        todo.push_back(x);
        bfs_depth[x] = 0;
    }
    while (todo.size() > 0) {
        auto a = todo.front();
        todo.pop_front();
        for (auto x : r_graph[a]) {
            if (bfs_depth[x] != -1) {
                continue;
            }
            bfs_depth[x] = bfs_depth[a] + 1;
            todo.push_back(x);
        }
    }

    vector<int> out;
    for (int i = 0; i != W; ++i) {
        if (edge_regions[i].second == -1) {
            cout << "-1 : " << i << "\n";
            return 1;
        }
        if (bfs_depth[edge_regions[i].first] == bfs_depth[edge_regions[i].second]) {
            out.push_back(i + 1);
        }
    }
    cout << out.size() << "\n";
    for (auto x : out) {
        cout << x << "\n";
    }
}
