#include <bits/stdc++.h>

using namespace std;

using T = vector<vector<vector<int>>>;

int go(int lpos, int rpos, int wdelta, T& dp, const vector<bool>& left_w, const vector<bool>& right_w) {
    int N = left_w.size();

    int rdelta = rpos - lpos + 2;
    int wlookup = wdelta + N;

    if (rdelta > 4 || rdelta < 0) {
        return 100000;
    }

    if (lpos == N - 1 && rpos == N - 1) {
        return abs(wdelta);
    }

    if (dp[wlookup][lpos][rdelta] != -1) {
        return dp[wlookup][lpos][rdelta];
    }

    int out = 100000;

    for (int new_r = rpos + 1; (new_r - lpos) <= 2 && new_r < N; ++new_r) {
        int temp = 1 + go(lpos, new_r, wdelta + right_w[new_r], dp, left_w, right_w);
        if (wdelta < 0) {
            temp += right_w[new_r];
        }
        out = min(out, temp);
    }

    for (int new_l = lpos + 1; (new_l - rpos) <= 2 && new_l < N; ++new_l) {
        int temp = 1 + go(new_l, rpos, wdelta - left_w[new_l], dp, left_w, right_w);
        if (wdelta > 0) {
            temp += left_w[new_l];
        }
        out = min(out, temp);
    }

//    cout << "ret\n";
//    cout << "pos=(" << lpos << ", " << rpos << "), wlookup=" << wlookup << ", rdelta = " << rdelta << "\n";

    dp[wlookup][lpos][rdelta] = out;
    return dp[wlookup][lpos][rdelta];
}

int main() {
    int N;
    cin >> N;

    vector<bool> left_wet;
    left_wet.reserve(N);
    for (int i = 0; i != N; ++i) {
        char x;
        cin >> x;
        left_wet.push_back(x == 'W');
    }

    vector<bool> right_wet;
    right_wet.reserve(N);
    for (int i = 0; i != N; ++i) {
        char x;
        cin >> x;
        right_wet.push_back(x == 'W');
    }

    T dp(2*N + 1, vector<vector<int>>(N, vector<int>(5, -1)));

    cout << min(left_wet[0], right_wet[0]) + go(0, 0, right_wet[0] - left_wet[0], dp, left_wet, right_wet);
}
