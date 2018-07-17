#include <bits/stdc++.h>

using namespace std;

struct segment {
    int m;
    int c;
    int left; // first value where it's smaller!
    int right; // the "left" of the next guy
};

// find first place where a(x) < b(x)
// assume a.m < b.m
int intersect(segment a, segment b) {
//    cout << "a = {" << a.m << ", " << a.c << "}, b = {" << b.m << ", " << b.c << "}\n";
    int out = (a.c - b.c) / (b.m - a.m) + 1; // should be rounded up
//    cout << "out = " << out << "\n";
    return out;
}

struct leftcmp {
bool operator() (segment a, segment b) { return a.left < b.left; };
};

struct slopecmp {
bool operator() (segment a, segment b) { return a.m > b.m; }; // Both should be sorted in the same way, which is why the slopes are REVERSED
};

set<segment, leftcmp> lefthulls[2] = {};
set<segment, slopecmp> slopehulls[2] = {};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, A, B;
    cin >> N >> A >> B;

    long long best = static_cast<long long>(A) * B;

    lefthulls[0].insert({A, 0, 0, (int)1e9 + 2});
    lefthulls[1].insert({B, 0, 0, (int)1e9 + 2});
    slopehulls[0].insert({A, 0, 0, (int)1e9 + 2});
    slopehulls[1].insert({B, 0, 0, (int)1e9 + 2});

    // NEED TO INITIALIZE HULLS!


    for (int q = 0; q != N; ++q) {
        int t;
        cin >> t;
        if (t == 1) {
            char x;
            cin >> x;
            int i = (x == 'A') ? 0 : 1;
            int S, T;
            cin >> S >> T;
            auto p = lefthulls[1 - i].upper_bound({0, 0, S});
            advance(p, -1);
            auto val = static_cast<long long>(p->m) * static_cast<long long>(S) + static_cast<long long>(T) + static_cast<long long>(p->c);
            best = min(best, val);
//            cout << "best = " << best << "\n";

            segment newseg = {S, T, -1, -1};

            if (S >= slopehulls[i].begin()->m) {
                continue;
            }

            // insert into both lefts and slopes
            auto smaller_slope = slopehulls[i].lower_bound({S, 0, 0}); // hull.m <= S
            if (smaller_slope != slopehulls[i].end() && smaller_slope->m == S) {
                if (smaller_slope->c < T) {
                    // it's strictly better!
                    continue;
                    // let's just get out of here
                } else {
                    slopehulls[i].erase(smaller_slope);
                    lefthulls[i].erase(*smaller_slope);

                    // fix inconsistencies
                    // Do we need to???

                    smaller_slope = slopehulls[i].lower_bound({S, 0, 0}); // try again

                }
            }


            while (smaller_slope != slopehulls[i].end() && intersect(*smaller_slope, newseg) >= smaller_slope->right) {
                lefthulls[i].erase(*smaller_slope);
                smaller_slope = slopehulls[i].erase(smaller_slope);
            }

            if (smaller_slope != slopehulls[i].end()) {
                newseg.right = intersect(*smaller_slope, newseg);
                auto rightseg = *smaller_slope;
                lefthulls[i].erase(rightseg);
                slopehulls[i].erase(smaller_slope);
                rightseg.left = max(rightseg.left, newseg.right);
                lefthulls[i].insert(rightseg);
                slopehulls[i].insert(rightseg);
            } else {
                newseg.right = (int)1e9 + 2;
            }

            auto bigger_slope = slopehulls[i].lower_bound(newseg);
            while (bigger_slope != slopehulls[i].begin()) {
                advance(bigger_slope, -1);
                if (intersect(newseg, *bigger_slope) <= bigger_slope->left) {
                    lefthulls[i].erase(*bigger_slope);
                    bigger_slope = slopehulls[i].erase(bigger_slope);
                } else {
                    break;
                }
            }


            newseg.left = intersect(newseg, *bigger_slope);
            auto leftseg = *bigger_slope;
            lefthulls[i].erase(leftseg);
            slopehulls[i].erase(bigger_slope);
            leftseg.right = min(leftseg.right, newseg.left);
            lefthulls[i].insert(leftseg);
            slopehulls[i].insert(leftseg);

            if (newseg.left < newseg.right) {
                lefthulls[i].insert(newseg);
                slopehulls[i].insert(newseg);
            }
//
//            for (auto x : lefthulls[i]) {
//                cout << "{" << x.m << ", " << x.c << ", " << x.left << ", " << x.right << "}\n";
//            }

        } else {
            cout << best << "\n";
        }
    }
}
