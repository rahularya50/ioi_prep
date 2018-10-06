#include "bits/stdc++.h"

using namespace std;

struct row {
	int card;
	vector<int> vals;
};

bool operator<(row x, row y){
	return x.vals < y.vals;
}

int main() {
	int n;
	cin >> n;

	set<row> rows;
	vector<vector<row>> cards(n, vector<row>(5));

	for (int i = 0; i != n; ++i) {
		for (int x = 0; x != 5; ++x) {
			// read in a row
			vector<int> vals(5);
			for (auto& y : vals) {
				cin >> y;
			}
			rows.insert({i, vals});
			cards[i][x] = {i, vals};
		}
	}

	for (int card1 = 0; card1 != n; ++card1) {
		for (int card2 = card1 + 1; card2 != n; ++card2) {
			for (auto row1 : cards[card1]) {
				for (auto row2 : cards[card2]) {
					// check if they can lead to a tie
					set<int> vals;
					for (auto x : row1.vals) {
						vals.insert(x);
					}
					bool canTie = false;
					for (auto y : row2.vals) {
						if (vals.find(y) != vals.end()) {
							canTie = true;
						}
						vals.insert(y);
					}
					if (!canTie) {
						continue;
					}
					bool works = false;
					for (auto val : vals) {
						for (auto card : cards) {
							for (auto row_obj : card) {
								bool fail = false;
								for (auto x : row_obj.vals) {
									if (x == val || vals.find(x) == vals.end()) {
										fail = true;
										break;
									}
								}
								if (!fail) {
									// this val won't work
									goto end;
								}
							}
						}
						works = true;
						break;
						end:
							continue;
					}
					if (works) {
						// cout << row1.vals[0] << " with " << row2.vals[0] << " => ";
						cout << card1 + 1 << " " << card2 + 1 << "\n";
						return 0;
					}
					
				}
			}
		}
	}

	cout << "no ties\n";

	return 0;
}