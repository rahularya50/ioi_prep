#include "bits/stdc++.h"

using namespace std;

int main() {
	int n;
	cin >> n;
	for (int i = 0; i != n; ++i) {
		int gnomes;
		cin >> gnomes;
		vector<int> g(gnomes);
		for (auto& x : g) {
			cin >> x;
		}
		for (int j = 1; j != gnomes-1; ++j) {
			if (g[j] - g[j - 1] != 1) {
				cout << (j+1) << "\n";
				break;
			}
		}
	}
}