#include "bits/stdc++.h"

using namespace std;

long long square(long long x) {
    return x * x;
}

struct segment {
    long long left;
    long long m;
    long long c;
};

void printseg(segment x){
    cout << "{" << x.left << ", " << x.m << ", " << x.c << "}";
}

// when does b first become smaller than a
// b.m < a.m
long long first_smaller(segment a, segment b) {
//    cout << "Comparing ";
//    printseg(a);
//    cout << " to ";
//    printseg(b);
//    cout << "\n";
    return (b.c - a.c - 1) / (a.m - b.m) + 1;
}

long long take_photos(int N, int M, int K, vector<int> R, vector<int> C) {
//    cout << "Starting!" << "\n";
    vector<pair<long long, long long>> intervals;
    for (long long i = 0; i != N; ++i) {
        intervals.push_back({min(R[i], C[i]), max(R[i], C[i])});
    }
    sort(intervals.begin(), intervals.end());
    vector<pair<long long, long long>> simple_intervals;
    for (long long i = 0; i != N; ++i) {
        pair<long long, long long> curr_interval = intervals[i];
        if (simple_intervals.size() > 0 && curr_interval.second <= simple_intervals.back().second) {
            continue;
        } else if (simple_intervals.size() > 0 && simple_intervals.back().first == curr_interval.first) {
            simple_intervals.back() = curr_interval;
        } else {
            simple_intervals.push_back(curr_interval);
        }
    }

//    for (auto x : simple_intervals) {
//        cout << "(" << x.first << ", " << x.second << "), ";
//    }
//    cout << "\n";

    long long N2 = simple_intervals.size();

    vector<long long> overlap(N2);
    vector<long long> next_pos(N2);
    for (long long i = 0; i != N2 - 1; ++i) {
        next_pos[i] = simple_intervals[i + 1].first;
        if (next_pos[i] > simple_intervals[i].second) {
            overlap[i] = simple_intervals[i].second + 1;
        } else {
            overlap[i] = next_pos[i];
        }
//        cout << "overlap[" << i << "] = " << overlap[i] << "\n";
//        cout << "next_pos[" << i << "] = " << next_pos[i] << "\n";
    }

    vector<vector<long long>> dp(K + 1, vector<long long>(N2));
    vector<vector<segment>> hull(K + 1);

    // solve for i = 0
    for (long long k = 1; k <= K; ++k) {
        auto x = simple_intervals[0].second;
        dp[k][0] = square(simple_intervals[0].second - simple_intervals[0].first + 1);
        hull[k].push_back({-1, - 2LL*next_pos[0], dp[k][0] + 2LL * (x + 1) * overlap[0] - square(x + 1) + square(next_pos[0]) - square(overlap[0])});
//        cout << "dp[" << k << "][" << 0 << "] = " << dp[k][0] << "\n";
    }

    for (long long i = 1; i != N2; ++i) {
        // wanna cover up to elem i - 1 with 1 thing
        auto x = simple_intervals[i].second;
//        for (long long k = 1; k <= K; ++k) {
//            dp[k][i - 1] = square(simple_intervals[i - 1].second - simple_intervals[0].first + 1);
//            cout << "dp[" << k << "][" << i - 1 << "] = " << dp[k][i - 1] << "\n";
//            segment newseg = {-1, -2*prev[i], dp[k][i - 1] + 2 * (x + 1) * prev[i - 1] - square(x + 1)};
//            while (hull[k].size() > 0 && first_smaller(hull[k].back(), newseg) <= hull[k].back().left) {
//                hull[k].pop_back();
//            }
//            if (hull[k].size() > 0) {
//                newseg.left = first_smaller(hull[k].back(), newseg);
//            }
//            hull[k].push_back(newseg);
//        }
        for (long long k = 1; k <= K; ++k) {
//            cout << "Trying i = " << i << ", k = " << k << "\n";
            if (k == 1) {
                dp[k][i] = square(simple_intervals[i].second - simple_intervals[0].first + 1);
            } else {
                auto hull_iter = upper_bound(hull[k - 1].begin(), hull[k - 1].end(), x + 1, [](long long y, segment s) { return y < s.left; });
                advance(hull_iter, -1);
                auto m = hull_iter->m;
                auto c = hull_iter->c;
//                cout << "m = " << m << ", c = " << c << "\n";
//                cout << "x = " << x << "\n";
                dp[k][i] = square(x + 1) + m*(x + 1) + c;
            }
//            cout << "dp[" << k << "][" << i << "] = " << dp[k][i] << "\n";
            if (i != N2 - 1) {
                segment newseg = {-1, -2LL*next_pos[i], dp[k][i] + 2LL*(x + 1)*overlap[i] - square(x + 1) + square(next_pos[i]) - square(overlap[i])};
                while (hull[k].size() > 0 && first_smaller(hull[k].back(), newseg) <= hull[k].back().left) {
                    hull[k].pop_back();
                }
                if (hull[k].size() > 0) {
                    newseg.left = first_smaller(hull[k].back(), newseg);
                }
                hull[k].push_back(newseg);
            }
        }
    }

    return dp[K].back();
}
//
//long long main() {
//    long long n, m, k;
//    cin >> n >> m >> k;
//    vector<long long> r(n);
//    vector<long long> c(n);
//    for (long long i = 0; i != n; ++i) {
//        cin >> r[i] >> c[i];
//    }
//    cout << take_photos(n, m, k, &r[0], &c[0]) << "\n";
//}
