#include <bits/stdc++.h>

using namespace std;

struct skip {
    int g;
    int i;
    int cnt;
};

vector<vector<skip>> dp;
vector<vector<int>> groups;
vector<int> lookup;

int N, L, M;

void solve_group(int g) {
    int pos = groups[g].front();
    int start = groups[g].front();
    if (dp[g].size() != groups[g].size()) {
        dp[g] = vector<skip>(groups[g].size(), {-1, -1, -1});
    }
    vector<vector<int>> prev(groups[g].size());
    int p1 = 0;
    int g_next = g;
    int p2 = 0;
    while (p1 != groups[g].size()) {
        while (g_next != groups.size() && groups[g_next][p2] - groups[g][p1] <= L) {
            ++p2;
            while (g_next != groups.size() && p2 == groups[g_next].size()) {
                p2 = 0;
                ++g_next;
            }
        }
        if (g_next != g) {
            vector<pair<int, skip>> todo = {{p1, {g_next, p2, 1}}};
            while (todo.size() > 0) {
                auto a = todo.back();
                todo.pop_back();
                dp[g][a.first] = a.second;
                ++a.second.cnt;
                for (auto x : prev[a.first]) {
                    todo.push_back({x, a.second});
                }
            }
        } else {
            prev[p2].push_back(p1);
        }
        ++p1;
    }
}

void build_groups() {
    vector<vector<int>> new_groups;
    new_groups.push_back({});
    for (int g = 0; g != groups.size(); ++g) {
        for (auto x : groups[g]) {
            if (new_groups.back().size() * new_groups.back().size() > N) {
                new_groups.push_back({});
            }
            new_groups.back().push_back(x);
        }
    }
    groups = new_groups;
}

void print_groups() {
    cout << "groups = {";
    for (auto g : groups) {
        cout << "{";
        for (auto x : g) {
            cout << x << ", ";
        }
        cout << "}, ";
    }
    cout << "}\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> L >> M;
//
//    if (N > 100) {
//        return 0;
//    }

    vector<int> positions(N);
    lookup = vector<int>(N);
    for (int i = 0; i != N; ++i) {
        int x;
        cin >> x;
        lookup[i] = x;
        positions[i] = x;
    }
    sort(positions.begin(), positions.end());
    groups = {positions};
    build_groups();
    dp = vector<vector<skip>>(groups.size());
    for (int g = 0; g != groups.size(); ++g) {
        solve_group(g);
    }
    int cnt = 0;
    for (int q = 0; q != M; ++q) {
        if (cnt * cnt > N) {
//            cout << "rebuilding\n";
            build_groups();
            for (int g = 0; g != groups.size(); ++g) {
                solve_group(g);
            }
            cnt = 0;
        }
        ++cnt;
        int i, y;
        cin >> i >> y;
        auto pos = lookup[i];
        int old_group = lower_bound(groups.begin(), groups.end(), pos, [&](const vector<int>& x, int val) { return x.back() < val; }) - groups.begin();
        if (old_group == groups.size()) {
            return 1;
        }
        lookup[i] = y;
//        cout << "old_pos = " << pos << ", old_group = " << old_group << ", new_group = " << new_group << "\n";
        for (int i = 0; i != groups[old_group].size(); ++i) {
            if (groups[old_group][i] == pos) {
                groups[old_group].erase(groups[old_group].begin() + i);
                break;
            }
        }

        int new_group = lower_bound(groups.begin(), groups.end(), y, [&](const vector<int>& x, int val) { return x.back() < val; }) - groups.begin();
        if (new_group == groups.size()) {
            --new_group;
        }
        if (groups[new_group].size() == 0 || groups[new_group].back() <= y) {
            groups[new_group].push_back(y);
        } else {
            for (int i = 0; i != groups[new_group].size(); ++i) {
                if (groups[new_group][i] > y) {
                    groups[new_group].insert(groups[new_group].begin() + i, y);
                    break;
                }
            }
        }
//        if (groups[old_group].size() == 0) {
//            cout << "emptied\n";
//            return 0;
//        }
//        cout << "groups modified\n";
//        print_groups();
        solve_group(old_group);
        do {
            --old_group;
        } while (old_group > 0 && groups[old_group].size() == 0);
        if (old_group >= 0) {
            solve_group(old_group);
        }

        solve_group(new_group);
        do {
            --new_group;
        } while (new_group > 0 && groups[new_group].size() == 0);
        if (new_group >= 0) {
            solve_group(new_group);
        }

        int out = 0;
        skip state = {0, 0, 0};
        while (0 == groups[state.g].size()) {
            ++state.g;
        }
        while (state.g != groups.size()) {
//            cout << state.g << ", " << state.i << "\n";
            state = dp[state.g][state.i];
//            if (state.i >= groups[state.g].size()) {
////                cout << "err " << state.i << "\n";
//                return 0;
//            }
            out += state.cnt;
        }
        cout << out << "\n";
    }
}
