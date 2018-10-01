#include "bits/stdc++.h"

using namespace std;

int thing(int i, int min) {
	return i + min * 1000;
}

vector<int> weights;
unordered_map<int, bool> dp;

bool go(int i, int min, int max) {
	if (i == -1) {
		return (min <= 0 && 0 <= max);
	}

	if (max < 0) return false;

	if (dp.find(thing(i, min)) != dp.end()) {
		return dp[thing(i, min)];
	}

	if (go(i - 1, min - weights[i], max - weights[i])) {
		dp[thing(i, min)] = true;
		return true;
	}

	if (go(i - 1, min, max)) {
		dp[thing(i, min)] = true;
		return true;
	}

	dp[thing(i, min)] = false;
	return false;
}

int main() {
	int s;
	cin >> s;
	for (int i = 0; i < s; ++i) {
		int cMin, cMax, n;
		cin >> cMin >> cMax >> n;

		weights = vector<int>(n);

		for (auto& x : weights) {
			cin >> x;
		}

		dp.clear();

		cout << (go(n - 1, cMin, cMax) ? "Sallow swallow swallows." : "Sallow swallow wallows in dust.") << "\n";
	}
}