#include <bits/stdc++.h>

using namespace std;

int gcd = 2520;

pair<int, int> go(int i, int lbuff, const vector<int>& dists, vector<vector<int>>& dp, bool traceback, bool skipCache) {
    if (lbuff < 0 || lbuff >= 3 * gcd) {
        return {gcd * 5, 0};
    }
    if (i == dists.size()) {
        return {0, 0};
    }
    if (dp[i][lbuff] != -1 && !traceback && !skipCache) {
        return {dp[i][lbuff], 0};
    }
    pair<int, int> a = {go(i + 1, lbuff + dists[i], dists, dp, false, false).first + dists[i], 1};
    pair<int, int> b = {max(0, go(i + 1, lbuff - dists[i], dists, dp, false, false).first - dists[i]), -1};

    dp[i][lbuff] = min(a.first, b.first);

    if (traceback) {
        if (a < b) {
            cout << "u";
            go(i + 1, lbuff + dists[i], dists, dp, true, false);
        } else {
            cout << "d";
            go(i + 1, lbuff - dists[i], dists, dp, true, false);
        }
    }

//    cout << i << " " << lbuff << " " << dp[i][lbuff] << "\n";
    return min(a, b);
}

int main() {
    int N;
    cin >> N;
    vector<int> dists;
    for (int i = 0; i != N; ++i)
    {
        int temp;
        cin >> temp;
        dists.push_back(gcd / temp);
    }

    int pos;
    pair<int, int> best = {-1, 0};
    vector<vector<int>> dp(N, vector<int>(3*gcd, -1));

    for (int lbuff = 0; lbuff != 3*gcd; ++lbuff) {
        auto x = go(0, lbuff, dists, dp, false, true);
        pair<int, int> c = {x.first + lbuff, x.second};
        if (best.first == -1 || best > c) {
            best = c;
            pos = lbuff;
        }
    }
    go(0, pos, dists, dp, true, false);
}
