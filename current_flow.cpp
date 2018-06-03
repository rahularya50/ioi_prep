#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M, Q, T;
    cin >> N >> M >> Q >> T;
    vector<vector<int>> P(N, vector<int>(M));
    for (int i = 0; i != N; ++i) {
        for (int j = 0; j != M; ++j) {
            int x;
            cin >> x;
            P[i][j] = x;
        }
    }

    int num = static_cast<int>(log2(T)) + 2;

    vector<vector<pair<int, int>>> out_moves(N, vector<pair<int, int>>(M));
    vector<vector<pair<int, int>>> curr_moves(N, vector<pair<int, int>>(M));
    vector<vector<pair<int, int>>> prev_moves(N, vector<pair<int, int>>(M));

    for (int i = 0; i != N; ++i) {
        for (int j = 0; j != M; ++j) {
            pair<int, pair<int, int>> best = {P[i][j], {i, j}};
            if (i != N - 1) {
                best = max(best, {P[i + 1][j], {i + 1, j}});
            }
            if (i != 0) {
                best = max(best, {P[i - 1][j], {i - 1, j}});
            }
            if (j != M - 1) {
                best = max(best, {P[i][j + 1], {i, j + 1}});
            }
            if (j != 0) {
                best = max(best, {P[i][j - 1], {i, j - 1}});
            }
            prev_moves[i][j] = best.second;
            if (T % 2 == 0) {
                out_moves[i][j] = {i, j};
            } else {
                out_moves[i][j] = best.second;
            }
        }
    }

//    cout << "doubling\n";

    for (int i = 1; i < num; ++i) {
        for (int r = 0; r != N; ++r) {
            for (int c = 0; c != M; ++c) {
                auto temp = prev_moves[r][c];
                curr_moves[r][c] = prev_moves[temp.first][temp.second];
            }
        }
        for (int r = 0; r != N; ++r) {
            for (int c = 0; c != M; ++c) {
                if (T & (1 << i)) {
                    auto x = out_moves[r][c];
                    out_moves[r][c] = curr_moves[x.first][x.second];
                }
            }
        }
        prev_moves = move(curr_moves);
        curr_moves = vector<vector<pair<int, int>>>(N, vector<pair<int, int>>(M));
    }

//    cout << "reading queries\n";

    for (int q = 0; q != Q; ++q) {
        int r, c;
        cin >> r >> c;
        --r;
        --c;
        int t = T;
        cout << out_moves[r][c].first + 1 << " " << out_moves[r][c].second + 1 << "\n";
    }
}
