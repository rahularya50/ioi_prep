#include "bits/stdc++.h"

using namespace std;

using ll = long long;

ll dp_k;
ll dp_minus_1[501][501];
ll dp[501][501];
vector<ll> x;
vector<ll> t;
vector<ll> y;
vector<ll> r;

const ll UNDEF = -1;
const ll INFTY = 10000000000000000;

ll go(ll x1, ll x2, ll k) {
	if (x2 < 0) {
		// should never happen
		exit(1);
	}

	if (k < 0) {
		if (x1 <= 0 && x2 <= 0) {
			return 0;
		} else {
			return INFTY;
		}
	}

	if (x1 < 0) {
		if (x2 > 0) {
			return go(0, x2, k);
		} else {
			// x1 < 0, x2 == 0 => DONE!!!
			return 0;
		}
	}

	if (x1 == 0 && x2 == 0) {
		return 0;
	}

	if (k == dp_k && dp[x1][x2] != UNDEF) {
		return dp[x1][x2];
	}
	if (k == dp_k - 1 && dp_minus_1[x1][x2] != UNDEF) {
		return dp_minus_1[x1][x2];
	}

	ll val = go(x1, x2, k-1);
	if (y[k] <= x2) {
		val = min(val, go(x1, x2 - y[k], k - 1) + r[k]);
	}
	if (x[k] > x2) {
		val = min(val, go(x1 - (x[k] - x2), 0, k - 1) + t[k]);
	}
	val = min(val, go(x1 - x[k], x2, k - 1) + t[k]);

	dp[x1][x2] = val;
	// cout << "dp[" << x1 << "][" << x2 << "][" << k << "] = " << val << "\n";
	return val;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	ll n, s1, s2;
	cin >> n >> s1 >> s2;

	x = vector<ll>(n);
	t = vector<ll>(n);
	y = vector<ll>(n);
	r = vector<ll>(n);

	for (ll i = 0; i != n; ++i) {
		cin >> x[i] >> t[i] >> y[i] >> r[i];
	}

	memset(dp_minus_1, UNDEF, 501*501 * sizeof(ll));

	for (ll k = 0; k != n; ++k) {
		memset(dp, UNDEF, 501*501 * sizeof(ll));
		dp_k = k;
		for (ll x1 = 0; x1 <= s1; ++x1) {
			for (ll x2 = 0; x2 <= s2; ++x2) {
				go(x1, x2, k);
			}
		}
		memcpy(dp_minus_1, dp, 501*501 * sizeof(ll));
	}

	ll out = go(s1, s2, (n - 1));

	if (out >= INFTY) out = -1;

	cout << out << "\n";
}
