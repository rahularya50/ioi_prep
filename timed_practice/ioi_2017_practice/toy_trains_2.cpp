
#include <bits/stdc++.h>

using namespace std;

vector<int> owner;
vector<int> charging;
vector<vector<int>> graph;

int UNSET = 15;

using ull = unsigned long long;

void printstate(const vector<int>& states, int pos) {
    cout << "pos = " << pos << ", ";
    for (int i = 0; i != states.size(); ++i) {
        cout << i << " -> " << states[i] << ", ";
    }
    cout << "\n";
}
// 4 bits for 15 nodes => 60 bits i.e. a long long
ull encode(const vector<int>& states, int pos) {
//    cout << "encoding!\n";
    ull out = 0;
    for (auto x : states) {
        out <<= 4;
        out += x;
    }
    out <<= 4;
    out += pos;
//    printstate(states, pos);
//    cout << "out = " << out << "\n";
    return out;
}



map<ull, bool> cache;

bool solve(ull state) {
    if (cache.find(state) != cache.end()) {
        return cache[state];
    }

    ull original_state = state;

    int pos = state % (1 << 4);
    state >>= 4;

    vector<int> states(graph.size());
    for (int i = graph.size() - 1; i >= 0; --i) {
        states[i] = state % (1 << 4);
        state >>= 4;
    }

    if (states[pos] != UNSET) {
        // is in cycle
        bool isChargeCycle = charging[pos];
        int cycle_pos = states[pos];
        while (cycle_pos != pos) {
            if (charging[cycle_pos]) {
                isChargeCycle = true;
                break;
            }
            cycle_pos = states[cycle_pos];
        }
        cache[original_state] = isChargeCycle;
        return isChargeCycle;
    }

    bool desired = owner[pos];
    bool result = !desired;
    for (auto new_pos : graph[pos]) {
        states[pos] = new_pos;
        auto res = solve(encode(states, new_pos));
        if (res == desired) {
            result = desired;
            break;
        }
    }
    cache[original_state] = result;
//    printstate(states, pos);
//    cout << "Res = " << result << "\n";
    return result;
}

vector<int> who_wins(vector<int> a, vector<int> r, vector<int> u, vector<int> v) {
    owner = a; // {1, 1, 1, ...}
    charging = r;
    graph = vector<vector<int>>(a.size());
    for (int i = 0; i != u.size(); ++i) {
        graph[u[i]].push_back(v[i]);
    }

    vector<int> out(a.size());
    vector<int> defstates(graph.size());
    for (auto& x : defstates) {
        x = UNSET;
    }
    for (int i = 0; i != a.size(); ++i) {
        out[i] = solve(encode(defstates, i));
    }

    return out;
}
//
//int main() {
//	int n, m;
//	assert(2 == scanf("%d %d", &n, &m));
//
//	vector<int> a(n), r(n), u(m), v(m);
//
//	for(int i = 0; i < n; i++)
//		assert(1 == scanf("%d", &a[i]));
//
//	for(int i = 0; i < n; i++)
//		assert(1 == scanf("%d", &r[i]));
//
//	for(int i = 0; i < m; i++)
//		assert(2 == scanf("%d %d", &u[i], &v[i]));
//
//	vector<int> res = who_wins(a, r, u, v);
//
//	for(int i = 0; i < (int)res.size(); i++)
//		printf(i ? " %d" : "%d", res[i]);
//	printf("\n");
//
//	return 0;
//}
