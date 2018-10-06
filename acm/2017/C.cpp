#include "bits/stdc++.h"

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> c(n); 
	for (auto& x : c) {
		cin >> x;
	}
	sort(c.begin(), c.end());
	auto maxval = c[n-1] + c[n-2];
	
	vector<int> greedy(maxval);
	vector<int> dp(maxval);
	for (int i = 1; i != maxval; ++i) {
		for (int j = n - 1; j >= 0; --j) {
			if (c[j] <= i) {
				greedy[i] = greedy[i - c[j]] + 1;
				break;
			}
		}
		dp[i] = numeric_limits<int>::max();
		for (auto x : c) {
			if (x > i) {
				break;
			}
			dp[i] = min(dp[i], dp[i - x] + 1);
		}
	}

	bool flag = false;
	for (int i = 0; i != maxval; ++i) {
		if (greedy[i] != dp[i]) {
			cout << "non-canonical\n";
			flag = true;
			break;
		}
	}
	if (!flag) {
		cout << "canonical\n";
	}
}