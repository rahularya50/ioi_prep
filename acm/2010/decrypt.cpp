#include "bits/stdc++.h"

using namespace std;



double r(int a, int m, int &s) {
	double val = (s % m) / static_cast<double>(m);
	s = (a * s + 1) % m;
	return val;
}

int main() {
	int a, m, s;
	cin >> a >> m >> s;
	char c;
	cin.get(c);
	while (cin.get(c)) {
		// cout << "Read: " << c << "\n";
 		if (c < 0x20 || c > 0x7e) {
			cout << c;
		} else {
			int notmod = r(a,m,s)*95;
			int modulus = 95 - notmod;
			char real = 32 + (c - modulus - 32 + 2 * 95) % 95;
			// cout << "Char = " << (int)real << ", ";
			cout << real;
		}
	}
	return 0;
}