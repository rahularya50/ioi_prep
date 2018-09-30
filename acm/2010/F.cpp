#include "bits/stdc++.h"

using namespace std;

using ll = long long;

using digcount = array<int, 10>;

void printdigits(digcount x) {
	cout << "{";
	for (int i = 0; i != 10; ++i) {
		cout << i << ": " << x[i] << ", ";
	}
	cout << "}";
}

bool worker(digcount& digits, ll goal, ll left, ll right, ll base) {
	// printdigits(digits);
	// cout << ", " << goal << ", " << left << ", " << right << ", " << base << "\n";


	if (left * right > goal) return false;

	auto remaining = accumulate(digits.begin(), digits.end(), 0);
	if (remaining == 0) {
		if (left * 10 < base || right * 10 < base) return false;
		return (left * right == goal);
	}

	for (int i = 0; i != 10; ++i) {
		if (i == 0 && base != 1 && left * 10 < base) continue;
		for (int j = 0; j != 10; ++j) {
			if (j == 0 && base != 1 && right * 10 < base) continue;
			if (digits[i] <= 0 || digits[j] <= 0) {
				continue;
			}
			if (i == j && digits[i] <= 1) {
				continue;
			}
			auto newleft = base * i + left;
			auto newright = base * j + right;
			auto prod = newleft * newright;
			if (prod % (base * 10) != goal % (base * 10)) {
				continue;
			}
			--digits[i];
			--digits[j];
			if (worker(digits, goal, newleft, newright, base * 10)) {
				return true;
			}
			++digits[i];
			++digits[j];
		}
	}

	return false;
}

string vampire(string n) {
	if (n.size() % 2 == 1) return "no";
	ll thing = stoll(n);
	if (thing <= 0) return "no";
	digcount digits = {};
	for (auto x : n) {
		++digits[x - '0'];
	}
	if (worker(digits, thing, 0, 0, 1)) {
		return "yes";
	} else {
		return "no";
	}
}

int main() {
	string n;
	cin >> n;
	while (n != "0") {
		cout << n << ": " << vampire(n) << "\n";
		cin >> n;
	}
	return 0;
}