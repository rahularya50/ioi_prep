#include <bits/stdc++.h>

using namespace std;

int go(int R, int B, int next_to_get, int min_next, vector<int>& mins, vector<vector<vector<vector<int>>>>& dp) {
//    cout << R << " " << B << " " << next_to_get << " " << min_next << "\n";
    if (R == 0 && B == 0) {

        return 0;
    }

    if (next_to_get > R) {

        return 0;
    }

    if (dp[R][B][min_next][next_to_get] != -1) {
//        cout << "\n" << dp[R][B][min_next][next_to_get] << "\n";
        return dp[R][B][min_next][next_to_get];
    }

    int best = 0;
    if (min_next <= B) {
        ++mins[next_to_get];
//        cout << "first recur\n";
        best = max(best, 1 + go(R - next_to_get, B - min_next, next_to_get, mins[next_to_get], mins, dp));
        --mins[next_to_get];
    }
    if (next_to_get != R) {
//        cout << "second recur\n";
        best = max(best, go(R, B, next_to_get + 1, mins[next_to_get + 1], mins, dp));
    }

    dp[R][B][min_next][next_to_get] = best;

//    cout << "ret";
    return best;
}

int main() {
    int T;
    cin >> T;
    for (int t = 0; t != T; ++t) {
        int R, B;
        cin >> R >> B;
        int big = max(R, B) + 2;
        cout << "Case #" << (t + 1) << ": ";
        vector<int> mins(R + 1, 0);
        vector<vector<vector<vector<int>>>> dp(big, vector<vector<vector<int>>>(big, vector<vector<int>>(big, vector<int>(big, -1))));
//        map<pair<pair<int, int>, vector<int>>, int> cache;
        mins[0] = 1;
        cout << go(R, B, 0, 1, mins, dp) << "\n";
    }
}
