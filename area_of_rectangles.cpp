#include <bits/stdc++.h>

using namespace std;

using interval = pair<long long, long long>;
using rect = pair<interval, interval>;
struct node {
    long long real_size;
    long long len_covered;
    long long times_covered;
};

long long log2(long long N) {
    long long out = 1;
    while (N >>= 1) {
        ++out;
    }
    return out;
}

long long add(long long row, long long i, long long a, long long b, vector<vector<node>>& segment_tree) {
    long long step_size = 1 << (segment_tree.size() - 1 - row);
    long long start_pos = step_size * i;
    long long end_pos = step_size * (i + 1);
    long long mid_pos = (start_pos + end_pos) / 2;

    if (step_size == 1) {
        if (a <= start_pos && end_pos <= b) {
            ++segment_tree[row][i].times_covered;
        }
        return segment_tree[row][i].real_size * (segment_tree[row][i].times_covered > 0);
    }

    if (a <= start_pos && end_pos <= b) {
        ++segment_tree[row][i].times_covered;
        return segment_tree[row][i].real_size * (segment_tree[row][i].times_covered > 0);
    }

    if (a < mid_pos) {
        add(row + 1, 2 * i, a, min(b, mid_pos), segment_tree);
    }

    if (b > mid_pos) {
        add(row + 1, 2 * i + 1, max(mid_pos, a), b, segment_tree);
    }

    long long out = (segment_tree[row + 1][2 * i].times_covered) ? (segment_tree[row + 1][2 * i].real_size) : (segment_tree[row + 1][2 * i].len_covered);
    out += (segment_tree[row + 1][2 * i + 1].times_covered) ? (segment_tree[row + 1][2 * i + 1].real_size) : (segment_tree[row + 1][2 * i + 1].len_covered);

    segment_tree[row][i].len_covered = out;

    if (segment_tree[row][i].times_covered) {
        return segment_tree[row][i].real_size;
    } else {
        return segment_tree[row][i].len_covered;
    }
}

long long del(long long row, long long i, long long a, long long b, vector<vector<node>>& segment_tree) {
    long long step_size = 1 << (segment_tree.size() - 1 - row);
    long long start_pos = step_size * i;
    long long end_pos = step_size * (i + 1);
    long long mid_pos = (start_pos + end_pos) / 2;

    if (step_size == 1) {
        if (a <= start_pos && end_pos <= b) {
            --segment_tree[row][i].times_covered;
        }
        return segment_tree[row][i].real_size * (segment_tree[row][i].times_covered > 0);
    }

    if (a <= start_pos && end_pos <= b) {
        --segment_tree[row][i].times_covered;
        if (segment_tree[row][i].times_covered > 0) {
            return segment_tree[row][i].real_size;
        } else {
            return segment_tree[row][i].len_covered;
        }
    }

    if (a < mid_pos) {
        del(row + 1, 2 * i, a, min(b, mid_pos), segment_tree);
    }

    if (b > mid_pos) {
        del(row + 1, 2 * i + 1, max(mid_pos, a), b, segment_tree);
    }

    long long out = (segment_tree[row + 1][2 * i].times_covered) ? (segment_tree[row + 1][2 * i].real_size) : (segment_tree[row + 1][2 * i].len_covered);
    out += (segment_tree[row + 1][2 * i + 1].times_covered) ? (segment_tree[row + 1][2 * i + 1].real_size) : (segment_tree[row + 1][2 * i + 1].len_covered);

    segment_tree[row][i].len_covered = out;

    if (segment_tree[row][i].times_covered) {
        return segment_tree[row][i].real_size;
    }

    return out;
}

int main() {
    ios::sync_with_stdio(false);

    long long N;
    cin >> N;

    vector<rect> rects;
    rects.reserve(N);
    map<long long, long long> ymap;
    map<long long, pair<vector<interval>, vector<interval>>> y_vals;

    for (long long i = 0; i != N; ++i) {
        long long lx, ly, hx, hy;
        cin >> lx >> ly >> hx >> hy;
        rects.push_back({{lx, hx}, {ly, hy}});
        ymap[ly] = 0;
        ymap[hy] = 0;
    }

    vector<long long> ylist;
    ylist.reserve(ymap.size());
    long long i = 0;
    for (auto iter : ymap) {
        auto y = iter.first;
        ylist.push_back(y);
        ymap[y] = i;
        ++i;
    }

    for (auto rect : rects) {
        y_vals[rect.first.first].first.push_back({ymap[rect.second.first], ymap[rect.second.second]});
        y_vals[rect.first.second].second.push_back({ymap[rect.second.first], ymap[rect.second.second]});
    }

    long long ysize = ylist.size();

//    cout << ysize << " distincts with log = " << (log2(ysize)) << "\n";

    vector<vector<node>> segment_tree(log2(ysize) + 1);

    segment_tree[log2(ysize)] = vector<node>(1 << log2(ysize));

    for (long long i = 0; i != (ysize - 1); ++i) {
        segment_tree[log2(ysize)][i] = {ylist[i + 1] - ylist[i], 0, 0};
    }

    for (long long row = log2(ysize) - 1; row >= 0; --row) {
        segment_tree[row].reserve(1 << row);
        for (long long i = 0; i != (1 << row); ++i) {
            segment_tree[row].push_back({segment_tree[row + 1][2 * i].real_size + segment_tree[row + 1][2 * i + 1].real_size});
        }
    }

    long long out = 0;
    long long curr = 0;
    long long prev_x = 0;

    for (auto& iter : y_vals) {
        long long x = iter.first;
        auto& intervals = iter.second;

        out += (x - prev_x) * curr;
        prev_x = x;

        const vector<interval>& to_add = intervals.first;
        const vector<interval>& to_del = intervals.second;

        for (auto interval : to_add) {
            curr = add(0, 0, interval.first, interval.second, segment_tree);
        }

        for (auto interval : to_del) {
            curr = del(0, 0, interval.first, interval.second, segment_tree);
        }
//
//        cout << "begin: \n";
//
//        for (auto row : segment_tree) {
//            for (auto elem : row) {
//                cout << "(" << elem.real_size << ", " << elem.len_covered << ", " << elem.times_covered << "), ";
//            }
//            cout << "\n";
//        }
//
//        cout << "at pos: " << x << " " << curr << "\n";
    }

    cout << out;
}
