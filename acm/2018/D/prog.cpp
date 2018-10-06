#include "bits/stdc++.h"

using namespace std;

struct lane {
	int offset;
	int interval;
	int speed;
};

int main() {
	int L, W;
	cin >> L >> W;
	vector<lane> lanes(L);
	
	// lane 0 is at the TOP
	for (int x = 0; x != L; ++x) {
		int O, I, S;
		cin >> O >> I >> S;
		if (x % 2 == 1) {
			O = W - O - 1;
		}
		lanes[x] = {O, I, S};
		if (S >= I) {
			cout << "squish" << "\n";
			return 0;
		}
	}

	int x, y;
	cin >> x; // x = 0 is at the LEFT
	y = L;

	string moves;
	cin >> moves;
	int turns = 0;
	for (auto move : moves) {
		auto newX = x;
		auto newY = y;
		if (move == 'U') {
			--newY;
		} else if (move == 'D') {
			++newY;
		}
		else if (move == 'L') {
			--newX;
		} else {
			++newX;
		}
		if (newY < 0) {
			y = newY;
			++turns;
			continue;
		}
		if (newY == L) {
			x = newX;
			y = newY;
			++turns;
			continue;
		}

		int min_danger_mod = (turns * lanes[newY].speed) % lanes[newY].interval;
		++turns; // actually is safe

		int max_danger_mod = (turns * lanes[newY].speed) % lanes[newY].interval;


		int xMod = (newX - lanes[newY].offset + 2*W*lanes[newY].interval) % lanes[newY].interval;
		if (newY % 2 == 1) {
			int xReflect = lanes[newY].offset - newX;
			xMod = (xReflect + 2*W*lanes[newY].interval) % lanes[newY].interval;
		}

		// cout << "xMod = " << xMod << "\n";
		// cout << "minMod = " << min_danger_mod << "\n";
		// cout << "maxMod = " << max_danger_mod << "\n";

		// cout << newX << ", " << newY << "\n";

		if (min_danger_mod == max_danger_mod) {
			if (xMod == min_danger_mod) {
				cout << "squish\n";
				return 0;
			}
		}
		else if (min_danger_mod < max_danger_mod) {
			if (xMod > min_danger_mod && xMod <= max_danger_mod) {
				cout << "squish" << "\n";
				return 0;
			}
		} else {
			if (xMod > min_danger_mod || xMod <= max_danger_mod) {
				cout << "squish" << "\n";
				return 0;
			}
		}

		x = newX;
		y = newY;
	}

	cout << (y < 0 ? "safe" : "squish") << "\n";
}