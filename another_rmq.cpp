#include <bits/stdc++.h>

using namespace std;

int cnt(int row, int i, int L, int R, int X, const vector<vector<vector<int>>>& segments) {
    int curr_step = (1 << (segments.size() - row - 1));
    int curr_start = curr_step * i;
    int curr_end = curr_step * (i + 1);
    int curr_mid = (curr_start + curr_end) / 2;

    if (X >= segments[row][i].back()) {
        return R - L;
    } else if (X < segments[row][i].front()) {
        return 0;
    }

    if (L == curr_start && R == curr_end) {
        return distance(segments[row][i].begin(), upper_bound(segments[row][i].begin(), segments[row][i].end(), X)); // <= X
    }

    int out = 0;
    if (L < curr_mid) {
        out += cnt(row + 1, i * 2, L, min(R, curr_mid), X, segments);
    }
    if (R > curr_mid) {
        out += cnt(row + 1, i * 2 + 1, max(L, curr_mid), R, X, segments);
    }

    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, Q;
    cin >> N >> Q;
    vector<int> A;
    A.reserve(N);
    for (int i = 0; i != N; ++i) {
        int x;
        cin >> x;
        A.push_back(x);
    }
    int rows = log2(N - 1) + 2;
//    cout << "Rows: " << rows << "\n";
    vector<vector<vector<int>>> segments(rows);
    for (int i = 0; i != N; ++i) {
        segments.back().push_back( { A[i] } );
    }
    for (int i = N; i != (1 << (rows - 1)); ++i) {
        segments.back().push_back( { } );
    }
    for (int row = rows - 2; row >= 0; --row) {
        segments[row].reserve(1 << row);
        for (int i = 0; i != (1 << row); ++i) {
            segments[row].push_back({});
            segments[row].back().reserve(1 << (rows - row));
            int p1 = 0;
            int p2 = 0;
            int child_size_1 = segments[row + 1][2 * i].size();
            int child_size_2 = segments[row + 1][2 * i + 1].size();
//            cout << "Child size: " << child_size << "\n";
            while (p1 < child_size_1 || p2 < child_size_2) {
                if (p2 == child_size_2 || (p1 != child_size_1 && segments[row + 1][2 * i][p1] < segments[row + 1][2 * i + 1][p2])) {
                    segments[row][i].push_back(segments[row + 1][2 * i][p1]);
                    ++p1;
                } else {
                    segments[row][i].push_back(segments[row + 1][2 * i + 1][p2]);
                    ++p2;
                }
            }
        }
    }
//
//    vector<vector<pair<int, int>>> table(log2(N) + 1);
//    table[0].reserve(N);
//    for (int i = 0; i != N; ++i) {
//        table[0].push_back({A[i], A[i]});
//    }
//    for (int row = 1; row <= log2(N); ++row) {
//        int stride = (1 << row);
//        table[row].reserve(N - stride + 2);
//        for (int i = 0; i + stride <= N; ++i) {
//            auto a = table[row - 1][i];
//            auto b = table[row - 1][i + stride / 2];
//            table[row].push_back({min(a.first, b.first), max(a.second, b.second)});
//        }
//    }

//
    for (auto& x : segments) {
        for (auto& y : x) {
            cout << "(";
            for (auto z : y) {
                cout << z << ", ";
            }
            cout << "), ";
        }
        cout << "\n";
    }

//    for (auto x : table) {
//        for (auto y : x) {
//            cout << "(" << y.first << ", " << y.second << "), ";
//        }
//        cout << "\n";
//    }

//    return 0;

    for (int q = 0; q != Q; ++q) {
        int L, R;
        cin >> L >> R;
        --L;
        int width = R - L + 1;

        int row = log2(R - L);
        int stride = 1 << row;

        int low = 0; // min(table[row][L].first, table[row][R - stride].first) - 1;
        int high = 10000; //max(table[row][L].second, table[row][R - stride].second) + 1;

//        cout << low << ", " << high << "\n";

        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (cnt(0, 0, L, R, mid, segments) < width / 2) {
                low = mid;
            } else {
                high = mid;
            }
        }
//        cout << "cnt(" << L << ", " << R << ", " << low << ") = " << cnt(0, 0, L, R, low, segments) << "\n";
//        cout << "cnt(" << L << ", " << R << ", " << high << ") = " << cnt(0, 0, L, R, high, segments) << "\n";
        cout << high << "\n";
    }
}
