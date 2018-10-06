#include "bits/stdc++.h"

using namespace std;

int lcm(int p, int q) {
	for (int i = min(p, q); i <= p*q; i++) {
		if (i % p == 0 && i % q == 0) {
			return i;
		}
	}
	return -1;
}

int main() {
	int p, q, s;
	cin >> p >> q >> s;
	cout << ((lcm(p, q) <= s) ? "yes" : "no") << "\n";
	return 0;
}