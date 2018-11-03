#include "bits/stdc++.h"

using namespace std;

struct elem {
	int i;
	vector<pair<char, char>> paths;
};

string decode(int i, int w, int h) {
	int xpos = i % 100;
	int ypos = i / 100;
	int row = ypos / 3;
	int col = xpos / 3;

	// cout << "xpos = " << xpos << ", ypos = " << ypos << ", row = " << row << ", col = " << col << "\n";

	if (row == 0) {
		int val = col + 1;
		// cout << "val = " << val << "\n";
		if (xpos % 3 == 1) {
			return to_string(val) + 'A';
		} else if (xpos % 3 == 2) {
			return to_string(val) + 'B';
		}
	}
	if (row == h) {
		int val = w * (h - 1) + col + 1;
		if (xpos % 3 == 1) {
			return to_string(val) + 'F';
		} else if (xpos % 3 == 2) {
			return to_string(val) + 'E';
		}
	}
	if (col == 0) {
		int val = (row) * w + 1;
		if (ypos % 3 == 1) {
			return to_string(val) + 'H';
		} else if (ypos % 3 == 2) {
			return to_string(val) + 'G';
		}
	}
	if (col == w) {
		int val = (row + 1) * w;
		if (ypos % 3 == 1) {
			return to_string(val) + 'C';
		} else if (ypos % 3 == 2) {
			return to_string(val) + 'D';
		}
	}
	return "Err";
}

int node_to_val(int w, int h, int i, char x) {
	int row = (i - 1) / w;
	int col = (i - 1) % w;
	int xDelta, yDelta;
	if (x == 'A') {
		xDelta = 1; yDelta = 0;
	}
	if (x == 'B') {
		xDelta = 2; yDelta = 0;
	}
	if (x == 'C') {
		xDelta = 3; yDelta = 1;
	}
	if (x == 'D') {
		xDelta = 3; yDelta = 2;
	}
	if (x == 'E') {
		xDelta = 2; yDelta = 3;
	}
	if (x == 'F') {
		xDelta = 1; yDelta = 3;
	}
	if (x == 'G') {
		xDelta = 0; yDelta = 2;
	}
	if (x == 'H') {
		xDelta = 0; yDelta = 1;
	}
	auto xpos = col * 3 + xDelta;
	auto ypos = row * 3 + yDelta;
	return xpos + ypos * 100;
}

int main() {
	int h, w;
	for (int i = 1; true; ++i) {
		cin >> h;
		cin >> w;
		if (h == 0) {
			break;
		}

		// cout << "readin " << h << ", " << w << endl;

		vector<elem> elems;
		while (true) {
			int n;
			cin >> n;
			if (n == 0) {
				break;
			}
			elem e;
			e.i = n;
			string s;
			getline(cin, s);

			char prev = 0;
			for (auto x : s) {
				if (x == ' ') {
					continue;
				}
				if (prev == 0) {
					prev = x;
				} else {
					e.paths.push_back({prev, x});
					prev = 0;
				}
			}

			elems.push_back(e);
		}

		// cout << "building graph\n";

		const int SIZE = w * h * 2000;

		vector<vector<int>> graph(SIZE);
		for (auto e : elems) {
			for (auto link : e.paths) {
				auto a = node_to_val(w, h, e.i, link.first);
				auto b = node_to_val(w, h, e.i, link.second);
				// cout << "edge: " << a << ", " << b << endl;
				graph[a].push_back(b);
				graph[b].push_back(a);
			}
		}

		string s;
		getline(cin, s);
		getline(cin, s);

		vector<int> starts;

		int val = 0;

		for (auto x : s) {
			if (x == ' ') {
				continue;
			}
			if ('0' <= x && x <= '9') {
				val = val * 10 + (x - '0');
			} else {
				starts.push_back(node_to_val(w, h, val, x));
				// cout << "Val was = " << val << "\n";
				// cout << "reading x = " << x << "\n";
				val = 0;
			}
		}

		cout << "Board " << i << ": \n";

		vector<bool> visited(SIZE);
		for (auto i : starts) {
			int pos = i;
			int prev = -1;
			// cout << "start: " << i << endl;
			while (pos == i || graph[pos].size() == 2) {
				// cout << "visiting " << pos << "\n";
				visited[pos] = true;
				int next;
				if (graph[pos][0] == prev) {
					next = graph[pos][1];
				} else {
					next = graph[pos][0];
				}
				prev = pos;
				pos = next;
			}
			visited[pos] = true;
			// cout << i << " is connected to " << pos << "\n";
			cout << decode(i, w, h) << " is connected to " << decode(pos, w, h) << "\n";
		}
		cout << "\n";

	}
}