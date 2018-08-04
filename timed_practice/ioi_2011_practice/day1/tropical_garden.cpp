#include <bits/stdc++.h>

using namespace std;

vector<vector<long long>> graph;

using dat = pair<long long, bool>;

// dat.second == did I arrive via the best edge?

// how long it takes to get to "P"
vector<dat> dp_restrict; // arrived via most beautiful edge
vector<dat> dp; // arrived via another edge

long long N, M, P;

long long UNKNOWN = -1;
long long INPROGRESS = -2;
long long NEVER = -3;

dat calc(long long);
dat calc_restrict(long long);

dat calc(long long i) {
//    cout << "Arriving at " << i << " via the second-most beautiful road!\n";
    if (i == P) {
        return {0, false};
    } else if (dp[i].first == UNKNOWN) {
        // solve for it
        dp[i].first = INPROGRESS;
        long long dest = graph[i].front();
        dat ans;
        if (i == graph[dest].front()) {
            // we're arriving via the most beautiful edge of the destination
            ans = calc_restrict(dest);
        } else {
            ans = calc(dest);
        }
        if (ans.first == NEVER) {
            dp[i].first = NEVER;
        } else {
            dp[i] = {ans.first + 1, ans.second};
        }
        return dp[i];
    } else if (dp[i].first == INPROGRESS) {
        dp[i].first = NEVER;
        return dp[i];
    } else {
        return dp[i];
    }
}

