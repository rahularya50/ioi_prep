#include "bits/stdc++.h"

using namespace std;

using ll = long long;

void print(map<ll, ll> x) {
	for (auto y : x) {
		cout << "(" << y.first << ", " << y.second << "), ";
	}
	cout << "\n";
}

ll cap(ll x, ll low, ll high) {
	if (x < low) return low;
	if (x > high) return high;
	return x;
}

int main() {
	ll n, k, t1, t2;
	cin >> n >> k >> t1 >> t2;
	vector<ll> moments(n);
	for (auto& x : moments) {
		cin >> x;
	}
	vector<pair<ll, ll>> intervals(k);
	for (auto& x : intervals) {
		cin >> x.first >> x.second;
	}

	map<ll, ll> unsafe_intervals;
	for (auto x : moments) {
		for (auto y : intervals) {
			pair<ll, ll> unsafe_interval = {y.first - x, y.second - x};
			auto next_interval = unsafe_intervals.lower_bound(unsafe_interval.first);

			if (next_interval != unsafe_intervals.begin()) {
				auto prev_interval = next(next_interval, -1);
				if (prev_interval->second >= unsafe_interval.first) {
					unsafe_interval.first = prev_interval->first;
					unsafe_interval.second = max(unsafe_interval.second, prev_interval->second);
					unsafe_intervals.erase(prev_interval);
				}
			}

			// cout << "Inserting: (" << unsafe_interval.first << ", " << unsafe_interval.second << ")\n";

			while (true) {
				// print(unsafe_intervals);
				if (next_interval == unsafe_intervals.end()) {
					unsafe_intervals[unsafe_interval.first] = unsafe_interval.second;
					break;
				} else if (next_interval->first <= unsafe_interval.second) {
					unsafe_interval.second = max(unsafe_interval.second, next_interval->second);
					next_interval = unsafe_intervals.erase(next_interval);
				} else {
					unsafe_intervals[unsafe_interval.first] = unsafe_interval.second;
					break;
				}
			}
			// print(unsafe_intervals);
		}
	}

	long double unsafe_len = 0;
	for (auto x : unsafe_intervals) {
		unsafe_len += (cap(x.second, t1, t2) - cap(x.first, t1, t2));
		// cout << "len = " << unsafe_len << "\n";
	}

	cout << setprecision(10) << 1.0 - unsafe_len / (t2 - t1) << "\n";
}