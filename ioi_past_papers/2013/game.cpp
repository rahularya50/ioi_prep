#include <bits/stdc++.h>

using namespace std;

int R, C, N;

struct segment {
    int lower;
    int upper;
    int val;
};

using y_seg_tree = vector<vector<segment>>;

struct x_segment {
    int lower;
    int upper;
    y_seg_tree val;
};

using range_tree = vector<vector<x_segment>>;
range_tree x_seg_tree;

struct point {
    int x;
    int y;
    int val;
};

vector<point> points;

int gcd(int X, int Y) {
    int tmp;
    while (X != Y && Y != 0) {
        tmp = X;
        X = Y;
        Y = tmp % Y;
    }
    return X;
}

y_seg_tree build_y_segs(int start_i, int end_i, const vector<point>& points) {
//    cout << "Building from " << start_i << " to " << end_i << "\n";
    int y_rows = log2(end_i - start_i - 1) + 2;
//    cout << "Rows: " << y_rows << "\n";
    y_seg_tree out(y_rows);
    out.back() = vector<segment>(1 << (y_rows - 1));
    for (int i = start_i; i != end_i; ++i) {
        out.back()[i - start_i] = {points[i].y, points[i].y, points[i].val};
    }
    for (int row = y_rows - 2; row >= 0; --row) {
        int stride = 1 << (y_rows - row - 1);
        out[row] = vector<segment>(1 << row);
        for (int i = 0; i * stride < end_i - start_i; ++i) {
//            cout << "Building x row from " << (stride * i) << " to " << (stride*(i+1)) << "\n";
            out[row][i] = {out[row + 1][2 * i].lower, out[row + 1][2 * i + 1].upper,
            gcd(out[row + 1][2 * i].val, out[row + 1][2 * i + 1].val)};
        }
    }
    return out;
}

// assume the number of points is a power of two
void rebuild_seg_tree(const vector<point>& points) {
    sort(points.begin(), points.end(), [](point a, point b){ return a.x < b.x; });
    auto S = points.size();
    int x_rows = log2(S - 1) + 2;
    range_tree x_seg_tree = vector<vector<x_segment>>(x_rows);
    x_seg_tree.back() = vector<x_segment>(1 << (x_rows - 1));
    for (int i = 0; i != S; ++i) {
        x_seg_tree[x_rows - 1][i] = {points[i].x, points[i].x, {{{points[i].y, points[i].y, points[i].val}}}};
    }
    for (int x_row = x_rows - 2; x_row >= 0; --x_row) {
        int x_skip = 1 << (x_rows - x_row - 1);
//        cout << "Attemping with x_skip = " << x_skip << "\n";
        x_seg_tree[x_row] = vector<x_segment>(1 << x_row);
        for (int i = 0; i * x_skip < S; ++i) {
//            cout << "Building y-seg from " << (i * x_skip) << " to " << (i * x_skip + x_skip) << "\n";
            inplace_merge(points.begin() + i * x_skip,
                          points.begin() + i * x_skip + x_skip / 2,
                          points.begin() + i * x_skip + x_skip,
                          [](point a, point b){ return a.x < b.x; }
                          );
            x_seg_tree[x_row][i] = {points[i * x_skip].x, points[(i + 1) * x_skip - 1].x, build_y_segs(i * x_skip, (i + 1) * x_skip, points)};
        }
    }
    return x_seg_tree;
}

int y_lookup(int i, int row, int minY, int maxY, const y_seg_tree& tree) {
    if (minY <= tree[row + 1][2 * i].lower && maxY >= tree[row + 1][2 * i + 1].upper) {
        return tree[row][i].val;
    }

    int mid1 = tree[row + 1][2 * i].upper;
    int mid2 = tree[row + 1][2 * i + 1].upper;

    int out = 0;
    if (minY <= mid1) {
        out = gcd(out, y_lookup(2 * i, row + 1, minY, min(maxY, mid1), tree));
    }
    if (maxY >= mid2) {
        out = gcd(out, y_lookup(2 * i + 1, row + 1, max(minY, mid2), maxY, tree));
    }
    return out;
}

int x_lookup(int i, int row, int minX, int maxX, int minY, int maxY, const range_tree& tree) {
    if (minX <= tree[row + 1][2 * i].lower && maxX >= tree[row + 1][2 * i + 1].upper) {
        cout << "querying with x = " << minX << "\n";
        return y_lookup(0, 0, minY, maxY, tree[row][i].val);
    }

    int mid1 = tree[row + 1][2 * i].upper;
    int mid2 = tree[row + 1][2 * i + 1].upper;

    int out = 0;
    if (minX <= mid1) {
        out = gcd(out, x_lookup(2 * i, row + 1, minX, min(maxX, mid1), minY, maxY, tree));
    }
    if (maxX >= mid2) {
        out = gcd(out, x_lookup(2 * i + 1, row + 1, max(minX, mid2), maxX, minY, maxY, tree));
    }
    return out;
}

int x_update(int i, int row, int x, int y, const range_tree& tree) {
}


int main() {
//    cin >> R >> C >> N;
    points = {{0, 0, 10}, {0, 1, 15}, {1, 0, 20}, {1, 1, 26}};
    rebuild_seg_tree();
    cout << x_lookup(0, 0, 0, 0, 0, 1);
}
