#include <bits/stdc++.h>

using namespace std;

struct segment {
    long long left;
    long long m;
    long long c;
};

long long intersect(segment a, segment b) { // a.m >= b.m
    // when does a first exceed b?
    if (a.m == b.m) {
        if (a.c > b.c) {
            return 100LL * numeric_limits<int>::min();
        } else {
            return 100LL * numeric_limits<int>::max();
        }
    }
//    cout << "a = [" << a.m << ", " << a.c << "], b = [" << b.m << ", " << b.c << "]\n";
    return ((b.c - a.c) / (a.m - b.m)) + 1;
//    return ceil((long double)(b.c - a.c) / (a.m - b.m));
}

bool operator<(segment a, segment b) {
    return a.left < b.left || (a.left == b.left && a.m < b.m) || (a.left == b.left && a.m == b.m && a.c < b.c);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long N, A, B;
    cin >> N >> A >> B;
    set<pair<long long, segment>> left_x = {{0, {0, A, 0}}};
    set<pair<long long, segment>> left_m = {{A, {0, A, 0}}};
    set<pair<long long, segment>> right_x = {{0, {0, B, 0}}};
    set<pair<long long, segment>> right_m = {{B, {0, B, 0}}};

    map<int, int> left_reps;
    map<int, int> right_reps;

    long long best = A*B;

    for (long long i = 0; i != N; ++i) {
        long long t;
        cin >> t;
        if (t == 1) {
            char l;
            cin >> l;
            long long s, t;
            cin >> s >> t;
            if (l == 'A' && s >= A || l == 'B' && s >= B) {
                continue;
            }
            set<pair<long long, segment>> *xh;
            set<pair<long long, segment>> *mh;
            set<pair<long long, segment>> *xh_2;
            map<int, int> *rs;
            if (l == 'A') {
                xh = &left_x;
                mh = &left_m;
                xh_2 = &right_x;
                rs = &left_reps;
            } else {
                xh = &right_x;
                mh = &right_m;
                xh_2 = &left_x;
                rs = &right_reps;
            }

            auto& x_hull = *xh;
            auto& m_hull = *mh;
            auto& lookup = *xh_2;
            auto& reps = *rs;

            if (reps.find(s) != reps.end() && reps.find(s)->second < t) {
                continue;
            }

            // lookup in right
            auto seg = next(lookup.upper_bound({s + 1, {numeric_limits<long long>::min(), 0, 0}}), -1)->second;
            auto val = seg.m * s + seg.c + t;
            best = min(val, best);
//            cout << "seg = [" << seg.m << ", " << seg.c << "]\n";
//            cout << "Best = " << best << "\n";

            segment newseg = {-1, s, t};
            // insert into left
            auto l_slope = m_hull.lower_bound({s + 1, {numeric_limits<long long>::min(), 0, 0}});
            auto r_slope = l_slope;
            bool flag = false;
            if (l_slope == m_hull.begin()) { // if we're the smallest slope, no point in eliminating
                flag = true;
            } else {
                advance(r_slope, -1);
//                cout << "r_slope = " << r_slope->second.m << "\n";
            }
            while (l_slope != m_hull.end() && intersect(l_slope->second, newseg) <= l_slope->second.left) {
                auto n = next(l_slope);
                auto ret = x_hull.erase({l_slope->second.left, l_slope->second});
                while (ret == 0) { }
                m_hull.erase(l_slope);
                l_slope = n;
            }
//            cout << "cat\n";
//            cout << "meow\n";

            if (!flag) {
                auto n = r_slope;
                if (r_slope != m_hull.begin()) {
                    n = next(r_slope, -1);
                }
                while (r_slope != m_hull.begin() && intersect(newseg, r_slope->second) >= n->second.left) {
//                    cout << "erasing slope = " << r_slope->second.m << ", " << r_slope->second.c << "\n";
                    auto ret = x_hull.erase({r_slope->second.left, r_slope->second});
                    while (ret == 0) { }
                    m_hull.erase(r_slope);
                    r_slope = n;
                    if (r_slope != m_hull.begin()) {
                        n = next(r_slope, -1);
                    }
                }
//              cout << "finalizing\n";
                auto oldseg = r_slope->second;
                auto ret = x_hull.erase({r_slope->second.left, r_slope->second});
                while (ret == 0) { }
                m_hull.erase(r_slope);
                oldseg.left = max(oldseg.left, intersect(newseg, oldseg));
                x_hull.insert({oldseg.left, oldseg});
                m_hull.insert({oldseg.m, oldseg});
            }

            newseg.left = intersect(l_slope->second, newseg);
            auto r_intersect = intersect(newseg, r_slope->second);
//            cout << newseg.left << " <= x < " << r_intersect << "\n";
            if (flag || r_intersect > newseg.left) {
//                cout << "inserting\n";
                x_hull.insert({newseg.left, newseg});
                m_hull.insert({newseg.m, newseg});
                reps[newseg.m] = newseg.c;
            } else {
//                cout << "irrelevant\n";
            }

//
//            for (auto x : m_hull) {
//                cout << x.second.left << ", " << x.second.m << ", " << x.second.c << "\n";
//            }
//            cout << "---\n";
//            for (auto x : x_hull) {
//                cout << x.second.left << ", " << x.second.m << ", " << x.second.c << "\n";
//            }

//            cout << "Done\n";
        } else {
            cout << best << "\n";
        }
    }
}

