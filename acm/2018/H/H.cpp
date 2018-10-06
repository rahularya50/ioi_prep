#include "bits/stdc++.h"

using namespace std;

using ld = long double;

int main() {
	int n, p, c;
	cin >> n >> p >> c;
	cout << setprecision(10);
	// cout << 100000.005 << "\n";

	vector<pair<ld, ld>> pills(p);
	for (auto& x : pills) {
		cin >> x.first;
		int a, b;
		cin >> a >> b;
		x.second = static_cast<ld>(b) / a;
	}

	if (pills[0].first > n) {
		cout << n << "\n";
		return 0;
	}

	ld remaining = n - pills[0].first; // how many years I have left in non-scaled terms
	ld rate = 1;

	for (int i = 0; i != p; ++i) {
		// should I take this pill?
		auto curr_pill = pills[i];
		auto curr_time = curr_pill.first;
		auto new_rate = curr_pill.second;

		auto lifespan = remaining / rate;
		auto new_lifespan = (remaining - c) / new_rate;

		if (lifespan < new_lifespan) {
			remaining -= c;
			rate = new_rate;
			// cout << "Taking pill: " << i << "\n";
			lifespan = new_lifespan;
		}
	
		if (i == p - 1 || lifespan < (pills[i + 1].first - curr_time)) {
			cout << lifespan + curr_time << "\n";
			return 0;
		}

		auto next_time = pills[i + 1].first;
		remaining -= (next_time - curr_time) * rate;
	}
}