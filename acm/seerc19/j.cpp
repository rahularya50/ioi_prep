#include "bits/stdc++.h"

using namespace std;

long long graph[1001][1001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	long long n;
  cin >> n;

  for (long long i = 0; i != n * (n - 1) / 2; ++i) {
    long long u, v, w;
    cin >> u >> v >> w;
    --u; --v;
    graph[u][v] = w;
    graph[v][u] = w;
  }

  long long minCost = 0;
  for (long long i = 0; i != n; ++i) {
    vector<long long> edges;
    for (long long j = 0; j != n; ++j) {
      if (i == j) continue;
      edges.push_back(graph[j][i]);
    }
    sort(edges.begin(), edges.end());
    for (long long i = 0; i != n - 1; i += 2) {
      minCost += edges[i + 1];
    }
  }

  cout << minCost << "\n";
}
