#include "bits/stdc++.h"

using namespace std;

const int GOAL = 2018;

int main() {
	vector<pair<int, int>> combos;
	for (int i = 0; i <= 2018; ++i) {
		int delta_squared = GOAL*GOAL - i*i;
		int maybe = round(sqrt(delta_squared));
		if (maybe * maybe == delta_squared) {
			combos.push_back({i, maybe});
			// cout << i << ", " << maybe << "\n";
		}
	}
	int n;
	cin >> n;
	set<pair<int, int>> points;
	for (int i = 0; i != n; ++i) {
		int x, y;
		cin >> x >> y;
		points.insert({x, y});
	}

	int out = 0;
	for (auto& p : points) {
		auto x = p.first;
		auto y = p.second;

		for (auto combo : combos) {
			for (auto deltaX : {-1, 1}) {
				for (auto deltaY : {-1, 1}) {
					auto newX = x + deltaX * combo.first;
					auto newY = y + deltaY * combo.second;
					if (points.find({newX, newY}) != points.end()) {
						// cout << x << ", " << y << " -> " << newX << ", " << newY << "\n";
						++out;
					}
					if (combo.second == 0) {
						break;
					}
				}
				if (combo.first == 0) {
					break;
				}
			}
		}
	}

	cout << (out / 2) << "\n";
}