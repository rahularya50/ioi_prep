#include "bits/stdc++.h"
using namespace std;

int N;
string s;

int main() {
	scanf("%d\n", &N);
	for(int i = 0; i < N; i++) {
		getline(cin, s);
		int ng = 0, nb = 0;
		for(char x: s) {
			ng += x == 'g' || x == 'G';
			nb += x == 'b' || x == 'B'; 
		}
		cout << s << " is ";
		if(ng > nb) {
			cout << "GOOD\n";
		} else if(ng < nb) {
			cout << "A BADDY\n";
		} else {
			cout << "NEUTRAL\n";
		}
	}
}