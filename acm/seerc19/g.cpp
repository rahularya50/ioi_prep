#include "bits/stdc++.h"

using namespace std;

bool most[101][101][101];
bool least[101][101][101];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);


	int n, m, h;
	cin >> n >> m >> h;
	vector<vector<int>> left(n, vector<int>(m));
	for (int i = 0; i != n; ++i) {
		for (int j = 0; j != m; ++j) {
			char x;
			cin >> x;
			left[i][j] = (x == '1');
		}
	}
	vector<vector<int>> front(n, vector<int>(h));
	for (int i = 0; i != n; ++i) {
		for (int j = 0; j != h; ++j) {
			char x;
			cin >> x;
			front[i][j] = (x == '1');
		}
	}

	auto leftRemaining = left;
	auto frontRemaining = front;

	int kmax = 0;
	int kmin = 0;

	// first compute max
	for (int i = 0; i != n; ++i) {
		for (int j =  0; j != m; ++j) {
			for (int k = 0; k != h; ++k) {
				if (left[i][j] && front[i][k]) {
					most[i][j][k] = true;
					leftRemaining[i][j] = false;
					frontRemaining[i][k] = false;
					++kmax;
				}
			}
		}
	}

	// then verify
	for (int i = 0; i != n; ++i) {
		for (int j = 0; j != m; ++j) {
			if (leftRemaining[i][j])  {
				cout << -1 << "\n";
				return 0;
			}
		}
		for (int j = 0; j != h; ++j) {
			if (frontRemaining[i][j])  {
				cout << -1 << "\n";
				return 0;
			}
		}
	}

	// otherwise begin output of the max
	cout << kmax << "\n";
	for (int i = 0; i != n; ++i) {
		for (int j =  0; j != m; ++j) {
			for (int k = 0; k != h; ++k) {
				if (most[i][j][k]) {
					cout << i << " " << j << " " << k << "\n";
				}
			}
		}
	}

	// find min
	for (int i = 0; i != n; ++i) {
		vector<int> left_cords;
		vector<int> front_cords;
		for (int j = 0; j != m; ++j) {
			if (left[i][j]) left_cords.push_back(j);
		}
		for (int j = 0; j != h; ++j) {
			if (front[i][j]) front_cords.push_back(j);
		}
		int l0 = 0;
		int f0 = 0;
		while (l0<left_cords.size() || f0<front_cords.size()){
			least[i][left_cords[l0]][front_cords[f0]] = true;
			if (left_cords.size()-l0> front_cords.size()-f0){
				l0 ++;
			}
			else if (left_cords.size()-l0< front_cords.size()-f0){
				f0 ++;
			}
			else{
				l0++;f0++;
			}
		}
	}

	for (int i = 0; i != n; ++i) {
		for (int j =  0; j != m; ++j) {
			for (int k = 0; k != h; ++k) {
				if (least[i][j][k]) {
					++kmin;
				}
			}
		}
	}

	// otherwise begin output of the min
	cout << kmin << "\n";
	for (int i = 0; i != n; ++i) {
		for (int j =  0; j != m; ++j) {
			for (int k = 0; k != h; ++k) {
				if (least[i][j][k]) {
					cout << i << " " << j << " " << k << "\n";
				}
			}
		}
	}


}
