#include "bits/stdc++.h"

using namespace std;

double square(double x) { return x*x; }

double find_len(vector<pair<double, double>>& points) {
	double out = 0;
	auto curr = points.front();
	for (auto x : points) {
		out += sqrt(square(x.first - curr.first) + square(x.second - curr.second));
		curr = x;
	}
	return out;
}

int main() {
	int n, t;
	cin >> n >> t;
	vector<pair<double, double>> points(n);
	vector<int> times(n);
	for (int i = 0; i != n; ++i) {
		auto& x = points[i];
		cin >> x.first >> x.second >> times[i];
	}

	int start_i = 0;
	int end_i = 1;

	vector<pair<double, double>> gps;
	for (int T = 0; T < times.back(); T += t) {
		while (times[end_i] < T) {
			++start_i;
			++end_i;
		}
		int start_t = times[start_i];
		int end_t = times[end_i];
		double end_weight = static_cast<double>(T - start_t) / (end_t - start_t);
		double x = (1.0 - end_weight) * points[start_i].first + end_weight * points[end_i].first;
		double y = (1.0 - end_weight) * points[start_i].second + end_weight * points[end_i].second;
		gps.push_back({x, y});
	}

	gps.push_back(points.back());

	cout << setprecision(10) << (100 - find_len(gps) * 100 / find_len(points)) << "\n";
}