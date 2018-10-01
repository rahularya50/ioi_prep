#include "bits/stdc++.h"

using namespace std;

void go(long long n) {
	auto besta = 4000;
	auto bestb = 4000;
	auto bestc = 4000;
	for (long long a = 1; a < 4000; ++a) {
		for (long long c = 1; a+c < 4000 && c <= a; ++c) {
			auto cubesum = a*a*a + c*c*c;
			if (cubesum % n != 0) continue;
			auto bcube = cubesum / n;
			auto b = round(pow(bcube, 1.0/3));
			if (b*b*b != bcube) continue;
			auto sum = a + 2*b + c;
			if (sum < besta + 2*bestb + bestc) {
				besta = a;
				bestb = b;
				bestc = c;
			}
		}
	}
	if (besta == 4000) {
		cout << "No value.\n";
	} else {
		cout << "(" << besta << "/" << bestb << ")^3 + (" << bestc << "/" << bestb << ")^3 = " << n << "\n";
	}
}

int main() {
	int n;
	for (cin >> n; n != 0; cin >> n) {
		go(n);
	}
}