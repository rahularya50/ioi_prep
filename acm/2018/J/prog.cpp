#include "bits/stdc++.h"

using namespace std;

int size = 15;

vector<int> pegs(size);

int count_pegs() {
	int count = 0;
	for (int i = 0; i != size; ++i) {
		if (pegs[i] != 0) {
			count++;
		}
	}
	return count;
}

int new_scores(int delta, int add, bool turn) {
	if (turn) {
		return delta + add;
	}
	return delta - add;
}

int make_move(int delta, bool turn);

int create_move(int delta, bool turn, int from, int hop, int to) {
	if (pegs[hop] == 0) {
		return numeric_limits<int>::min();
	}
	int prevHop = pegs[hop];
	pegs[hop] = 0;
	pegs[to] = pegs[from];
	pegs[from] = 0;
	int retval = make_move(new_scores(delta, prevHop * pegs[to], turn), !turn);
	pegs[hop] = prevHop;
	pegs[from] = pegs[to];
	pegs[to] = 0;
	return retval;
}

int make_move(int scores, bool turn) {
	if (count_pegs() == 1) {
		return scores.first - scores.second;
	}
	int m = numeric_limits<int>::min();
	for (int i = 0; i != size; ++i) {
		if (pegs[i] == 0) {
			switch (i) {
				case 0:
					m = max(m, create_move(scores, turn, 3, 1, 0));
					m = max(m, create_move(scores, turn, 5, 2, 0));
					break;
				case 1:
					m = max(m, create_move(scores, turn, 6, 3, 1));
					m = max(m, create_move(scores, turn, 8, 4, 1));
					break;
				case 2:
					m = max(m, create_move(scores, turn, 7, 4, 2));
					m = max(m, create_move(scores, turn, 9, 5, 2));
					break;
				case 3:
					m = max(m, create_move(scores, turn, 10, 6, 3));
					m = max(m, create_move(scores, turn, 12, 7, 3));
					m = max(m, create_move(scores, turn, 5, 4, 3));
					m = max(m, create_move(scores, turn, 0, 1, 3));
					break;
				case 4:
					m = max(m, create_move(scores, turn, 11, 7, 4));
					m = max(m, create_move(scores, turn, 13, 8, 4));
					break;
				case 5:
					m = max(m, create_move(scores, turn, 12, 8, 5));
					m = max(m, create_move(scores, turn, 14, 9, 5));
					m = max(m, create_move(scores, turn, 3, 4, 5));
					m = max(m, create_move(scores, turn, 0, 2, 5));
					break;
				case 6:
					m = max(m, create_move(scores, turn, 8, 7, 6));
					m = max(m, create_move(scores, turn, 1, 3, 6));
					break;
				case 7:
					m = max(m, create_move(scores, turn, 9, 8, 7));
					m = max(m, create_move(scores, turn, 2, 4, 7));
					break;
				case 8:
					m = max(m, create_move(scores, turn, 6, 7, 8));
					m = max(m, create_move(scores, turn, 1, 4, 8));
					break;
				case 9:
					m = max(m, create_move(scores, turn, 7, 8, 9));
					m = max(m, create_move(scores, turn, 2, 5, 9));
					break;
				case 10:
					m = max(m, create_move(scores, turn, 3, 6, 10));
					m = max(m, create_move(scores, turn, 12, 11, 10));
					break;
				case 11:
					m = max(m, create_move(scores, turn, 4, 7, 11));
					m = max(m, create_move(scores, turn, 13, 12, 11));
					break;
				case 12:
					m = max(m, create_move(scores, turn, 3, 7, 12));
					m = max(m, create_move(scores, turn, 5, 8, 12));
					m = max(m, create_move(scores, turn, 10, 11, 12));
					m = max(m, create_move(scores, turn, 14, 13, 12));
					break;
				case 13:
					m = max(m, create_move(scores, turn, 4, 8, 13));
					m = max(m, create_move(scores, turn, 11, 12, 13));
					break;
				case 14:
					m = max(m, create_move(scores, turn, 5, 9, 14));
					m = max(m, create_move(scores, turn, 12, 13, 14));
					break;
			}
		}
	}
	return m;
}

int main() {
	for (auto &x : pegs) {
		cin >> x;
	}
	cout << make_move(0, true) << "\n";
	return 0;
}