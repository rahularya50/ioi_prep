#include <bits/stdc++.h>

using namespace std;

int main() {
	int N;
	cin >> N;
	vector<long long> V;
	for (int i = 0; i != N; ++i) {
		long long temp;
		cin >> temp;
		V.push_back(temp);
	}
	
	sort(V.begin(), V.end());
	
	double best = numeric_limits<double>::infinity();
	for (int i = 0; i != N - 2; ++i) {
		best = min(best, (V[i+2] - V[i]) / 2.0);
	}
	
	cout << fixed;
	cout << setprecision(1);

	cout << best;
}
