#include "bits/stdc++.h"

using namespace std;

bool evaluate(string expr) {
	// cout << expr << "\n";
	if (expr[0] == '!') {
		return !evaluate(expr.substr(1, expr.size()));
	}
	if (expr.size() == 1) {
		return expr == "t";
	}
	int i = 0;
	int countBrackets = 0;
	while (countBrackets != 1 || (expr[i] != '&' && expr[i] != '|')) {
		if (expr[i] == '(') {
			countBrackets++;
		}
		if (expr[i] == ')') {
			countBrackets--; 
		}

		++i;
	}
	string left = expr.substr(1, i - 1);
	string right = expr.substr(i + 1, expr.size() - i - 2);
	char op = expr[i];
	if (op == '&') {
		return evaluate(left) && evaluate(right);
	} else {
		return evaluate(left) || evaluate(right);
	}
}

int main() {
	int x;
	cin >> x;
	string expr, eq, val;
	for (int i = 1; i <= x; ++i) {
		cin >> expr >> eq >> val;
		if (evaluate(expr) == (val == "t")) {
			cout << i << ": " << "Good brain\n";
		}
		else {
			cout << i << ": " << "Bad brain\n";
		}
	}
	return 0;
}