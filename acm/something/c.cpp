#include "bits/stdc++.h"

using namespace std;

using ll = long long;
//
bool black[102];
// int dp[102][102];
//
// struct edge {
//   int len;
//   int dest;
// }
//
// // maxdist is OUTSIDE dp!!!!
// int solve(int node, int maxdist, int parlen, vector<vector<edge>>& children) {
//   // everyone must be no deeper than parlen from root
//   if (dp[node][parlen] != -1) {
//     return dp[node][parlen];
//   }
//   for (int x = 0; x != parlen; ++x) {
//
//   }
// }

int main() {
	int N, M;
  cin >> N >> M;

  if (M == 1) {
    cout << 0 << endl;
    return 0;
  }

  for (int i = 0; i != N; ++i) {
    cin >> black[i];
  }
  vector<vector<int>> graph(N);
  for (int i = 0; i != N - 1; ++i) {
    int u, v;
    cin >> u >> v;
    graph[u-1].push_back(v-1);
    graph[v-1].push_back(u-1);
  }

  vector<vector<int>> dists(N, vector<int>(N, -1));
  for (int root = 0; root != N; ++root) {
    deque<int> todo = {root};
    dists[root][root] = 0;

    while (todo.size() > 0) {
      int next = todo.front();
      todo.pop_front();
      for (auto x : graph[next]) {
        if (dists[root][x] != -1) {
          continue;
        }
        todo.push_back(x);
        dists[root][x] = dists[root][next] + 1;
      }
    }
  }

  int best = 10000000;

  for (int root = 0; root != N; ++root) {
    vector<pair<int, int>> fromRoot;
    for (int i = 0; i != N; ++i) {
      if (black[i]) {
        fromRoot.push_back({dists[root][i], i});
      }
    }
    sort(fromRoot.begin(), fromRoot.end());
    int curr = 0;
    for (int i = 0; i != M; ++i) {
      for (int j = 0; j != M; ++j) {
        curr = max(curr, dists[fromRoot[i].second][fromRoot[j].second]);
      }
    }
    best = min(curr, best);
  }

  for (int root = 0; root != N; ++root) {
    for (int dest : graph[root]) {
      vector<pair<int, int>> fromRoot;
      for (int i = 0; i != N; ++i) {
        if (black[i]) {
          fromRoot.push_back({min(dists[root][i], dists[dest][i]), i});
        }
      }
      sort(fromRoot.begin(), fromRoot.end());
      int curr = 0;
      for (int i = 0; i != M; ++i) {
        for (int j = 0; j != M; ++j) {
          curr = max(curr, dists[fromRoot[i].second][fromRoot[j].second]);
        }
      }
      best = min(curr, best);
    }
  }


  cout << best << endl;
}
