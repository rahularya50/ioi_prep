#include <bits/stdc++.h>

using namespace std;

vector<int> owner;
vector<int> charging;
vector<vector<int>> graph;
vector<int> winner;

int go_1(int i) {
//    cout << "go(" << i << ")\n";
    bool selfLoop = false;
    int nextNode = -1;
    for (auto x : graph[i]) {
        if (x == i) {
            selfLoop = true;
        } else {
            nextNode = x;
            // x = i + 1!
        }
    }

    if (charging[i]) {
        if ((owner[i] == 1 && selfLoop) || nextNode == -1) {
            winner[i] = 1;
            return 1;
            // can force to enter selfLoop
        } else {
            // will not enter selfLoop
            winner[i] = go_1(nextNode);
            return winner[i];
        }
    } else {
        if ((owner[i] == 0 && selfLoop) || nextNode == -1) {
            winner[i] = 0;
            return 0;
        } else {
            winner[i] = go_1(nextNode);
            return winner[i];
        }
    }
}

vector<int> who_wins_1(vector<int> a, vector<int> r, vector<int> u, vector<int> v) {
    owner = a;
    charging = r;
    graph = vector<vector<int>>(a.size());
    for (int i = 0; i != u.size(); ++i) {
        graph[u[i]].push_back(v[i]);
    }

    vector<int> out(a.size());
    winner = vector<int>(a.size(), -1);
    for (int i = 0; i != a.size(); ++i) {
        out[i] = go_1(i);
    }
    return out;
}


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

vector<int> who_wins_2(vector<int> a, vector<int> r, vector<int> u, vector<int> v) {
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

vector<vector<int>> canreach;

// we need to find all the cycles from charging points, and mark such visited points as "win states"

int OLD_CYCLE = 1;
int WIN = 2;
int LOSE = 3;
int UNKNOWN = 0;

void dfs_3(int i, int origin, bool isFirst) {
//    cout << "Reached " << i << " from " << origin << "\n";
    if (canreach[origin][i] == true) {
        return;
    }
    if (!isFirst) {
        canreach[origin][i] = true;
    }
    for (auto x : graph[i]) {
        dfs_3(x, origin, false);
    }
}

vector<int> who_wins_3(vector<int> a, vector<int> r, vector<int> u, vector<int> v) {
    owner = a; // {1, 1, 1, ...}
    charging = r;
    graph = vector<vector<int>>(a.size());
    for (int i = 0; i != u.size(); ++i) {
        graph[u[i]].push_back(v[i]);
    }

    vector<int> out(a.size());
    canreach = vector<vector<int>>(a.size(), vector<int>(a.size(), false));
    for (int i = 0; i != a.size(); ++i) {
        dfs_3(i, i, true);
    }

//    for (int i = 0; i != a.size(); ++i) {
//        cout << i << ": {";
//        for (auto x : canreach[i]) {
//            cout << x << ", ";
//        }
//        cout << "}\n";
//    }

    vector<int> useful_chargers;
    for (int i = 0; i != a.size(); ++i) {
        if (charging[i] && canreach[i][i]) {
            useful_chargers.push_back(i);
        }
    }

    for (int i = 0; i != a.size(); ++i) {
        for (auto x : useful_chargers) {
            if (canreach[i][x]) {
                out[i] = 1;
            }
        }
    }

    return out;
}

vector<vector<int>> canreach_nochargers;

// we need to find all the cycles from charging points, and mark such visited points as "win states"


void dfs_4(int i, int origin, bool isFirst) {
//    cout << "Reached " << i << " from " << origin << "\n";
    if (canreach[origin][i] == true) {
        return;
    }
    if (!isFirst) {
        canreach[origin][i] = true;
    }
    for (auto x : graph[i]) {
        dfs_4(x, origin, false);
    }
}

void dfs_nochargers_4(int i, int origin, bool isFirst) {
//    cout << "Reached " << i << " from " << origin << "\n";
    if (charging[i]) {
        canreach_nochargers[origin][i] = false;
        return;
    }
    if (canreach_nochargers[origin][i] == true) {
        return;
    }
    if (!isFirst) {
        canreach_nochargers[origin][i] = true;
    }
    for (auto x : graph[i]) {
        dfs_nochargers_4(x, origin, false);
    }
}

vector<int> who_wins_4(vector<int> a, vector<int> r, vector<int> u, vector<int> v) {
    owner = a; // {0, 0, 0, ...}
    charging = r;
    graph = vector<vector<int>>(a.size());
    for (int i = 0; i != u.size(); ++i) {
        graph[u[i]].push_back(v[i]);
    }

    vector<int> out(a.size(), 1);
    canreach = vector<vector<int>>(a.size(), vector<int>(a.size(), false));
    canreach_nochargers = vector<vector<int>>(a.size(), vector<int>(a.size(), false));
    for (int i = 0; i != a.size(); ++i) {
        dfs_4(i, i, true);
        dfs_nochargers_4(i, i, true);
    }

//    for (int i = 0; i != a.size(); ++i) {
//        cout << i << ": {";
//        for (auto x : canreach[i]) {
//            cout << x << ", ";
//        }
//        cout << "}\n";
//    }

    vector<int> cycle_nodes;
    for (int i = 0; i != a.size(); ++i) {
        if (canreach_nochargers[i][i]) {
            cycle_nodes.push_back(i);
        }
    }

    for (int i = 0; i != a.size(); ++i) {
        for (auto x : cycle_nodes) {
            if (canreach[i][x]) {
                out[i] = 0;
            }
        }
    }

    return out;
}

vector<int> who_wins(vector<int> a, vector<int> r, vector<int> u, vector<int> v) {
    bool allZero = true;
    bool allOne = true;

    for (auto x : a) {
        if (x == 0) {
            allOne = false;
        } else {
            allZero = false;
        }
    }

    bool allEasy = true;
    for (int i = 0; i != u.size(); ++i) {
        if (u[i] != v[i] && u[i] + 1 != v[i]) {
            allEasy = false;
        }
    }

    if (allOne) {
        return who_wins_3(a, r, u, v);
    } else if (allZero) {
        return who_wins_4(a, r, u, v);
    } else if (allEasy) {
        return who_wins_1(a, r, u, v);
    } else {
        return who_wins_2(a, r, u, v);
    }
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
