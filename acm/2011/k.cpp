#include "bits/stdc++.h"

using namespace std;

long long dp[1500][30];

long long go(long long N, long long h) {
	if (h < 0) {
		return 0;
	}
	if (N < 0) {
		return 0;
	}
	if (h == 0) {
		return (N == 0);
	}
	if (N == 0) {
		return (h == 0);
	}

	if (dp[N][h] != -1) {
		return dp[N][h];
	}
	long long h1, h2;
	h1 = h - 1;
	h2 = h - 2;
	long long out = 0;
	for (long long left = 0; left <= N - 1; ++left) {
		auto delta = go(left, h1) * go(N - left - 1, h2)
					 + go(left, h2) * go(N - left - 1, h1)
					 + go(left, h1) * go(N - left - 1, h1);
		out += delta;
		out %= 1000000000;
	}
	dp[N][h] = out % 1000000000;
	if (dp[N][h] < 0) {
		cout << "dp[" << N << "][" << h << "] = " << out << "\n";
	}
	return dp[N][h];
}

int main() {
	memset(dp, -1, sizeof(dp));
	long long N;
	while (cin >> N) {
		long long out = 0;
		bool nonzero = false;
		for (long long h = 0; h != 30; ++h) {
			auto val = go(N, h);
			if (val != 0) {
				nonzero = true;
			}
			if (nonzero && val == 0) {
				break;
			}
			out += val;
		}
		printf("%09lld\n", out % 1000000000);
	}
}