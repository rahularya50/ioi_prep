#include "bits/stdc++.h"

using namespace std;

const int LEFT = 0;
const int RIGHT = 1;
const int FORWARD = 2;

pair<int, int> execute(vector<int>& instructions) {
	pair<int, int> pos = {0, 0};
	int deltaX = 0;
	int deltaY = 1;

	for (const auto& x : instructions) {
		if (x == FORWARD) {
			pos.first += deltaX;
			pos.second += deltaY;
		}
		else if (x == LEFT) {
			auto newdeltaX = -1*deltaY;
			deltaY = deltaX;
			deltaX = newdeltaX;
		}
		else if (x == RIGHT) {
			auto newdeltaX = deltaY;
			deltaY = -1*deltaX;
			deltaX = newdeltaX;
		}
			// cout << pos.first << ", " << pos.second << "\n";
	}


	return pos;
}

int main() {
	int x, y;
	cin >> x >> y;
	int n;
	cin >> n;
	vector<int> instructions(n);
	for (auto& x : instructions) {
		string s;
		cin >> s;
		switch (s[0]) {
			case 'L': x = LEFT; break;
			case 'R': x = RIGHT; break;
			case 'F': x = FORWARD; break;
		}
	}

	// execute(instructions);
	// return 0;

	// for (auto x : instructions) {
	// 	cout << x << ", ";
	// }

	pair<int, int> goal = {x, y};
	for (int i = 0; i != n; ++i) {
		auto original = instructions[i];
		for (int alt = 0; alt != 3; ++alt) {
			instructions[i] = alt;
			if (execute(instructions) == goal) {
				cout << (i + 1) << " ";
				if (alt == LEFT) {
					cout << "Left";
				} else if (alt == RIGHT) {
					cout << "Right";
				} else {
					cout << "Forward";
				}
				cout << "\n";
				return 0;
			}
		}
		instructions[i] = original;
	}

	cout << "fail\n";


}