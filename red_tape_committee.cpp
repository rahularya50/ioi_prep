#include <bits/stdc++.h>

using namespace std;

int go(int upto, int targetsize, int targetyeses, vector<vector<vector<double>>>& dp, const vector<double>& P) {
    if (upto == 0) {
        if (targetsize == 0 && targetyeses == 0) {
            return 1;
        }
        return 0;
    }
    double best = go(upto - 1, targetsize, targetyeses, dp, P);
    best = max(best, go(upto - 1, targetsize - 1))
}

int main() {
    int T;
    cin >> T;
    for (int t = 0; t != T; ++t) {
        int N, K;
        cin >> N >> K;
        vector<double> P(N);
        for (int i = 0; i != N; ++i) {
            double temp;
            cin >> temp;
            P[i] = temp;
        }
        vector<vector<vector<double>>> dp(N + 1, K + 1, K / 2 + 1); // dp[up to][committee size][target #yeses]
        go(N, K, K / 2, dp, P);
    }
}
