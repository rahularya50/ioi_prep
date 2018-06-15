#include <bits/stdc++.h>

using namespace std;

int N;

vector<int> dp(256);
vector<int> dp_new(256);

vector<int> shipments;

int gen_hash(int mine1first, int mine1second, int mine2first, int mine2second) {
    auto x = mine1first + mine1second * 4 + mine2first * 16 + mine2second * 64;
    return x;
}

int go(int i, int prevhash) {
    int x = prevhash;
    int mine1first = prevhash % 4;
    prevhash /= 4;
    int mine1second = prevhash % 4;
    prevhash /= 4;
    int mine2first = prevhash % 4;
    prevhash /= 4;
    int mine2second = prevhash % 4;

    int food = shipments[i];
    int best = -1;
    for (int dest = 0; dest != 2; ++dest) {
        int prev1;
        int prev2;
        if (dest == 0) {
            prev1 = mine1first;
            prev2 = mine1second;
        } else {
            prev1 = mine2first;
            prev2 = mine2second;
        }
        int diffs;
        if (prev1 == 0) {
            diffs = 1;
        } else if (prev2 == 0) {
            diffs = 1 + (food != prev1);
        } else {
            if (prev1 == prev2) {
                diffs = (food != prev1) + 1;
            } else {
                if (food == prev1 || food == prev2) {
                    diffs = 2;
                } else {
                    diffs = 3;
                }
            }
        }
        if (dest == 0) {
            best = max(best, diffs + dp[gen_hash(food, prev1, mine2first, mine2second)]);
        } else {
            best = max(best, diffs + dp[gen_hash(mine1first, mine1second, food, prev1)]);
        }
    }

//    cout << best << "\n";
    dp_new[x] = best;
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N;
    shipments = vector<int>(N);
    for (auto& x : shipments) {
        char y;
        cin >> y;
        if (y == 'M') {
            x = 1;
        } else if (y == 'F') {
            x = 2;
        } else {
            x = 3;
        }
    }
    for (int i = N - 1; i >= 0; --i) {
        for (int h = 0; h != 256; ++h) {
            go(i, h);
        }
        swap(dp, dp_new);
    }
    cout << dp[0];
}
