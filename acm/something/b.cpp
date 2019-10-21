#include "bits/stdc++.h"

using namespace std;

using ll = unsigned long long;

int main() {
	ll A, B, C, N;
	cin >> A >> B >> C >> N;
	ll up = N == 2 ? 0 : (N - 1) / 2 - 1;
	ll sum = up * (up + 1);
	sum >>= 1;
	ll cnt = sum * N;
	ll choose;
	if (N % 6 == 0) {
		choose = (N / 6) * (N-1) * (N-2);
	} else if (N % 6 == 1) {
		choose = N * ((N-1)/6) * (N-2);
	} else if (N % 6 == 2) {
		choose = N * (N-1) * ((N-2)/6);
	} else if (N % 6 == 3) {
		choose = (N / 3) * ((N-1) / 2) * (N-2);
	} else if (N % 6 == 4) {
		choose = (N / 2) * ((N-1) / 3) * (N-2);
	} else {
		choose = N * ((N - 1) / 2) * ((N - 2) / 3);
	}
	cnt = choose - cnt;
	set<ll> x;
	x.insert(A);
	x.insert(B);
	x.insert(C);
	if (x.size() == 3) {
		cout << 6 * cnt;
	} else if (x.size() == 2) {
		cout << 3 * cnt;
	} else {
		cout << cnt;
	}
	cout << endl;
}
