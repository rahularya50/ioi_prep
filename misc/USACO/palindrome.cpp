#include <bits/stdc++.h>

using namespace std;

array<array<int, 5000>, 5000> dp;

int go(int i, int j, const vector<char>& inp) {
    if (dp[i][j] != -1) {
        return dp[i][j];
    }
    if (i >= j) {
        return 0;
    }
    if (inp[i] == inp[j]) {
        return go(i + 1, j - 1, inp);
    }
    dp[i][j] = min(go(i, j - 1, inp), go(i + 1, j, inp)) + 1;
    return dp[i][j];
}

int main() {
    int N;
    vector<char> inp;
    cin >> N;
    for (int i = 0; i != N; ++i) {
        char temp;
        cin >> temp;
        inp.push_back(temp);
    }
    for (int i = 0; i != N; ++i) {
        for (int j = 0; j != N; ++j) {
            dp[i][j] = -1;
        }
    }
    cout << go(0, N, inp);
}
