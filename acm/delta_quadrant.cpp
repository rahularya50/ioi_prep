#include "bits/stdc++.h"

using namespace std;

struct edge {
	int dest;
	int cost;
};

vector<vector<edge>> graph;
vector<vector<edge>> children;
vector<int> ordering;
vector<int> lookup;
vector<int> skip;
vector<edge> par_edges;

vector<int> subtree_size;
vector<int> subtree_cost;

int dp[10002][22];
vector<vector<vector<int>>> excluded;

int N, K;

bool doExcluded = true;

void dfs_skip(int pos, int next_par) {
//	cerr << pos << "\n";
//	cerr << children.size() << "\n";
	for (int i = 0; i + 1 < children[pos].size(); ++i) {
//		cerr << "i = " << i << ", x = " << children[pos][i].dest << endl;
		skip[children[pos][i].dest] = children[pos][i + 1].dest;
		dfs_skip(children[pos][i].dest, children[pos][i + 1].dest);
		subtree_size[pos] += subtree_size[children[pos][i].dest];
		subtree_cost[pos] += children[pos][i].cost + subtree_cost[children[pos][i].dest];
	}
//	cerr << "cat\n" << endl;
	if (children[pos].size() > 0) {
		skip[children[pos].back().dest] = next_par;
		dfs_skip(children[pos].back().dest, next_par);
		subtree_size[pos] += subtree_size[children[pos].back().dest];
		subtree_cost[pos] += children[pos].back().cost + subtree_cost[children[pos].back().dest];
	}
	subtree_size[pos] += 1;
//	cerr << "sub_size[" << pos << "] = " << subtree_size[pos] << "\n";
}

int do_dp(int i, int k) {
	if (i == N) {
		return 0;
	}
	if (dp[i][k] != -1) {
		return dp[i][k];
	}

	// cerr << "dping " << ordering[i] << " " << k << "\n";
	
	auto out = par_edges[ordering[i]].cost + do_dp(i + 1, k);
	dp[i][k] = out;
	// cerr << "out = " << out << "\n";
	if (k >= subtree_size[ordering[i]]) {
		// cout << "???" << endl;
//		cout << "after skip = " << skip[ordering[i]] << "\n";
		auto alternative = do_dp(lookup[skip[ordering[i]]], k - subtree_size[ordering[i]]);
		if (alternative < out) {
			// cerr << "Skipping " << ordering[i] << "\n";
			if (doExcluded) {
				if (skip[ordering[i]] == N) {
				excluded[i][k] = {};
			} else {
				excluded[i][k] = excluded[lookup[skip[ordering[i]]]][k - subtree_size[ordering[i]]];
			}
			excluded[i][k].push_back(ordering[i]);
			dp[i][k] = alternative;
//			cerr << "alternative = " << alternative << "\n";
		} else if (doExcluded && i + 1 != N) {
			excluded[i][k] = excluded[i + 1][k];
		}
	} else if (doExcluded && i + 1 != N) {
//		cout << "......" << endl;
//		cerr << excluded[i + 1].size() << endl;
		excluded[i][k] = excluded[i + 1][k];
	}
	
	
	// cerr << "returning " << i << " " << k << " " << dp[i][k] << endl;
	return dp[i][k];
}

void dfs_preorder(int i) {
	ordering.push_back(i);
	for (auto x : children[i]) {
		dfs_preorder(x.dest);
	}
}

int go(int i) {
	//dfs parents + children
	vector<int> todo = {i};
	par_edges[i] = {-1, 0};
	while (todo.size() > 0) {
		auto pos = todo.back();
		todo.pop_back();
		for (auto x : graph[pos]) {
			if (x.dest == par_edges[pos].dest) {
				continue;
			}
			par_edges[x.dest] = {pos, x.cost};
			children[pos].push_back(x);
			todo.push_back(x.dest);
		}
	}
	skip[i] = N;
	dfs_skip(i, N);
	
	// for (auto x : skip) {
	// 	cout << x << " ";
	// }
	// cout << "\n";

	ordering = {};
	dfs_preorder(i);
	
	// for (auto x : ordering) {
	// 	cout << x << " ";
	// }
	// cout << "\n";

	lookup = vector<int>(N);
	for (int i = 0; i != N; ++i) {
		lookup[ordering[i]] = i;
	}
	
	lookup.push_back(N);
	
	
	memset(dp, -1, sizeof(dp));
	do_dp(0, K);
//	cerr << do_dp(0, K) << "\n";
	return dp[0][K];
}

int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t != T; ++t) {
		cin >> N >> K;
		graph = vector<vector<edge>>(N);
		children = vector<vector<edge>>(N);
		subtree_size = vector<int>(N);
		subtree_cost = vector<int>(N);
		skip = vector<int>(N);
		excluded = vector<vector<vector<int>>>(N, vector<vector<int>>(K + 1));
		par_edges = vector<edge>(N, {-1, -1});
		for (int i = 0; i != N - 1; ++i) {
			int a, b, c;
			cin >> a >> b >> c;
			graph[a].push_back({b, c});
			graph[b].push_back({a, c});
		}
		
		auto out = go(0);
		// cout << "out = " << out << "\n";
		
		vector<int> todo = excluded[0][K];
		vector<int> also_try;
		
		while (todo.size() > 0) {
			auto next = todo.back();
			todo.pop_back();
			also_try.push_back(next);
			// cout << next << endl;
			for (auto x : children[next]) {
				todo.push_back(x.dest);
			}
		}

		doExcluded = false;
		
		for (auto also : also_try) {
			children = vector<vector<edge>>(N);
			// subtree_size = vector<int>(N);
			// subtree_cost = vector<int>(N);
			// skip = vector<int>(N);
			// excluded = vector<vector<vector<int>>>(N, vector<vector<int>>(K + 1));
			par_edges = vector<edge>(N, {-1, -1});
			// cerr << "also = " << also << "\n";
			auto trial = go(also);
			// cerr << "trial = " << trial << "\n";
			out = min(out, trial);
		}
		cout << 2 * out << "\n";

		doExcluded = true;
	}
}
