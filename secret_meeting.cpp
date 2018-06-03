#include <bits/stdc++.h>

using namespace std;

struct segment {
    int left;
    int m;
    int c;
};

int t_intersect(segment a, segment b, bool maximizing) {
    if (a.m == b.m) {
        if ((a.c > b.c) ^ maximizing) {
            return -1;
        } else {
            return numeric_limits<int>::max();
        }
    }
    if (maximizing) {
        return (a.c - b.c - 1) / (b.m - a.m) + 1;
    } else {
        return (b.c - a.c - 1) / (a.m - b.m) + 1;
    }
}

vector<segment> make_hull(vector<pair<int, int>>& inp_segs, bool maximizing) {
    vector<segment> hull;
    for (int i = 0; i != inp_segs.size(); ++i) {
        segment new_seg = {-1, inp_segs[i].first, inp_segs[i].second};
        while (hull.size() > 0 && t_intersect(hull.back(), new_seg, maximizing) <= hull.back().left) {
            hull.pop_back();
        }
        if (hull.size() > 0) {
            new_seg.left = t_intersect(hull.back(), new_seg, maximizing);
        }
        hull.push_back(new_seg);
    }
    return hull;
}

vector<segment> merge_hulls(vector<segment>& top_hull, vector<segment>& bottom_hull) {
    vector<segment> hull;
    int p1 = 0;
    int p2 = 0;
    while (p1 != top_hull.size() || p2 != bottom_hull.size()) {
        if (p1 == top_hull.size() || p2 != bottom_hull.size() && top_hull[p1].left > bottom_hull[p2].left) {
            if (p1 != 0) {
                if (hull.size() > 0 && hull.back().left == bottom_hull[p2].left) {
                    hull.pop_back();
                }
                hull.push_back({bottom_hull[p2].left, top_hull[p1 - 1].m - bottom_hull[p2].m, top_hull[p1 - 1].c - bottom_hull[p2].c});
            }
            ++p2;
        } else {
            if (p2 != 0) {
                if (hull.size() > 0 && hull.back().left == top_hull[p1].left) {
                    hull.pop_back();
                }
                hull.push_back({top_hull[p1].left, top_hull[p1].m - bottom_hull[p2 - 1].m, top_hull[p1].c - bottom_hull[p2 - 1].c});
            }
            ++p1;
        }
    }
    return hull;
}

segment lookup(int t, vector<segment>& hull) {
    return *(next(upper_bound(hull.begin(), hull.end(), t, [](int t, segment x) { return t < x.left; }), -1));
}

int getValue(int t, int c, int d, vector<segment>& width, vector<segment>& height) {
    auto seg1 = lookup(t, width);
    auto seg2 = lookup(t, height);
    return max(seg1.m * t * c + seg1.c * c, seg2.m * t * d + seg2.c * d);
}

int main() {
    int N, T;
    cin >> N >> T;
    vector<pair<pair<int, int>, pair<int, int>>> people;
    vector<pair<int, int>> x_segs; // {slope, intercept}
    vector<pair<int, int>> y_segs; // {slope, intercept}
    for (int i = 0; i != N; ++i) {
        int x, y, u, v;
        cin >> x >> y >> u >> v;
        people.push_back({{x, y}, {u, v}});
        x_segs.push_back({u, x});
        y_segs.push_back({v, y});
    }

    sort(x_segs.begin(), x_segs.end());
    auto x_max = make_hull(x_segs, true);
    reverse(x_segs.begin(), x_segs.end());
    auto x_min = make_hull(x_segs, false);

    sort(y_segs.begin(), y_segs.end());
    auto y_max = make_hull(y_segs, true);
    reverse(y_segs.begin(), y_segs.end());
    auto y_min = make_hull(y_segs, false);

    auto width = merge_hulls(x_max, x_min);
    auto height = merge_hulls(y_max, y_min);

//    cout << "Ymin: \n";
//    for (auto x : y_min) {
//        cout << x.left << " " << x.m << " " << x.c << "\n";
//    }
//
//    cout << "\n";
//
//    cout << "Ymax: \n";
//    for (auto x : y_max) {
//        cout << x.left << " " << x.m << " " << x.c << "\n";
//    }
//
//    cout << "\n";
//
//    cout << "Width: \n";
//    for (auto x : width) {
//        cout << x.left << " " << x.m << " " << x.c << "\n";
//    }
//
//    cout << "\n";
//
//     cout << "Xmin: \n";
//    for (auto x : x_min) {
//        cout << x.left << " " << x.m << " " << x.c << "\n";
//    }
//
//    cout << "\n";
//
//    cout << "Xmax: \n";
//    for (auto x : x_max) {
//        cout << x.left << " " << x.m << " " << x.c << "\n";
//    }
//
//    cout << "\n";
//
//    cout << "Height: \n";
//    for (auto x : height) {
//        cout << x.left << " " << x.m << " " << x.c << "\n";
//    }
//
//    cout << "\n";

    int Q;
    cin >> Q;
    for (int q = 0; q != Q; ++q) {
        int c, d;
        cin >> c >> d;
        int low = 1;
        int high = T + 1;
        while (high - low > 2) {
            int x = high - low;
            int mid1 = low + x / 3;
            int mid2 = low + 2 * x / 3;
            auto val1 = getValue(mid1, c, d, width, height);
            auto val2 = getValue(mid2, c, d, width, height);
//            cout << low << " " << mid1 << "=" << val1 << " " << mid2 << "=" << val2 << " " << high << " " "\n";
            if (val1 <= val2) {
                high = mid2;
            } else {
                low = mid1;
            }
        }

        auto val1 = getValue(low, c, d, width, height);
        auto val2 = getValue(low + 1, c, d, width, height);
//        cout << low << "=" << val1 << " " << low + 1 << "=" << val2 << "\n";
        if (val1 <= val2) {
            cout << low << " ";
        } else {
            cout << low + 1 << " ";
        }
        cout << min(val1, val2) / 2 << "\n";
    }
}
