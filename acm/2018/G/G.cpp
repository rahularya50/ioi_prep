#include "bits/stdc++.h"

using namespace std;

int main() {
	int n;
	cin >> n;
	string seq;
	cin >> seq;
	
	int i = 0;
	int firstLs = 0;
	while (i != seq.size() && seq[i] == 'L') {
		++i;
		++firstLs;
	}
	int cnt = 0;
	vector<int> cnts;
	for (; i != seq.size(); ++i) { // Ls after each R
		if (seq[i] == 'L') {
			++cnt;
		} else {
			if (i != firstLs) cnts.push_back(cnt);
			cnt = 0;
		}
	}
	if (firstLs != seq.size()) {
		cnts.push_back(cnt);
	}

	int pos = firstLs;
	while (pos >= 0) {
		cout << pos+1 << "\n";
		--pos;
	}

	int first_empty = firstLs + 1;
	for (auto x : cnts) {
		// cout << "x = " << x << "\n";
		int end = first_empty + x;
		for (int i = 0; i <= x; ++i) {
			cout << (end - i + 1) << "\n";
		}
		first_empty += x + 1;
	}
}