#include <bits/stdc++.h>

using namespace std;

struct segment {
    long long left; // first xval where it becomes useful
    long long m;
    long long c;
};

// first xval where b exceeds a i.e. b.m > a.m
long long intersect(segment a, segment b) {
//    cout << "a.m = " << a.m << ", b.m = " << b.m << "\n";
    if (a.m == b.m) {
        if (a.c > b.c) {
            return numeric_limits<int>::max();
        } else {
            return numeric_limits<int>::min();
        }
    }
    return (a.c - b.c) / (b.m - a.m) + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    long long A, B, C;
    cin >> A >> B >> C;
    vector<int> X(N);
    for (auto& x : X) {
        cin >> x;
    }

    vector<long long> S = {0};
    S.reserve(N);
    long long curr = 0;
    for (auto& x : X) {
        curr += x;
        S.push_back(curr);
    }

    vector<segment> hulls;
    hulls.push_back({0, 0, 0});
    long long dp;
    int pos = 0;
    for (int x = 0; x != N; ++x) {
        while (pos != hulls.size() - 1 && hulls[pos + 1].left <= S[x + 1]) {
            ++pos;
        }
        auto seg = hulls[pos];
        dp = seg.m * S[x + 1] + seg.c + A * S[x + 1] * S[x + 1] + B * S[x + 1] + C;
//        cout << "segval = " << seg.m * S[x + 1] + seg.c << "\n";
//        cout << "dp[" << x << "] = " << dp[x] << "\n";
        segment newseg = {0, -2LL * A * S[x + 1], A * S[x + 1] * S[x + 1] - B * S[x + 1] + dp};
        while (hulls.size() > 0 && intersect(hulls.back(), newseg) <= hulls.back().left) {
            hulls.pop_back();
        }
        if (hulls.size() != 0) {
            newseg.left = intersect(hulls.back(), newseg);
        }
        hulls.push_back(newseg);
//        cout << "hull\n";
    }
    cout << dp;
}
