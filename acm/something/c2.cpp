#include "bits/stdc++.h"

using namespace std;

using ll = long long;

int dp[102][102][102];
bool black[102];

bool solve(int i, int height, int path, const vector<vector<int>>& children) {
  if (dp[i][height][path] != -1) {
    return dp[i][height][path];
  }
  int a = 0;
  if (height <= 0 && black[i]) {
    for (auto x : children[i]) {
      a += solve(x, path, path, children);
    }
  }
  int b = 0;
  for (auto x : children[i]) {
    b += solve(x, height - 1, path, children);
  }
  dp[i][height][path] = max(a, b);
  return max(a, b);
}

int main() {
	int N, M;
  cin >> N >> M;

  memset(dp, -1, 102*102*102);

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
  cerr << "OK so far" << endl;
  vector<bool> visited(N);
  vector<vector<int>> children(N);
  vector<int> todo = {0};
  visited[0] = true;

  while (todo.size() > 0) {
    int next = todo.back();
    todo.pop_back();
    for (auto x : graph[next]) {
      if (visited[x]) {
        continue;
      }
      children[next].push_back(x);
      todo.push_back(x);
      visited[x] = true;
    }
  }

  int low = 0;
  int high = N;
  while (low + 1 < high) {
    int mid = (low + high) / 2;
    int num = solve(0, 0, mid, children);
    if (num <= M) {
      low = mid;
    } else {
      high = mid;
    }
  }
  cout << low << endl;
}
