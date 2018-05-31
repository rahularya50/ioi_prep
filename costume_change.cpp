#include <bits/stdc++.h>

using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 0; t != T; ++t) {
        int N;
        cin >>N;
        vector<vector<int>> vals(N, vector<int>(N, 0));
        for (int i = 0; i != N; ++i) {
            for (int j = 0; j != N; ++j) {
                int x;
                cin >> x;
                if (x > 0) {
                    vals[i][j] = x + N - 1;
                }
                if (x < 0) {
                    vals[i][j] = -x - 1;
                }
            }
        }


        pair<int, int> worst = {0, 0};

        int out = 0;

        while (true) {
            vector<vector<int>> counts(N, vector<int>(N, -1));

            for (int x = 0; x != N; ++x) {
                for (int y = 0; y != N; ++y) {
                    for (int x2 = 0; x2 != N; ++x2) {
                        if (vals[x][y] == vals[x2][y]) {
                            ++counts[x][y];
                        }
                    }
                    for (int y2 = 0; y2 != N; ++y2) {
                        if (vals[x][y] == vals[x][y2]) {
                            ++counts[x][y];
                        }
                    }
                    if (counts[x][y] > counts[worst.first][worst.second]) {
                        worst = {x, y};
                    }
                }
            }

            if (counts[worst.first][worst.second] == 1) {
                break;
            }

            int x = worst.first;
            int y = worst.second;

            vector<bool> present(2*N, false);
            for (int x2 = 0; x2 != N; ++x2) {
                    present[vals[x2][y]] = true;
                }
                for (int y2 = 0; y2 != N; ++y2) {
                    present[vals[x][y2]] = true;
                }

            int tv = -1;
            for (int v = 0; v != 2 * N; ++v) {
                if (!present[v]) {
                    tv = v;
                    break;
                }
            }
            while (tv < 0) { }

            vals[x][y] = tv;
//            cout << "Setting (" << x << ", " << y << ") to " << tv << "\n";
            ++out;
        }

        cout << "Case #" << (t + 1) << ": " << out << "\n";

    }
}
