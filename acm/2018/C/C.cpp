#include "bits/stdc++.h"

using namespace std;

int ww, wb, bw, bb, L;
map<pair<int, int>, vector<int>> w_w;
map<pair<int, int>, vector<int>> w_b;
map<pair<int, int>, vector<int>> b_w;
map<pair<int, int>, vector<int>> b_b;
vector<int> note;

bool is_black(int note) {
	int whatever = note % 12;
	if (whatever == 0 || whatever == 2 || whatever == 5 || whatever == 7 || whatever == 10)
		return true;
	return false;
}

int difficulty(int n1, int f1, int n2, int f2) {
	if (n2 < n1) {
		swap(n1, n2);
		swap(f1, f2);
	}
	if (n1 == n2) {
		return (f1 == f2) ? 0 : numeric_limits<int>::max() / 3;
	}
	bool black1 = is_black(n1);
	bool black2 = is_black(n2);
	if (!black1 && !black2) {
		if (w_w.find({f1, f2}) == w_w.end())
			return numeric_limits<int>::max() / 3;
		return w_w[{f1, f2}][n2-n1-1];
	}
	if (!black1 && black2) {
		if (w_b.find({f1, f2}) == w_b.end())
			return numeric_limits<int>::max() / 3;
		return w_b[{f1, f2}][n2-n1-1];
	}
	if (black1 && !black2) {
		if (b_w.find({f1, f2}) == b_w.end())
			return numeric_limits<int>::max() / 3;
		return b_w[{f1, f2}][n2-n1-1];
	}
	if (black1 && black2) {
		if (b_b.find({f1, f2}) == b_b.end())
			return numeric_limits<int>::max() / 3;
		return b_b[{f1, f2}][n2-n1-1];
	}
}

int main() {
	cin >> ww >> wb >> bw >> bb >> L;
	for (int i = 0; i < ww; i++) {
		int f1, f2;
		cin >> f1 >> f2;
		f1--;
		f2--;
		vector<int> v(12);
		for (auto& x : v) {
			cin >> x;
		}
		w_w[{f1, f2}] = v;
		// w_w[{f2, f1}] = v;
	}
	for (int i = 0; i < wb; i++) {
		int f1, f2;
		cin >> f1 >> f2;
		f1--;
		f2--;
		vector<int> v(12);
		for (auto& x : v) {
			cin >> x;
		}
		w_b[{f1, f2}] = v;
		// b_w[{f2, f1}] = v;
	}
	for (int i = 0; i < bw; i++) {
		int f1, f2;
		cin >> f1 >> f2;
		f1--;
		f2--;
		vector<int> v(12);
		for (auto& x : v) {
			cin >> x;
		}
		b_w[{f1, f2}] = v;
		// w_b[{f2, f1}] = v;
	}
	for (int i = 0; i < bb; i++) {
		int f1, f2;
		cin >> f1 >> f2;
		f1--;
		f2--;
		vector<int> v(12);
		for (auto& x : v) {
			cin >> x;
		}
		b_b[{f1, f2}] = v;
		// b_b[{f2, f1}] = v;
	}
	vector<int> v(L);
	for (auto& x : v) {
		cin >> x;
	}
	note = v;

	int dp[L][5];
	for (int i = 0; i != L; ++i) {
		for (int j = 0; j < 5; ++j) {
			dp[i][j] = numeric_limits<int>::max() / 3;
		}
	}

	int fingers[] = {0, 1, 2, 3, 4};
	for (int i = 0; i < L; i++) {
		for (int j : fingers) {
			if (i == 0) {
				dp[i][j] = 0;
				continue;
			}
			// cout << "dp[" << i << "][" << j << "] is the min of: " << dp[i-1][j] << " + \n";
			for (int k : fingers) {
				dp[i][j] = min(dp[i][j], dp[i-1][k] + difficulty(note[i-1], k, note[i], j));
				// cout << "\t" << difficulty(note[i-1], k, note[i], j) << "\n";
			}
		}
	}
	int final_min = numeric_limits<int>::max();
	for (int x : fingers) {
		final_min = min(final_min, dp[L-1][x]);
	}
	cout << final_min << "\n";

	// for (int i = 0; i != L; ++i) {
	// 	for (int x : fingers) {
	// 		cout << dp[i][x] << " ";
	// 	}
	// 	cout << "\n";
	// }
}