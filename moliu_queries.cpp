#include <bits/stdc++.h>

using namespace std;

struct segment {
    long long cnt;
    long long sum;
    long long sum_squares;
};

void update(long long sign, long long x, long long i, long long row, vector<vector<segment>>& segments) {
    long long step_size = 1 << (segments.size() - row - 1);
    long long start_pos = step_size * i;
    long long end_pos = step_size * (i + 1);
    long long mid_pos = (start_pos + end_pos) / 2;

    segments[row][i].cnt += sign;
    segments[row][i].sum += sign * x;
    segments[row][i].sum_squares += sign * x * x;

    if (step_size > 1) {
        if (x < mid_pos) {
            update(sign, x, 2 * i, row + 1, segments);
        } else {
            update(sign, x, 2 * i + 1, row + 1, segments);
        }
    }
}

segment total(long long a, long long b, long long i, long long row, vector<vector<segment>>& segments) {
//    cout << "segment: " << a << " -> " << b << "\n";
    long long step_size = 1 << (segments.size() - row - 1);
    long long start_pos = step_size * i;
    long long end_pos = step_size * (i + 1);
    long long mid_pos = (start_pos + end_pos) / 2;

    if (a == start_pos & b == end_pos) {
        return segments[row][i];
    }

    segment out = {0, 0, 0};
    if (a < mid_pos) {
        auto x = total(a, min(b, mid_pos), 2 * i, row + 1, segments);
        out.cnt += x.cnt;
        out.sum += x.sum;
        out.sum_squares += x.sum_squares;
    }
    if (b > mid_pos) {
        auto x = total(max(a, mid_pos), b, 2 * i + 1, row + 1, segments);
        out.cnt += x.cnt;
        out.sum += x.sum;
        out.sum_squares += x.sum_squares;
    }
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long N;
    cin >> N;
    vector<long long> bitstring(N);
    for (long long i = 0; i != N; ++i) {
        char x;
        cin >> x;
        bitstring[i] = (x == '1');
    }
    vector<long long> diffs(N - 1); // diff between i and i + 1
    for (long long i = 0; i != N - 1; ++i) {
        diffs[i] = (bitstring[i] != bitstring[i + 1]);
    }
    long long rows = log2(N - 1) + 2;
    vector<vector<segment>> segments(rows);
    segments.back().reserve(1 << (rows - 1));
    for (long long i = 0; i != N - 1; ++i) {
        segments.back().push_back({diffs[i], diffs[i] * i, diffs[i] * i * i});
    }
    while (segments.back().size() < (1 << (rows - 1))) {
        segments.back().push_back({0, 0, 0});
    }
    for (long long row = rows - 2; row >= 0; --row) {
        segments[row].reserve(1 << row);
        for (long long i = 0; i != (1 << row); ++i) {
            auto a = segments[row + 1][2 * i];
            auto b = segments[row + 1][2 * i + 1];
            segments[row].push_back({a.cnt + b.cnt, a.sum + b.sum, a.sum_squares + b.sum_squares});
        }
    }

//    for (auto x : segments) {
//        for (auto y : x) {
//            cout << y.cnt << " ";
//        }
//        cout << "\n";
//    }

    long long Q;
    cin >> Q;
    for (long long q = 0; q != Q; ++q) {
        long long type;
        cin >> type;
        long long l, r;
        cin >> l >> r;
        --l;
//        for (auto x : segments) {
//            for (auto y : x) {
//                cout << y.cnt << " ";
//            }
//            cout << "\n";
//        }
        if (type == 1) {
            if (l) {
                long long delta = 1 - 2 * (segments.back()[l - 1].cnt);
                update(delta, l - 1, 0, 0, segments);
            }
            if (r != N) {
                update(1 - 2 * (segments.back()[r - 1].cnt), r - 1, 0, 0, segments);
            }
        } else {
            if (l + 1 == r) {
                cout << 1 << "\n";
                continue;
            }
            auto x = total(l, r - 1, 0, 0, segments);
//            cout << "cnt = " << x.cnt << ", sum = " << x.sum << ", sqsum = " << x.sum_squares << "\n";
            cout << (l + r - 2) * x.sum - x.sum_squares + (r + l - r*l - 1) * x.cnt + (r - l) * (r - l + 1) / 2 << "\n";
        }
    }
}
