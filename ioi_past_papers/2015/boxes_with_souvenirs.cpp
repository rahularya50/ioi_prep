#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long N, K, L;
    cin >> N >> K >> L;
    vector<long long> pos(N);
    for (auto& x : pos) {
        cin >> x;
    }
//    cout << "dps built\n";

    vector<long long> l_dp(N);
    for (long long i = 0; i != N; ++i) {
        long long curr = 2 * pos[i];
        if (i >= K) {
            curr += l_dp[i - K];
        }
        l_dp[i] = curr;
    }

    vector<long long> r_dp(N);
    for (long long i = N - 1; i >= 0; --i) {
        long long curr = 2 * (L - pos[i]);
        if (i + K < N) {
            curr += r_dp[i + K];
        }
        r_dp[i] = curr;
    }


    long long best = numeric_limits<long long>::max();

    for (long long i = 0; i != N; ++i) {
        long long s_i = i;
        long long e_i = min(i + K - 1, N - 1);
        long long curr = L;
        if (s_i != 0) {
            curr += l_dp[s_i - 1];
        }
        if (e_i != N - 1) {
            curr += r_dp[e_i + 1];
        }
        best = min(best, curr);
    }

    for (int i = 0; i != N - 1; ++i) {
        best = min(best, r_dp[i + 1] + l_dp[i]);
//        cout << best << "\n";
    }

//    cout << best << "\n";
    best = min(best, l_dp[N - 1]);
    best = min(best, r_dp[0]);

    cout << best << "\n";
}
