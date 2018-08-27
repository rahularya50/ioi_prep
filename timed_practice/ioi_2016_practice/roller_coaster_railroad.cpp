#include "bits/stdc++.h"

using namespace std;

vector<long long> dp;
vector<int> S;
vector<int> T;

int N;

int encode(int visited, int prev) {
    return (visited << 4) + prev;
}

struct ret {
    int visited;
    int prev;
};

ret decode(int val) {
    return {val / 16, val % 16};
}

long long go(const int visited, const int prev) {
    if (visited == (1 << N) - 1) {
        return 0;
    }
    if (prev != -1 && dp[encode(visited, prev)] != -1) {
        return dp[encode(visited, prev)];
    }

    int t_prev = (prev == -1) ? 1 : T[prev];

    long long out = numeric_limits<long long>::max();
    for (int i = 0; i != N; ++i) {
        if (visited & (1 << i)) {
            continue;
        }
        long long curr = max(t_prev - S[i], 0);
        int new_visited = visited + (1 << i);
        curr += go(new_visited, i);
        out = min(out, curr);
    }

    if (prev != -1) {
        dp[encode(visited, prev)] = out;
    }
    return out;
}

long long plan_roller_coaster(vector<int> s, vector<int> t) {
    S = s;
    T = t;
    N = s.size();
    dp = vector<long long>(1 << 20, -1);
    return go(0, -1);
}
//
//int main() {
//    int n;
//    cin >> n;
//    vector<int> s(n);
//    vector<int> t(n);
//    for (int i = 0; i != n; ++i) {
//        cin >> s[i] >> t[i];
//    }
//    cout << plan_roller_coaster(s, t);
//}
