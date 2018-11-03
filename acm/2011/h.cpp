#include "bits/stdc++.h"

using namespace std;

int main() {
	double a, b, c, d, m, t;
	while (cin >> a) {
		cin >> b >> c >> d >> m >> t;
		double low = 0;
		double high = 1000000000000;
		while (high - low > 1e-9) {
			auto v = (low + high) / 2;
			auto consumed = m * (a * pow(v, 3) + b * pow(v, 2) + c * pow(v, 1) + d);
			if (consumed < t) {
				low = v;
			} else {
				high = v;
			}
		}
		printf("%.2lf\n", floor(low * 100) / 100.0);
	}
}