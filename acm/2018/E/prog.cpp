#include "bits/stdc++.h"

using namespace std;

double dot(pair<double, double> a, pair<double, double> b) { return a.first * b.first + a.second * b.second; }
double square(double x) { return x * x; }

int main() {
	int n;
	cin >> n;
	vector<pair<double, double>> coords(n);
	for (auto& x : coords) {
		cin >> x.first >> x.second;
	}
	int out = -1;
	for (int i = 0; i != n; ++i) {
		for (int j = i + 1; j != n; ++j) {
			if (coords[i] == coords[j]) continue;
			vector<double> projections(n);
			for (int k = 0; k != n; ++k) {
				auto a = coords[i];
				auto b = coords[j];
				auto p = coords[k];

				pair<double, double> ap = {p.first - a.first, p.second - a.second};
				pair<double, double> ab = {b.first - a.first, b.second - a.second};
				double u = dot(ap, ab) / dot(ab, ab);
				pair<double, double> c = {a.first + ab.first * u, a.second + ab.second * u};
				auto sqdist = square(c.first - p.first) + square(c.second - p.second);
				auto dist = sqrt(sqdist);

				projections[k] = dist;
			}
			sort(projections.begin(), projections.end());
			int low = 0;
			int high = 0;
			int best = -1;
			int curr = 0;
			for (auto x : projections) {
				cout << x << ", ";
			}
			cout << "\n";
			while (low != n) {
				if (high != n && projections[high] - projections[low] <= 1) {
					++high;
					++curr;
					continue;
				}
				cout << i << ", " << j << ", " << low << ", " << high << ", " << curr << "\n";
				best = max(best, curr);
				++low;
				--curr;
			}
			out = max(best, out);

		}
	}
	if (out == -1) out = n;
	cout << out << "\n";
}