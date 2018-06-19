#include <bits/stdc++.h>

using namespace std;

struct fair {
    int t; // day
    int l; // location
    int m; // profit
};

bool operator<(fair a, fair b) {
    return a.t < b.t;
}

int main() {
    int N, U, D, S;
    cin >> N >> U >> D >> S;
    vector<fair> fairs(N);
    for (auto& x : fairs) {
        cin >> x.t >> x.l >> x.m;
    }
    fairs.push_back({0, S, 0});
    sort(fairs.begin(), fairs.end());
    set<pair<int, int>> up_segs_intercepts; // {xintercept, index}
    set<pair<int, int>> down_segs_intercepts; // {xintercept, index}
    set<pair<int, int>> seg_starts; // {start_x, index}
    vector<pair<int, bool>> segs; // {start_x, isUp}
    int out = 0;
    for (int i = N; i >= 0; --i) {
        int x = fairs[i].l;
        int val = 0;
        auto activeSeg = seg_starts.upper_bound({x, 0});
        if (activeSeg != seg_starts.begin()) {
            advance(activeSeg, -1);
            auto xi = activeSeg->first;
            auto m = segs[activeSeg->second].second ? U : D;
            val = max(val, m * (x - xi));
        }
        val += fairs[i].m;
        out = max(out, val);
        int left_i = x - val / U;
        int right_i = x + val / D;
        auto iter = up_segs_intercepts.upper_bound({left_i, 0});
        while (iter != up_segs_intercepts.end()) {
            auto xi = iter->first;
            int xpos = (val + x * D + xi * (U - 1)) / (U + D);
            if (xpos < xi) {
                break;
            }
            int index = iter->second;
            seg_starts.erase({segs[index].first, index});
            iter = up_segs_intercepts.erase(iter);
        }
        if (iter != up_segs_intercepts.end()) {
            int prev_start_x = segs[iter->second].first;
            seg_starts.erase({prev_start_x, iter->second});

        }
        iter = down_segs_intercepts.upper_bound({right_i, 0});
        while (iter != down_segs_intercepts.begin()) {
            advance(iter, -1);
            auto xi = iter->first;
            int xpos = (val - x * U + xi * (D - 1)) / (D - U);
            if (xpos > xi) {
                break;
            }
            int index = iter->second;
            seg_starts.erase({segs[index].first, index});
            iter = down_segs_intercepts.erase(iter);
        }
        int left_start = left_i;
        if (iter != down_segs_intercepts.begin()) {
            advance(iter, -1);
            auto xi = iter->first;
            left_start = (val - x * U + xi * (D - 1)) / (D - U);
        }
        segs.push_back({left_start, true});
        seg_starts.insert({left_start, segs.size() - 1});
        up_segs_intercepts.insert({left_i, segs.size() - 1});

        segs.push_back({x, false});
        seg_starts.insert({x, segs.size() - 1});
        down_segs_intercepts.insert({right_i, segs.size() - 1});

        cout << "Up seg intercepts: [";
        for (auto x : up_segs_intercepts) {
            cout << "(" << x.first << ", " << x.second << "), ";
        }
        cout << "] \n";

        cout << "Down seg intercepts: [";
        for (auto x : down_segs_intercepts) {
            cout << "(" << x.first << ", " << x.second << "), ";
        }
        cout << "] \n";

        cout << "Seg_starts: [";
        for (auto x : seg_starts) {
            cout << "(" << x.first << ", " << x.second << "), ";
        }
        cout << "] \n";
        cout << "Starting here you earn " << val << "\n";
    }
    cout << out << "\n";
}
