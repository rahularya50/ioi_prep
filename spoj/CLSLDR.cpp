#include <bits/stdc++.h>

using namespace std;

const int SIZE = 10*10*10 + 3;
using X = vector<vector<int>>; //array<array<int, SIZE>, SIZE>;
X dp(SIZE, vector<int>(SIZE, -1));


int go(int n, int o, X& dp) {
//    cout << n << " " << o << "\n";
    if (n == 1) {
        return 0;
    }
    if (dp[n][o] != -1) {
//        cout << n << " " << o << "\n";
//        cout << "cache: " << dp[n][o] << "\n";
        return dp[n][o];
    }
    int a = go(n - 1, o, dp);
    int b = (a + o) % n;
    if (b == (o % n)) {
        b = (o + n - 1) % n;
    }
    dp[n][o] = b;
//    cout << "ret: " << b << "\n";
    return dp[n][o];

//    if (a + o < n) {
//        dp[n][o] = a + o;
//        cout << "ret1: " << dp[n][o] << "\n";
//        return dp[n][o];
//    } else {
//        dp[n][o] = (a + 1) % n;
//        cout << "ret2: " << a << " -> " << (a + 1) % n << "\n";
//        return (a + 1) % n;
//    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
//    for (auto &x : dp) {
//        for (auto &y : x) {
//            y = -1;
//        }
//    }
    for (int t = 0; t != T; ++t) {
        int n, m, o;
        cin >> n >> m >> o;
        cout << (m + go(n, o, dp) - 1) % n + 1 << "\n";
    }
}
