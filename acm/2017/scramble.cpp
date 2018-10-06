#include "bits/stdc++.h"

using namespace std;

int main() {
	int n;
	cin >> n;
	for (int i = 0; i != n; ++i) {
		char c;
		string s;
		cin >> c;
		getline(cin, s);
		bool isFirst = true;
		if (c == 'e') {
			int curr = 0;
			for (auto x : s) {
				if (isFirst) {
					isFirst = false;
					continue;
				}
				int v;
				if (x == ' ') {
					v = 0;
				} else {
					v = x - 'a' + 1;
				}
				curr = (curr + v) % 27;
				char out = (curr == 0) ? ' ' : curr + 'a' - 1;
				cout << out;
			}
		}
		if (c == 'd') {
			int curr = 0;
			for (auto x : s) {
				if (isFirst) {
					isFirst = false;
					continue;
				}
				int currval = (x == ' ') ? 0 : (x - 'a' + 1);
				curr = (currval - curr + 27) % 27;
				char out = (curr == 0) ? ' ' : (curr + 'a' - 1);
				cout << out;
				curr = currval;
			}
		}
		cout << "\n";
	}
}