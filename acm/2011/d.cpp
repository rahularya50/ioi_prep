#include "bits/stdc++.h"
#define X real()
#define Y imag()
using namespace std;
typedef long long ll;
typedef complex<ll> pt;

const int MAXN = 1e6 + 10;

bool cmp(pt a, pt b) {
	return a.X == b.X? a.Y < b.Y : a.X < b.X;
}

ll cross(pt a, pt b) {
	return (conj(a)*b).Y;
}

ll ccw(pt a, pt b, pt c) {
	return cross(b-a, c-a);
}

struct tri {
	pt a, b, c;
	int i;
	bool operator<(tri o) const {
		return !cmp(a, o.a) && !cmp(o.a, a)? cmp(b, o.b) : cmp(a, o.a);
	};
	bool lower() {
		return ccw(a, b, c) < 0;
	}
};

int N, T;
vector<int> adj[MAXN];
bool vis[MAXN];
vector<int> ans;

pt read_pt() {
	ll x, y;
	scanf("%I64d%I64d", &x, &y);
	return pt(x, y);
}

void dfs(int i) {
	vis[i] = true;
	for(int j: adj[i]) {
		if(vis[j]) {
			continue;
		}
		dfs(j);
	}
	ans.push_back(i);
}

void solve() {
	scanf("%d", &N);
	vector<tri> v;
	for(int i = 1; i <= N; i++) {
		pt a = read_pt(), b = read_pt(), c = read_pt();
		v.push_back(tri{min(a, b, cmp), max(a, b, cmp), c, i});
		v.push_back(tri{min(a, c, cmp), max(a, c, cmp), b, i});
		v.push_back(tri{min(b, c, cmp), max(b, c, cmp), a, i});
		adj[i].clear();
		vis[i] = false;
	}
	ans.clear();
	sort(v.begin(), v.end());
	for(int i = 0; i+1 < v.size(); i++) {
		if(v[i].a == v[i+1].a && v[i].b == v[i+1].b) {
			if(v[i].a.X == v[i].b.X) {
				continue;
			}
			if(v[i].lower()) {
				adj[v[i].i].push_back(v[i+1].i);
			} else {
				adj[v[i+1].i].push_back(v[i].i);
			}
		}
	}
	for(int i = 1; i <= N; i++) {
		if(vis[i]) {
			continue;
		}
		dfs(i);
	}
	reverse(ans.begin(), ans.end());
	for(int x: ans) {
		printf("%d ", x);
	}
	puts("");
}

int main() {
	scanf("%d", &T);
	for(int test = 1; test <= T; test++) {
		solve();
	}
}