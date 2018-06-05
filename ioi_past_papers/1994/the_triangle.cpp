#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
    vector<vector<int>> triangle(n);
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != (i + 1); ++j) {
            int x;
            cin >> x;
            triangle[i].push_back(x);
        }
    }

    vector<vector<int>> dp(n, vector<int>(n));
    dp[0][0] = triangle[0][0];
    for (int row = 1; row != n; ++row) {
        for (int pos = 0; pos != (row + 1); ++pos) {
            int best = 0;
            if (pos != 0) {
                best = max(best, dp[row - 1][pos - 1] + triangle[row][pos]);
            }
            if (pos != n - 1) {
                best = max(best, dp[row - 1][pos] + triangle[row][pos]);
            }
            dp[row][pos] = best;
        }
    }
    cout << *max_element(dp.back().begin(), dp.back().end());
}
