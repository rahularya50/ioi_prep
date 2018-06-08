#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    long long M, N, a, b, c, d;
    cin >> M >> N >> a >> b >> c >> d;

    vector<vector<long long>> grid(M, vector<long long>(N));
    for (long long row = 0; row != N; ++row) {
        for (long long col = 0; col != M; ++col) {
            long long x;
            cin >> x;
            grid[col][row] = x;
        }
    }

    vector<vector<long long>> col_sums(M, vector<long long>(N));
    for (long long col = 0; col != M; ++col) {
        long long run_sum = 0;
        for (long long row = 0; row != N; ++row) {
            run_sum += grid[col][row];
            col_sums[col][row] = run_sum;
        }
    }

    vector<vector<long long>> big_sums(M, vector<long long>(N));
    for (long long row = 0; row <= (N - b); ++row) {
        long long run_sum = 0;
        for (long long col = 0; col != a; ++col) {
            run_sum += col_sums[col][row + b - 1];
            if (row != 0) {
                run_sum -= col_sums[col][row - 1];
            }
        }
        big_sums[0][row] = run_sum;
        for (long long col = a; col != M; ++col) {
            run_sum += col_sums[col][row + b - 1];
            run_sum -= col_sums[col - a][row + b - 1];
            if (row != 0) {
                run_sum -= col_sums[col][row - 1];
                run_sum += col_sums[col - a][row - 1];
            }
            big_sums[col - a + 1][row] = run_sum;
        }
    }

    vector<vector<long long>> small_sums(M, vector<long long>(N));
    for (long long row = 0; row <= (N - d); ++row) {
        long long run_sum = 0;
        for (long long col = 0; col != c; ++col) {
            run_sum += col_sums[col][row + d - 1];
            if (row != 0) {
                run_sum -= col_sums[col][row - 1];
            }
        }
        small_sums[0][row] = run_sum;
        for (long long col = c; col != M; ++col) {
            run_sum += col_sums[col][row + d - 1];
            run_sum -= col_sums[col - c][row + d - 1];
            if (row != 0) {
                run_sum -= col_sums[col][row - 1];
                run_sum += col_sums[col - c][row - 1];
            }
            small_sums[col - c + 1][row] = run_sum;
        }
    }

//    for (long long row = 0; row <= (N - d); ++row) {
//        for (long long col = 0; col <= (M - c); ++col) {
//            cout << small_sums[col][row] << ", ";
//        }
//        cout << "\n";
//    }

    long long inner_rows = b - d - 1;
    long long inner_cols = a - c - 1;
//
//    cout << "inner_rows = " << inner_rows << "\n";
//    cout << "inner_cols = " << inner_cols << "\n";

    vector<vector<pair<long long, pair<long long, long long>>>> small_row_mins(M, vector<pair<long long, pair<long long, long long>>>(N));
    for (long long row = 0; row != N; ++row) {
        set<pair<long long, pair<long long, long long>>> vals;
        for (long long col = 0; col != inner_cols; ++col) {
            vals.insert({small_sums[col][row], {col, row}});
        }
        small_row_mins[0][row] = *vals.begin();
        for (long long col = inner_cols; col != M; ++col) {
            vals.insert({small_sums[col][row], {col, row}});
            vals.erase({small_sums[col - inner_cols][row], {col - inner_cols, row}});
            small_row_mins[col - inner_cols + 1][row] = *vals.begin();
        }
    }
//
//    for (long long row = 0; row <= (N - d); ++row) {
//        for (long long col = 0; col <= (M - c); ++col) {
//            cout << small_row_mins[col][row].first << ", ";
//        }
//        cout << "\n";
//    }

    long long best_val = 0;
    pair<long long, long long> best_big;
    pair<long long, long long> best_small;

    for (long long col = 0; col < M - a + 1; ++col) {
        set<pair<long long, pair<long long, long long>>> vals;
        for (long long row = 0; row != inner_rows; ++row) {
            vals.insert(small_row_mins[col + 1][row + 1]);
        }
        long long net = big_sums[col][0] - vals.begin()->first;
        if (net > best_val) {
            best_val = net;
            best_big = {col, 0};
            best_small = vals.begin()->second;
        }
//        cout << "Considering (" << 0 << ", " << col << ")\n";
        for (long long row = inner_rows; row < N - 1; ++row) {
//            cout << "Considering (" << row << ", " << col << ")\n";
            vals.insert(small_row_mins[col + 1][row + 1]);
            vals.erase(small_row_mins[col + 1][row - inner_rows + 1]);
            long long net = big_sums[col][row - inner_rows + 1] - vals.begin()->first;
            if (net > best_val) {
                best_val = net;
                best_big = {col, row - inner_rows + 1};
                best_small = vals.begin()->second;
            }
        }
    }

    cout << best_big.first+1 << " " << best_big.second+1 << "\n";
    cout << best_small.first+1 << " " << best_small.second+1 << "\n";
}
