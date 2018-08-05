#include <bits/stdc++.h>

using namespace std;

vector<int> owner;
vector<int> charging;
vector<vector<int>> graph;
vector<int> winner;

int go(int i) {
//    cout << "go(" << i << ")\n";
    bool selfLoop = false;
    int nextNode = -1;
    for (auto x : graph[i]) {
        if (x == i) {
            selfLoop = true;
        } else {
            nextNode = x;
            // x = i + 1!
        }
    }

    if (charging[i]) {
        if ((owner[i] == 1 && selfLoop) || nextNode == -1) {
            winner[i] = 1;
            return 1;
            // can force to enter selfLoop
        } else {
            // will not enter selfLoop
            winner[i] = go(nextNode);
            return winner[i];
        }
    } else {
        if ((owner[i] == 0 && selfLoop) || nextNode == -1) {
            winner[i] = 0;
            return 0;
        } else {
            winner[i] = go(nextNode);
            return winner[i];
        }
    }
}

vector<int> who_wins(vector<int> a, vector<int> r, vector<int> u, vector<int> v) {
    owner = a;
    charging = r;
    graph = vector<vector<int>>(a.size());
    for (int i = 0; i != u.size(); ++i) {
        graph[u[i]].push_back(v[i]);
    }

    vector<int> out(a.size());
    winner = vector<int>(a.size(), -1);
    for (int i = 0; i != a.size(); ++i) {
        out[i] = go(i);
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
