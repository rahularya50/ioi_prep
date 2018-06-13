#include <bits/stdc++.h>

using namespace std;

vector<vector<long long>> graph;
vector<pair<long long, bool>> dp[2]; // {{dist, is_arriving_via_best}}

const long long UNKNOWN = -1; // should never be returned
const long long INPROGRESS = -2; // should never be returned
const long long IMPOSSIBLE = -3;

long long N, M, P;

pair<long long, bool> go_best(long long);
pair<long long, bool> go_nonbest(long long);

// coming via best
pair<long long, bool> go(long long i, bool viabest, bool startP) {
    if (!startP && i == P) {
        return {0, viabest};
    }
    if (dp[viabest][i].first == INPROGRESS) {
        dp[viabest][i].first = IMPOSSIBLE;
        return {IMPOSSIBLE, -1};
    }
    if (dp[viabest][i].first != UNKNOWN) {
        return dp[viabest][i];
    }

    dp[viabest][i] = {INPROGRESS, -1};

    pair<long long, bool> x;
    long long dest;
    if (!viabest || graph[i].size() == 1) {
        dest = graph[i][0];
    } else {
        dest = graph[i][1];
    }

    if (i == graph[dest][0]) {
        // going via best of them
        x = go(dest, true, false);
    } else {
        x = go(dest, false, false);
    }

    if (x.first == IMPOSSIBLE) {
        dp[viabest][i].first = IMPOSSIBLE;
    } else {
        dp[viabest][i] = {x.first + 1, x.second};
    }

    return dp[viabest][i];
}

int main() {
//    long long N, M, P;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M >> P;
    graph = vector<vector<long long>>(N);

    for (long long i = 0; i != M; ++i) {
        long long a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dp[0] = vector<pair<long long, bool>>(N, {UNKNOWN, -1});
    dp[1] = vector<pair<long long, bool>>(N, {UNKNOWN, -1});

    for (long long i = 0; i != N; ++i) {
        go(i, false, false);
    }

    pair<long long, long long> r[2] = {go(P, false, true), go(P, true, true)};
//
//    for (long long i = 0; i != N; ++i) {
//        cout << "dp[false][" << i << "] = {" << dp[0][i].first << ", " << dp[0][i].second << "} \n";
//        cout << "dp[true][" << i << "] = {" << dp[1][i].first << ", " << dp[1][i].second << "} \n";
//    }

    long long Q;
    cin >> Q;
    vector<long long> G(Q);
    for (long long i = 0; i != Q; ++i) {
        long long x;
        cin >> x;
        G[i] = x;
    }

    vector<long long> out(Q);

    for (int state = 0; state != 2; ++state) {
//        cout << "Considering state = " << state << "\n";
        if (r[state].first < 0) {
            map<long long, long long> raw_cnt;
            for (long long i = 0; i != N; ++i) {
                if (dp[false][i].second != state || dp[false][i].first < 0) {
                    continue;
                }
                ++raw_cnt[dp[false][i].first];
            }
//            cout << "vals built\n";
            for (long long q = 0; q != Q; ++q) {
                out[q] += raw_cnt[G[q]];
            }
        } else if (r[state].second == state) {
            long long mod = r[state].first;
            vector<vector<long long>> vals(mod);
            for (long long i = 0; i != N; ++i) {
                if (dp[false][i].second != state || dp[false][i].first < 0) {
                    continue;
                }
                vals[dp[false][i].first % mod].push_back(dp[false][i].first);
            }
            for (long long i = 0; i != mod; ++i) {
                sort(vals[i].begin(), vals[i].end());
            }
            for (long long q = 0; q != Q; ++q) {
                long long cong = G[q] % mod;
                long long num = upper_bound(vals[cong].begin(), vals[cong].end(), G[q]) - vals[cong].begin();
                out[q] += num;
            }
        } else if (r[state].second != state) {
            if (r[1 - state].first < 0) {
                map<long long, long long> raw_cnt;
                for (long long i = 0; i != N; ++i) {
                    if (dp[false][i].second != state || dp[false][i].first < 0) {
                        continue;
                    }
                    ++raw_cnt[dp[false][i].first];
                    ++raw_cnt[dp[false][i].first + r[state].first];
                }
    //            cout << "vals built\n";
                for (long long q = 0; q != Q; ++q) {
                    out[q] += raw_cnt[G[q]];
                }
            } else if (r[1 - state].second != state) {
    //            cout << "Case 2\n";
                long long mod = r[1 - state].first;
                vector<vector<long long>> vals(mod);
                map<long long, long long> raw_cnt;
                for (long long i = 0; i != N; ++i) {
                    if (dp[false][i].second != state || dp[false][i].first < 0) {
                        continue;
                    }
                    vals[(dp[false][i].first + r[state].first) % mod].push_back(dp[false][i].first + r[state].first);
                    ++raw_cnt[dp[false][i].first];
                }
                for (long long i = 0; i != mod; ++i) {
                    sort(vals[i].begin(), vals[i].end());
                }
    //            cout << "vals built\n";
                for (long long q = 0; q != Q; ++q) {
    //                cout << "Considering G[" << q << "] = " << G[q] << "\n";
                    long long cong = G[q] % mod;
                    long long num = upper_bound(vals[cong].begin(), vals[cong].end(), G[q]) - vals[cong].begin();
                    out[q] += num;
                    out[q] += raw_cnt[G[q]];
                }
            } else {
                long long mod = r[state].first + r[1 - state].first;
                vector<vector<long long>> vals(mod);
                for (long long i = 0; i != N; ++i) {
                    if (dp[false][i].second != state || dp[false][i].first < 0) {
                        continue;
                    }
                    vals[dp[false][i].first % mod].push_back(dp[false][i].first);
                    vals[(dp[false][i].first + r[state].first) % mod].push_back(dp[false][i].first + r[state].first);
                }
                for (long long i = 0; i != mod; ++i) {
                    sort(vals[i].begin(), vals[i].end());
                }
                for (long long q = 0; q != Q; ++q) {
                    long long cong = G[q] % mod;
                    long long num = upper_bound(vals[cong].begin(), vals[cong].end(), G[q]) - vals[cong].begin();
                    out[q] += num;
                }
            }
        }
    }

    for (auto x : out) {
        cout << x << " ";
    }
}
