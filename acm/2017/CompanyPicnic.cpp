#include "bits/stdc++.h"

using namespace std;

vector<vector<int>> children;
vector<int> parent;
vector<double> speed;

struct thing {
	pair<int, double> best;
	pair<int, double> no_team;
};

thing empty_thing;

vector<thing> memo;

thing dp(int i) {
	if (memo[i].best.first != -1) {
		return memo[i];
	}
	pair<int, double> no_team = {0, 0.0};
	for (auto x : children[i]) {
		auto ret = dp(x).best;
		no_team.first += ret.first;
		no_team.second += ret.second;
	}

	pair<int, double> best = no_team;
	for (auto x : children[i]) {
		// make a team with x
		auto ret = dp(x).no_team;
		pair<int, double> candidate = no_team;
		candidate.first -= dp(x).best.first;
		candidate.second -= dp(x).best.second;

		candidate.first += dp(x).no_team.first;
		candidate.second += dp(x).no_team.second;

		candidate.first += 1;
		candidate.second += min(speed[i], speed[x]);

		best = max(best, candidate);
	}

	memo[i] = {best, no_team};

	return {best, no_team};
}

int main() {
	empty_thing.best.first = -1;

	int n; 
	cin >> n;
	vector<string> names(n);
	vector<string> boss(n);
	map<string, int> lookup;

	parent = vector<int>(n);
	speed = vector<double>(n);
	children = vector<vector<int>>(n);

	memo = vector<thing>(n, empty_thing);


	for (int i = 0; i != n; ++i) {
		cin >> names[i];
		cin >> speed[i];
		cin >> boss[i];
		lookup[names[i]] = i;
	}
	int root = -1;
	for (int i = 0; i != n; ++i) {
		if (boss[i] == "CEO") {
			parent[i] = -1;
			root = i;
		} else {
			parent[i] = lookup[boss[i]];
			children[parent[i]].push_back(i);
		}
	}

	cout << dp(root).best.first << " " << (dp(root).best.second / dp(root).best.first) << "\n";

}