#include <bits/stdc++.h>

using namespace std;

struct segment {
	int sell_down;
	int sell_up;

	int buy_down;
	int buy_up;

	int best_up;
	int best_down;

	int travel_cost;

	int top;
};

struct smallseg {
	int sell;
	int buy;
	int best;
};

struct edge {
	int dest;
	int cost;
};

smallseg get_best(vector<smallseg>& segs, int s, int t) {
	if (s + 1 == t) {
		return segs[s];
	}
	int mid = (s + t) / 2;
	auto a = get_best(segs, s, mid);
	auto b = get_best(segs, mid, t);

	auto buy = min(a.buy, b.buy);
	auto sell = max(a.sell, b.sell);
	auto best = max(a.best, b.best);
	best = max(best, b.sell - a.buy);
	return {sell, buy, best};
}

int main() {
    ifstream fin("trader.in");
    ofstream fout("trader.out");

	int N;
	fin >> N;

	vector<int> p(N);
	for (auto& x : p) {
		fin >> x;
	}


	vector<vector<edge>> graph(N);
	for (int i = 0; i != N - 1; ++i) {
		int a, b, c;
		fin >> a >> b >> c;
		--a;
		--b;
		cout << a << " " << b << " " << c << "\n";
		graph[a].push_back({b, c});
		graph[b].push_back({a, c});
	}

	vector<int> todo = {0};
	vector<int> parent(N, -1);
	vector<int> parent_cost(N);
	vector<int> depth(N);
	vector<int> order;
	while (todo.size() > 0) {
		auto n = todo.back();
		order.push_back(n);
		todo.pop_back();
		for (auto x : graph[n]) {
			if (parent[x.dest] != -1 || x.dest == 0) {
				continue;
			}
			parent[x.dest] = n;
			depth[x.dest] = 1 + depth[n];
			cout << "parent[" << x.dest << "] = " << n << "\n";
			parent_cost[x.dest] = x.cost;
			todo.push_back(x.dest);
		}
	}

	vector<vector<segment>> lookups(N);
	for (auto i : order) {
		lookups[i].push_back({p[i], p[i], p[i], p[i], 0, 0, 0, parent[i]});
		int above = parent[i];
		int loglen = 1; // len = 2
		cout << "doing node i = " << i << "\n";
		while (above != -1) {
			//cout << "stealing from node a = " << above << "node = " << i << " parent = " << parent[i] << "\n";
			if ((loglen - 1) >= lookups[above].size()) {
				break;
			}
			auto x = lookups[above][loglen - 1];
			lookups[i].push_back({});
			lookups[i].back().buy_up = min(x.buy_up, p[i] - x.travel_cost - parent_cost[i]);
			lookups[i].back().buy_down = min(p[i], x.buy_down + parent_cost[i]);
			lookups[i].back().sell_down = max(x.sell_down, p[i] - x.travel_cost - parent_cost[i]);
			lookups[i].back().sell_up = max(p[i], x.sell_up + parent_cost[i]);
			lookups[i].back().best_up = max(x.best_up, x.sell_up - p[i] - parent_cost[i]);
			lookups[i].back().best_down = max(x.best_down, p[i] - x.buy_down - parent_cost[i]);
			lookups[i].back().travel_cost = x.travel_cost + parent_cost[i];
			lookups[i].back().top = x.top;
			above = x.top;
			++loglen;
		}
	}

	for (int i = 0; i != N; ++i) {
		cout << i << "\n";
		for (auto x : lookups[i]) {
			cout << "buy_up = " << x.buy_up << ", ";
			cout << "buy_down = " << x.buy_down << ", ";
			cout << "sell_down = " << x.sell_down << ", ";
			cout << "sell_up = " << x.sell_up << ", ";
			cout << "best_up = " << x.best_up << ", ";
			cout << "best_down = " << x.best_down << ", ";
			cout << "travel_cost = " << x.travel_cost << ", ";
			cout << "top = " << x.top << ", ";
		}
		cout << "\n";
	}

	int Q;
	fin >> Q;

	cout << "q read = " << Q << "\n";

	for (int q = 0; q != Q; ++q) {
		int u, v;
		fin >> u >> v;
		--u;
		--v;
		vector<segment> leftsegs;
		vector<segment> rightsegs;
		while (depth[u] < depth[v]) {
			rightsegs.push_back(lookups[v][(int)log2(depth[v] - depth[u])]);
			v = rightsegs.back().top;
		}
		while (depth[u] > depth[v]) {
			leftsegs.push_back(lookups[u][(int)log2(depth[u] - depth[v])]);
			u = leftsegs.back().top;
		}
		int jumpSize = log2(depth[u]);
		while (jumpSize >= 0) {
			if (lookups[u][jumpSize].top != lookups[v][jumpSize].top) {
				leftsegs.push_back(lookups[u][jumpSize]);
				rightsegs.push_back(lookups[v][jumpSize]);
				u = leftsegs.back().top;
				v = rightsegs.back().top;
			}
			--jumpSize;
		}
		vector<smallseg> segments;
		int c = (u != v);
		for (auto x : leftsegs) {
			segments.push_back({x.sell_up, x.buy_up + parent_cost[u], x.best_up});
		};
		if (u == v) {
            segments.push_back({p[u], p[u], 0});
		} else {
			segments.push_back({p[parent[u]], p[parent[u]], 0});
		}
		for (int i = rightsegs.size() - 1; i >= 0; --i) {
			segments.push_back({rightsegs[i].sell_down + parent_cost[v], rightsegs[i].buy_down, rightsegs[i].best_down});
		}
		cout << segments.size() << "\n";
		auto x = get_best(segments, 0, segments.size()).best;
		cout << "x = " << x << "\n";
		fout << x << "\n";
	}
}
