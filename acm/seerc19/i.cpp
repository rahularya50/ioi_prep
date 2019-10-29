#include "bits/stdc++.h"

using namespace std;

const int INFTY = 2e9;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	multiset<int> a;
	deque<int> b(n);

	for (int i = 0; i != n; ++i) {
		int x;
		cin >> x;
		a.insert(x);
	}
	for (auto& x : b) {
		cin >> x;
	}

	sort(b.begin(), b.end());

	for (int i = n-1; i != 0; --i) {
		// a wants to find smallest different
		int best_a;
		int minDiff = INFTY;
		int b_pos = 0;
		for (auto x : a) {
			while (b_pos != b.size()) {
				minDiff = min(minDiff, abs(x - b[b_pos]));
				if (abs(x - b[b_pos]) == minDiff) {
					best_a = x;
				}
				if (b[b_pos] < x) {
					++b_pos;
				} else {
					break;
				}
			}
		}
		a.erase(a.find(best_a));

		// b wants to find largest diff
		int diff1 = abs(*a.begin() - b.back());
		int diff2 = abs(*a.rbegin() - b.front());

		if (diff1 < diff2) {
			b.pop_front();
		} else {
			b.pop_back();
		}
	}

	cout << abs(*a.begin() - b[0]) << "\n";
}
