#include <bits/stdc++.h>

using namespace std;

struct segment {
    long long left;
    long long m;
    long long c;
    int i;
};

long long x_intersect(segment a, segment b) {
    return (b.c - a.c - 1LL) / (a.m - b.m) + 1LL;
}

void insert_seg(segment seg, vector<segment>& hull) {
    while (hull.size() > 0 && x_intersect(seg, hull.back()) < hull.back().left) {
        hull.pop_back();
    }
    if (hull.size() > 0) {
        seg.left = x_intersect(seg, hull.back());
    }
    hull.push_back(seg);
}

long long hull_lookup(long long x, vector<segment>& hull) {
    if (hull.size() == 0) {
        return 0; // when initializing K = 0
    }

    auto curr_seg = upper_bound(hull.begin(), hull.end(), x, [](long long a, segment b){ return a < b.left; });
    advance(curr_seg, -1);
    return (*curr_seg).m * x + (*curr_seg).c;
}

int main() {
    ios::sync_with_stdio(false);

    int N, K;
    cin >> N >> K;
    vector<int> A;
    A.reserve(N);
    for (int i = 0; i != N; ++i) {
        int temp;
        cin >> temp;
        A.push_back(temp);
    }

    vector<long long> S;
    S.reserve(N);
    long long run_sum = 0;
    for (auto x : A) {
        run_sum += x;
        S.push_back(run_sum);
    }

    vector<long long> T;
    T.reserve(N);
    long long run_prod = 0;
    for (long long i = 0; i != N; ++i) {
        run_prod += i * A[i];
        T.push_back(run_prod);
    }

    vector<vector<segment>> hulls(K + 1);
    vector<vector<long long>> dp(K + 1, vector<long long>(N));

    for (int i = 0; i != N; ++i) {
        for (int k = 1; k <= K; ++k) {
            dp[k][i] = T[i] + hull_lookup(S[i], hulls[k - 1]);
            segment new_seg = {-1, -(i + 1), (i + 1) * S[i] - T[i] + dp[k][i], i};
            insert_seg(new_seg, hulls[k]);
        }
    }

    cout << dp[K][N - 1];
}
