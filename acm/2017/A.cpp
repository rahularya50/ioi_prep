#include "bits/stdc++.h"

using namespace std;

struct edge {
	long long dest;
	long long cost;
};

int main() {
	long long n, m, f, s, t;
	cin >> n >> m >> f >> s >> t;

	vector<vector<edge>> graph(n);
	for (long long i = 0; i != m; ++i) {
		long long a, b, c;
		cin >> a >> b >> c;
		graph[a].push_back({b, c});
		graph[b].push_back({a, c});
	}

	vector<long long> from_S(n, -1);
	priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> todo;
	todo.push({0, s});
	while (todo.size() > 0) {
		auto n = todo.top();
		auto pos = n.second;
		auto dist = n.first;
		todo.pop();
		if (from_S[pos] != -1) {
			continue;
		}
		from_S[pos] = dist;
		for (auto x : graph[pos]) {
			todo.push({dist + x.cost, x.dest});
		}
	}

	// for (long long i = 0; i != n; ++i) {
	// 	cout << i << ": " << from_S[i] << "\n";
	// }

	vector<long long> from_T(n, -1);
	todo = priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>>();
	todo.push({0, t});
	while (todo.size() > 0) {
		auto n = todo.top();
		auto pos = n.second;
		auto dist = n.first;
		todo.pop();
		if (from_T[pos] != -1) {
			continue;
		}
		from_T[pos] = dist;
		for (auto x : graph[pos]) {
			todo.push({dist + x.cost, x.dest});
		}
	}

	// cout << "\n";

	// for (long long i = 0; i != n; ++i) {
	// 	cout << i << ": " << from_T[i] << "\n";
	// }

	vector<pair<long long, long long>> flights(f);
	for (auto& x : flights) {
		cin >> x.first >> x.second;
	}

	long long best = from_S[t];
	for (auto& x : flights) {
		if (from_S[x.first] == -1 || from_T[x.second] == -1) {
			continue;
		}
		best = min(best, from_S[x.first] + from_T[x.second]);
	}

	cout << best << "\n";
}