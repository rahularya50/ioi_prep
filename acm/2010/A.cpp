// #include <vector>
// #include <iostream>
// #include <string>
#include "bits/stdc++.h"

using namespace std;

int main() {
	int q;
	cin >> q;
	vector<string> quotes(q);
	string meh;
	getline(cin, meh);
	for (auto& x : quotes) {
		getline(cin, x);
	}

	// cout << "meh = " << meh << "\n";

	int r;
	cin >> r;

	// cout << "r = " << r << "\n";

	for (int i = 0; i != r; ++i) {
		int x;
		cin >> x;
		// cout << "hi!\n";
		--x;
		if (x < 0 || x >= q) {
			// printf("hi");
			cout << "Rule " << (x + 1) << ": " << "No such rule" << endl;
		} else {
			cout << "Rule " << (x + 1) << ": " << quotes[x] << endl;	
		}
	}
}