#include <bits/stdc++.h>

using namespace std;

struct segment {
    int m;
    long long c;
    int left;
};

const int INF = numeric_limits<int>::max();

int intersect(const segment& a, const segment& b) {
    if (a.m == b.m) {
        if (a.c > b.c) {
            return -INF;
        } else {
            return INF;
        }
    }
    return (b.c - a.c - 1) / (a.m - b.m) + 1;
}

int A[1000000];
int S[1000000];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, K;
    cin >> N >> K;
    ++K;
    for (int i = 0; i != N; ++i) {
        cin >> A[i];
    }

    vector<int> S(N);
    int curr = 0;
    for (int i = 0; i != N; ++i) {
        curr += A[i];
        S[i] = curr;
    }

//    cout << "ready!\n";

    long long val;
//    vector<deque<segment>> hulls(K + 1);
    vector<segment> prev_hull;
    vector<segment> curr_hull;
    for (int k = 1; k <= K; ++k) {
        for (int n = 0; n < N; ++n) {
            val = 0;
            auto iter = upper_bound(prev_hull.begin(), prev_hull.end(), S[n], [](int x, const segment& a) { return x < a.left; });
            if (iter != prev_hull.begin()) {
                advance(iter, -1);
                val = ((long long)iter->m) * S[n] + iter->c;
            }
//            cout << "dp[" << n << "][" << k << "] = " << val << "\n";
//            cout << "valfound\n";
            segment new_seg = {S[n], val - ((long long)S[n])*S[n], -1};
            while (curr_hull.size() != 0 && intersect(new_seg, curr_hull.back()) <= curr_hull.back().left) {
                curr_hull.pop_back();
            }
//            cout << "hullcleared\n";
            if (curr_hull.size() == 0) {
                new_seg.left = 0;
            } else {
                new_seg.left = intersect(new_seg, curr_hull.back());
            }
            curr_hull.push_back(new_seg);
        }
        swap(prev_hull, curr_hull);
        curr_hull = {};
    }
    cout << val << "\n";
}
