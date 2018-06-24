#include <bits/stdc++.h>

using namespace std;

struct segment {
    long long left;
    long long m;
    long long c;
};

long long x_intersect(segment a, segment b) {
    long long temp = (b.c - a.c - 1) / (a.m - b.m) + 1;
//    cout << "polong long found at x = " << temp << "\n";
    return temp;
}

int main() {
    ios::sync_with_stdio(false);

    long long n;
    cin >> n;
    long long a, b, c;
    cin >> a >> b >> c;

    vector<long long> x;
    for (long long i = 0; i != n; ++i) {
        long long temp;
        cin >> temp;
        x.push_back(temp);
    }

    vector<long long> S = {};
    long long run_sum = 0;
    for (auto v : x) {
        run_sum += v;
        S.push_back(run_sum);
    }

    long long out = S.back() * b;
    a *= -1;

    vector<long long> dp;
    vector<segment> hull;

    for (long long i = 0; i != n; ++i) {
        if (hull.size() > 0) {
            auto x_val = S[i];

            auto iter = upper_bound(hull.begin(), hull.end(), x_val, [](long long a, segment b){return a < b.left; });
            auto curr_seg = *(iter - 1);

            auto y_val = curr_seg.m * x_val + curr_seg.c;

            dp.push_back(c - a * S[i] * S[i] + max(y_val, 0LL));
        }
        else {
            dp.push_back(c - a * S[i] * S[i]);
        }

//        cout << "new: " << dp.back() << "\n";

        long long m = 2 * a * S[i];
        long long k = dp[i] - a * S[i] * S[i];
        segment new_seg = {-1, m, k};
        long long left = hull.size() ? x_intersect(hull.back(), new_seg) : -1;

        while (hull.size() && x_intersect(hull.back(), new_seg) < hull.back().left) {
            hull.pop_back();
            left = x_intersect(hull.back(), new_seg);
        }

        new_seg.left = left;
//        cout << "left: " << left << "\n";
        hull.push_back(new_seg);

//        cout << "Current hull: ";
//        for (auto seg : hull) {
//            cout << "(" << seg.left << ", " << seg.m << ", " << seg.c << "), ";
//        }
//        cout << "\n";
    }

    cout << out + dp[n - 1];
}
