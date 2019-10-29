#include "bits/stdc++.h"

using namespace std;

const int UNDEF = 0;
const int CURR = 1;
const int NEXT = 2;

struct edge {
	int dest;
	int srcIndex;
	int destIndex;
};

vector<vector<edge>> graph;
vector<edge> edges;

bool go(int node, int prev, vector<vector<int>>& dp) {
	if (dp[node][prev] != UNDEF) {
		return dp[node][prev];
	}
	// NEXT is next to play
	for (auto v : graph[node]) {
		if (v.destIndex == prev) {
			continue;
		}
		if (go(v.dest, v.srcIndex, dp) == CURR) {
			dp[node][prev] = NEXT;
			return NEXT;
		}
	}
	dp[node][prev] = CURR;
	return CURR;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N;
	cin >> N;
	graph = vector<vector<edge>>(N);
	for (int i = 0; i != N - 1; ++i) {
		int u, v;
		cin >> u >> v;
		--u; --v;
		graph[u].push_back({v, (int) graph[u].size(),(int) graph[v].size()});
		graph[v].push_back({u, (int) graph[v].size(),(int) graph[u].size() - 1});
	}

	vector<vector<int>> dp(N);
	for (int i = 0; i != N; ++i) {
		dp[i] = vector<int>(graph[i].size() + 1);
	}

	for (int i = 0; i != N; ++i) {
		if (go(i, N, dp) == CURR) {
			cout << "Alice" << endl;
			cout << "start at " << i << "\n";
			return 0;
		}
	}
	cout << "Bob" << endl;
}
