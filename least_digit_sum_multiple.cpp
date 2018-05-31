#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<vector<pair<int, pair<int, int>>>> dp; // [row][modulus] -> {min_sum, {first_digit, old_mod}}
    dp.push_back({});
    dp.push_back(vector<pair<int, pair<int, int>>>(N));
    for (int i = 1; i != 10 && i <= N; ++i) {
        dp[1][i % N] = {i, {i, 0}};
    }

    int best = numeric_limits<int>::max();
    int bestlen = 1;

    if (N < 10) {
        best = N;
    }

    bool improving = true;

    int len = 1;
    int tenpow = 1;
    while (improving) {
        ++len;
//        cout << "loop\n";
        tenpow *= 10;
        tenpow %= N;
        dp.push_back(dp.back());
        for (int i = 0; i != N; ++i) {
            if (dp[len][i].first != 0) {
                dp[len][i].second.first = 0;
                dp[len][i].second.second = i;
//                cout << "dp[" << len << "][" << i << "] = {" << dp[len][i].first << ", {" << dp[len][i].second.first << ", " << dp[len][i].second.second << "}}" << "\n";
            }
        }
        improving = false;
        for (int i = 0; i != 10; ++i) {
            for (int j = 0; j != N; ++j) {
                if ((j != 0 && dp[len - 1][j].first == 0) || (j == 0 && i == 0)) {
                    continue;
                }
                auto newmod = (i * tenpow + j) % N;
                auto newsum = (j == 0) ? i : (dp[len - 1][j].first + i);
                if (dp[len][newmod].first == 0 || newsum < dp[len][newmod].first) {
                    dp[len][newmod] = {newsum, {i, (j ? j : -1)}};
                    improving = true;
//                    if (j == 0) {
//                        cout << "zero ";
//                    } else {
//                        cout << "nonzero ";
//                    }
//                    cout << "dp[" << len << "][" << newmod << "] = {" << newsum << ", {" << i << ", " << (j ? j : -1) << "}}" << "\n";
                }
                if (newmod == 0 && newsum < best) {
                    best = newsum;
                    bestlen = len;
//                    cout << "New best found with sum = " << best << " and len = " << len << "\n";
                }
            }
        }
    }

//    cout << "BESTLEN : " << bestlen << "\n";

    int currmod = 0;
    while (bestlen > 0) {
//        cout << "\n currmod = " << currmod << ", digit = ";
        if (currmod == -1) {
            cout << 0;
        } else {
            cout << dp[bestlen][currmod].second.first;
            currmod = dp[bestlen][currmod].second.second;
        }
        --bestlen;
    }
}
