#include <bits/stdc++.h>

using namespace std;

vector<int> owner;
vector<int> charging;
vector<vector<int>> graph;
vector<vector<int>> canreach;
vector<vector<int>> canreach_nochargers;

// we need to find all the cycles from charging points, and mark such visited points as "win states"

int OLD_CYCLE = 1;
int WIN = 2;
int LOSE = 3;
int UNKNOWN = 0;

void dfs(int i, int origin, bool isFirst) {
//    cout << "Reached " << i << " from " << origin << "\n";
    if (canreach[origin][i] == true) {
        return;
    }
    if (!isFirst) {
        canreach[origin][i] = true;
    }
    for (auto x : graph[i]) {
        dfs(x, origin, false);
    }
}

void dfs_nochargers(int i, int origin, bool isFirst) {
//    cout << "Reached " << i << " from " << origin << "\n";
    if (charging[i]) {
        canreach_nochargers[origin][i] = false;
        return;
    }
    if (canreach_nochargers[origin][i] == true) {
        return;
    }
    if (!isFirst) {
        canreach_nochargers[origin][i] = true;
    }
    for (auto x : graph[i]) {
        dfs_nochargers(x, origin, false);
    }
}

vector<int> who_wins(vector<int> a, vector<int> r, vector<int> u, vector<int> v) {
    owner = a; // {0, 0, 0, ...}
    charging = r;
    graph = vector<vector<int>>(a.size());
    for (int i = 0; i != u.size(); ++i) {
        graph[u[i]].push_back(v[i]);
    }

    vector<int> out(a.size(), 1);
    canreach = vector<vector<int>>(a.size(), vector<int>(a.size(), false));
    canreach_nochargers = vector<vector<int>>(a.size(), vector<int>(a.size(), false));
    for (int i = 0; i != a.size(); ++i) {
        dfs(i, i, true);
        dfs_nochargers(i, i, true);
    }

//    for (int i = 0; i != a.size(); ++i) {
//        cout << i << ": {";
//        for (auto x : canreach[i]) {
//            cout << x << ", ";
//        }
//        cout << "}\n";
//    }

    vector<int> cycle_nodes;
    for (int i = 0; i != a.size(); ++i) {
        if (canreach_nochargers[i][i]) {
            cycle_nodes.push_back(i);
        }
    }

    for (int i = 0; i != a.size(); ++i) {
        for (auto x : cycle_nodes) {
            if (canreach[i][x]) {
                out[i] = 0;
            }
        }
    }

    return out;
}
//
//int main() {
//	int n, m;
//	assert(2 == scanf("%d %d", &n, &m));
//
//	vector<int> a(n), r(n), u(m), v(m);
//
//	for(int i = 0; i < n; i++)
//		assert(1 == scanf("%d", &a[i]));
//
//	for(int i = 0; i < n; i++)
//		assert(1 == scanf("%d", &r[i]));
//
//	for(int i = 0; i < m; i++)
//		assert(2 == scanf("%d %d", &u[i], &v[i]));
//
//	vector<int> res = who_wins(a, r, u, v);
//
//	for(int i = 0; i < (int)res.size(); i++)
//		printf(i ? " %d" : "%d", res[i]);
//	printf("\n");
//
//	return 0;
//}
