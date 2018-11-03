#include "bits/stdc++.h"
using namespace std;

int main () {
	int T;
	cin >> T;
	while (T--) {
		int N;
		cin >> N;
		vector<int> x(N);
		vector<int> prev(N);
		for (int i = 0; i < N; ++i) {
			cin >> x[i];
			prev[i] = x[i];
		}
		int i;
		for (i = 1; i < N; ++i) {
			int acc = 0;
			for (int j = i - 1; j < N; ++j) {
				acc += (prev[j] != 0);
			}
			if (!acc) break;
			for (int j = i; j < N; ++j) {
				x[j] = x[j] - prev[j - 1];
			}
			for (int j = i; j < N; ++j) {
				prev[j] = x[j];
			}
		}
		//end:;
		if (x[N - 1] == 0) {
			for (int j = 0; j < i - 1; ++j) cout << "z";
			cout << "ap!" << endl;
		} else if (x[N - 1] > 0) {
			cout << "*fizzle*" << endl;
		} else {
			cout << "*bunny*" << endl;
		}
	}
}