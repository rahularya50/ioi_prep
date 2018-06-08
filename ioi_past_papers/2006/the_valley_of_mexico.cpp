#include <bits/stdc++.h>

using namespace std;

int C, N;
vector<vector<bool>> graph;
vector<vector<int>> dp;

const int UNDEF = -1;
const int IMPOSSIBLE = -2;
const int END = -3;

int go(int start, int delta, bool print) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int dp_delta = delta + C;
    if (print) {
//        cout << start << " " << delta << "\n";
    }
    if (dp[start][dp_delta] != UNDEF && !print) {
        return dp[start][dp_delta];
    }
    if (delta == 0) {
        return END;
    }
    int delta_sign = (delta > 0) * 2 - 1;
    int target_1 = (start + delta_sign + C) % C;
    int target_2 = (start + delta + C) % C;
    if (graph[start][target_1] && go(target_1, delta_sign * (abs(delta) - 1), false) != IMPOSSIBLE) {
        dp[start][dp_delta] = target_1;
        if (print) {
            cout << target_1+1 << "\n";
            go(target_1, delta_sign * (abs(delta) - 1), true);
        }
        return target_1;
    }
    if (graph[start][target_2] && go(target_2, -delta_sign * (abs(delta) - 1), false) != IMPOSSIBLE) {
        dp[start][dp_delta] = target_2;
        if (print) {
            cout << target_2+1 << "\n";
            go(target_2, -delta_sign * (abs(delta) - 1), true);
        }
        return target_2;
    }
    dp[start][dp_delta] = IMPOSSIBLE;
    return IMPOSSIBLE;
}

int main() {
    cin >> C >> N;
    graph = vector<vector<bool>>(C, vector<bool>(C, false));
    for (int i = 0; i != N; ++i) {
        int x, y;
        cin >> x >> y;
        graph[x - 1][y - 1] = true;
        graph[y - 1][x - 1] = true;
    }
    dp = vector<vector<int>>(C, vector<int>(2 * C, -1));

    for (int i = 0; i != C; ++i) {
        if (go(i, C - 1, false) != IMPOSSIBLE) {
            cout << i + 1 << "\n";
            go(i, C - 1, true);
            return 0;
        }
    }

    cout << -1 << "\n";
}
