#include <bits/stdc++.h>

using namespace std;

struct segment {
    int buy_up;
    int buy_down;
    int sell_up;
    int sell_down;
    int best_up;
    int best_down;
    int total_cost;
    int high;
};

struct edge {
    int dest;
    int cost;
};

struct smallseg {
	int sell;
	int buy;
	int best;
	int total_cost;
	int link_cost;
};

smallseg get_best(vector<smallseg>& segs, int s, int t) {
	if (s + 1 == t) {
		return segs[s];
	}
	int mid = (s + t) / 2;
	auto a = get_best(segs, s, mid);
	auto b = get_best(segs, mid, t);

	auto buy = max(a.buy - a.link_cost - b.total_cost, b.buy);
	auto sell = max(a.sell, b.sell - a.total_cost - a.link_cost);
	auto best = max(a.best, b.best);
	best = max(best, b.sell + a.buy - a.link_cost);
	return {sell, buy, best, a.total_cost + a.link_cost + b.total_cost, b.link_cost};
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
		graph[a].push_back({b, c});
		graph[b].push_back({a, c});
	}

	vector<int> parent(N, -1);
	vector<int> parent_cost(N);
	vector<int> depth(N);
	vector<int> todo = {0};
	todo.reserve(N);
	vector<int> ordering(N);
	int cnt = 0;
	while (todo.size() > 0) {
        auto n = todo.back();
        todo.pop_back();
        ordering[cnt] = n;
        ++cnt;
        for (auto x : graph[n]) {
            if (x.dest == 0 || parent[x.dest] != -1) continue;
            todo.push_back(x.dest);
            parent[x.dest] = n;
            parent_cost[x.dest] = x.cost;
            depth[x.dest] = depth[n] + 1;
        }
	}

	vector<vector<segment>> data(N);
    for (auto x : ordering) {
        data[x].push_back({-p[x], -p[x], p[x], p[x], 0, 0, 0, x});
        int above = parent[x];
        int loglen = 0; // log of the size of the guy we're stealing from
        while (above != -1) {
            if (loglen >= data[above].size()) {
                break;
            }
            auto nextseg = data[above][loglen];
            auto prevseg = data[x].back();
            segment newseg;
            newseg.buy_up = max(prevseg.buy_up - nextseg.total_cost - parent_cost[prevseg.high], nextseg.buy_up); // ok
            newseg.sell_up = max(prevseg.sell_up, nextseg.sell_up - prevseg.total_cost - parent_cost[prevseg.high]); // ok
            newseg.best_up = max({prevseg.best_up, nextseg.best_up, nextseg.sell_up + prevseg.buy_up - parent_cost[prevseg.high]}); // ok

            newseg.buy_down = max(nextseg.buy_down - parent_cost[prevseg.high] - prevseg.total_cost, prevseg.buy_down); // ok
            newseg.sell_down = max(nextseg.sell_down, prevseg.sell_down - nextseg.total_cost - parent_cost[prevseg.high]); // ok
            newseg.best_down = max({prevseg.best_down, nextseg.best_down, prevseg.sell_down + nextseg.buy_down - parent_cost[prevseg.high]}); // ok

            newseg.total_cost = prevseg.total_cost + nextseg.total_cost + parent_cost[prevseg.high];
            newseg.high = nextseg.high;

            above = parent[nextseg.high];
            data[x].push_back(newseg);
            ++loglen;
        }
    }

    int Q;
    fin >> Q;
    for (int q = 0; q != Q; ++q) {
		int u, v;
		fin >> u >> v;
		--u;
		--v;
		vector<segment> leftsegs;
		vector<segment> rightsegs;
		while (depth[u] < depth[v]) {
			rightsegs.push_back(data[v][(int)log2(depth[v] - depth[u])]);
			v = parent[rightsegs.back().high];
		}
		while (depth[u] > depth[v]) {
			leftsegs.push_back(data[u][(int)log2(depth[u] - depth[v])]);
            u = parent[leftsegs.back().high];
		}
		int jumpSize = log2(depth[u] + 1);
		while (jumpSize >= 0) {
            if (data[u].size() <= jumpSize) {
                --jumpSize;
                continue;
            }
			if (data[u][jumpSize].high != data[v][jumpSize].high) {
				leftsegs.push_back(data[u][jumpSize]);
				rightsegs.push_back(data[v][jumpSize]);
				u = parent[leftsegs.back().high];
				v = parent[rightsegs.back().high];
			}
			--jumpSize;
		}

		vector<smallseg> segments;
		for (auto x : leftsegs) {
			segments.push_back({x.sell_up, x.buy_up, x.best_up, x.total_cost, parent_cost[x.high]});
		};
		if (u == v) {
            segments.push_back({p[u], -p[u], 0, 0, 0});
		} else {
			segments.push_back({p[parent[u]], p[parent[u]], 0});
		}
		for (int i = (int)rightsegs.size() - 1; i >= 0; --i) {
            auto x = rightsegs[i];
			segments.push_back({x.sell_down, x.buy_down, x.best_down, x.total_cost, 0});
			segments[segments.size() - 2].link_cost = parent_cost[x.high];
		}
		auto x = get_best(segments, 0, segments.size()).best;
		fout << x << "\n";
	}
}

