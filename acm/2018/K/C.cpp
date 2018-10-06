#include "bits/stdc++.h"

using namespace std;

void encode(string s) {
	char cur;
	int count = 0;
	for (int i = 1; i < s.size(); i++) {
		if (count == 0) {
			cur = s[i];
			count = 1;
		}
		else if (cur == s[i]) {
			count ++;
		}
		else {
			cout << cur << count;
			count = 1;
			cur = s[i];
		}
	}
	cout << cur << count << "\n";
}

void decode(string s) {
	char c;
	for (int i = 1; i < s.size(); i++) {
		if (i % 2 == 1) {
			c = s[i];
		}
		else {
			for (int j = 0; j < s[i] - '0'; j++) {
				cout << c;
			}
		}
	}
	cout << "\n";
}

int main() {
	char operation;
	cin >> operation;
	string s;
	getline(cin, s);
	if (operation == 'E') {
		encode(s);
	}
	else {
		decode(s);
	}
	return 0;
}