dat calc_restrict(long long i) {
//    cout << "Arriving at " << i << " via the most beautiful road!\n";
    if (i == P) {
        return {0, true};
    } else if (dp_restrict[i].first == UNKNOWN) {
        // solve for it
        dp_restrict[i].first = INPROGRESS;
        long long dest = graph[i].back(); // take the second most beautiful edge, or the most beautiful edge if there's no alternative
        dat ans;
        if (i == graph[dest].front()) {
            // we're arriving via the most beautiful edge of the destination
            ans = calc_restrict(dest);
        } else {
            ans = calc(dest);
        }
        if (ans.first == NEVER) {
            dp_restrict[i].first = NEVER;
        } else {
            dp_restrict[i] = {ans.first + 1, ans.second};
        }
        return dp_restrict[i];
    } else if (dp_restrict[i].first == INPROGRESS) {
        dp_restrict[i].first = NEVER;
        return dp_restrict[i];
    } else {
        return dp_restrict[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M >> P;

    graph = vector<vector<long long>>(N);

    for (long long i = 0; i != M; ++i) {
        long long x, y;
        cin >> x >> y;
        if (graph[x].size() < 2) {
            graph[x].push_back(y);
        }
        if (graph[y].size() < 2) {
            graph[y].push_back(x);
        }
    }

    dp = vector<dat>(N, {UNKNOWN, 0});
    dp_restrict = vector<dat>(N, {UNKNOWN, 0});

    for (long long i = 0; i != N; ++i) {
//        cout << "calc(" << i << ") = {" << calc(i).first << ", " << calc(i).second << "}" << "\n";
//        cout << "calc_restrict(" << i << ") = {" << calc_restrict(i).first << ", " << calc_restrict(i).second << "}" << "\n";

        calc(i);
        calc_restrict(i);
    }

    long long Q;
    cin >> Q;

    vector<long long> G(Q);
    for (auto& x : G) {
        cin >> x;
    }

    dat mod;
    if (P == graph[graph[P].front()].front()) {
        mod = calc_restrict(graph[P].front());
    } else {
        mod = calc(graph[P].front());
    }
    dat mod_restrict;
    if (P == graph[graph[P].back()].front()) {
        mod_restrict = calc_restrict(graph[P].back());
    } else {
        mod_restrict = calc(graph[P].back());
    }
    if (mod.first != NEVER) {
        ++(mod.first);
    }
    if (mod_restrict.first != NEVER) {
        ++(mod_restrict.first);
    }

    // second means I end up at the same one
    mod.second = !mod.second; // EWWW

//    cout << "mod = {" << mod.first << ", " << mod.second << "}\n";
//    cout << "mod_restrict = {" << mod_restrict.first << ", " << mod_restrict.second << "}\n";

    map<long long, long long> specials;
    map<long long, vector<long long>> loop_1st; // period = mod_restrict.first
    map<long long, vector<long long>> loop_2nd; // period = mod.first
    map<long long, vector<long long>> loop_both; // period = mod.first + mod_restrict.first

    for (long long i = 0; i != N; ++i) {
        if (i == P) {
            dp[i] = {0, 0};
        }
//        cout << "Considering origin = " << i << "\n";
        if (dp[i].first == NEVER) {
            continue;
        }

        map<long long, vector<long long>> *loop1_ptr, *loop2_ptr;

        dat x1, x2;
        if (dp[i].second) {
            x2 = mod;
            x1 = mod_restrict;
            loop1_ptr = &loop_1st; // period = x1.first
            loop2_ptr = &loop_2nd; // period = x2.first
        } else {
            x1 = mod;
            x2 = mod_restrict;
            loop1_ptr = &loop_2nd; // period = x1.first
            loop2_ptr = &loop_1st; // period = x2.first
        }

        map<long long, vector<long long>>& loop1 = *loop1_ptr;
        map<long long, vector<long long>>& loop2 = *loop2_ptr;

        if (x1.first == NEVER) {
//            cout << "Route1 = " << dp[i].first << ".\n";
            ++specials[dp[i].first];
        } else if (x1.second == true) {
//            cout << "Route2 = " << dp[i].first << " % " << x1.first << ".\n";
            loop1[dp[i].first % x1.first].push_back(dp[i].first); // period = x1.first
        } else if (x2.first == NEVER) {
//            cout << "Route3 = " << dp[i].first << ".\n";
//            cout << "Route3 = " << dp[i].first + x1.first << ".\n";
            ++specials[dp[i].first];
            ++specials[dp[i].first + x1.first];
        } else if (x2.second == true) {
//            cout << "Route4 = " << dp[i].first << ".\n";
            ++specials[dp[i].first];
//            cout << "Route4 = " << dp[i].first + x1.first << " % " << x2.first << ".\n";
            loop2[(dp[i].first + x1.first) % x2.first].push_back(dp[i].first + x1.first);
        } else {
//            cout << "Route5 = " << dp[i].first << " % " << (x1.first + x2.first) << ".\n";
            loop_both[dp[i].first % (x1.first + x2.first)].push_back(dp[i].first);
//            cout << "Route5 = " << (dp[i].first + x1.first) << " % " << (x1.first + x2.first) << ".\n";
            loop_both[(dp[i].first + x1.first) % (x1.first + x2.first)].push_back(dp[i].first + x1.first);
        }
    }

    for (auto& x : loop_1st) {
        sort(x.second.begin(), x.second.end());
    }
    for (auto& x : loop_2nd) {
        sort(x.second.begin(), x.second.end());
    }
    for (auto& x : loop_both) {
        sort(x.second.begin(), x.second.end());
    }

    for (auto k : G) {
        if (k == 0) {
            cout << 1 << " ";
            continue;
        }
        long long out = 0;

        out += specials[k];

        if (mod_restrict.first != NEVER) {
            auto iter_1st = upper_bound(loop_1st[k % mod_restrict.first].begin(), loop_1st[k % mod_restrict.first].end(), k);
            out += distance(loop_1st[k % mod_restrict.first].begin(), iter_1st);
        }

        if (mod.first != NEVER) {
            auto iter_2nd = upper_bound(loop_2nd[k % mod.first].begin(), loop_2nd[k % mod.first].end(), k);
            out += distance(loop_2nd[k % mod.first].begin(), iter_2nd);
        }

        if (mod.first != NEVER && mod_restrict.first != NEVER) {
            long long x = mod.first + mod_restrict.first;
            auto iter_both = upper_bound(loop_both[k % x].begin(), loop_both[k % x].end(), k);
            out += distance(loop_both[k % x].begin(), iter_both);
        }

        cout << out << " ";
    }
}
