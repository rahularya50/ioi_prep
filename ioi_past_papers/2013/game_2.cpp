#include <bits/stdc++.h>

using namespace std;

using y_tree = vector<vector<long long>>;
using x_tree = vector<vector<y_tree>>;

long long gcd(long long X, long long Y) {
    long long tmp;
//    cout << "gcd of " << X << " and " << Y << "is = ";
    while (X != Y && Y != 0) {
        tmp = X;
        X = Y;
        Y = tmp % Y;
    }
//    cout << X << "\n";
    return X;
}

void y_update(long long i, long long row, long long y, long long val, long long prev_i, long long prev_row, x_tree& tree1) {
    auto& tree2 = tree1[prev_row][prev_i];

    long long step_size = 1 << (tree2.size() - row - 1);
    long long start_pos = i * step_size;
    long long end_pos = (i + 1) * step_size;
    long long mid_pos = (start_pos + end_pos) / 2;
//    cout << "Considering block where " << start_pos << " <= y < " << end_pos << "\n";

    if (step_size == 1 && prev_row == tree1.size() - 1) {
        tree2[row][i] = val;
//        cout << "Updating block wherex " << start_pos << " <= y < " << end_pos << " to " << tree2[row][i] << "\n";
        return;
    }

    if (step_size != 1) {
        if (y < mid_pos) {
            y_update(i * 2, row + 1, y, val, prev_i, prev_row, tree1);
        } else  {
            y_update(i * 2 + 1, row + 1, y, val, prev_i, prev_row, tree1);
        }
    }

    if (prev_row == tree1.size() - 1) {
        // thin segtree
        tree2[row][i] = gcd(tree2[row + 1][i * 2], tree2[row + 1][i * 2 + 1]);
    } else {
        // thick segtree
//        cout << prev_row+1 << " " << 2*i << "\n";
        tree2[row][i] = gcd(tree1[prev_row + 1][2 * prev_i][row][i], tree1[prev_row + 1][2 * prev_i + 1][row][i]);
    }
//    cout << "Updating block where " << start_pos << " <= y < " << end_pos << " to " << tree2[row][i] << "\n";

}

void update2(long long i, long long row, long long val, long long x, long long y, x_tree& tree) {
    long long step_size = 1 << (tree.size() - row - 1);
    long long start_pos = i * step_size;
    long long end_pos = (i + 1) * step_size;
    long long mid_pos = (start_pos + end_pos) / 2;

    if (step_size != 1) {
        if (x < mid_pos) {
            update2(i * 2, row + 1, val, x, y, tree);
        } else  {
            update2(i * 2 + 1, row + 1, val, x, y, tree);
        }
    }

//    cout << "Considering segtree for " << start_pos << " <= x < " << end_pos << "\n";

    y_update(0, 0, y, val, i, row, tree);
}

long long y_lookup(long long i, long long row, long long minY, long long maxY, const y_tree& tree) {
    long long step_size = 1 << (tree.size() - row - 1);
    long long start_pos = i * step_size;
    long long end_pos = (i + 1) * step_size;
    long long mid_pos = (start_pos + end_pos) / 2;

//    cout << "Considering block where " << start_pos << " <= y < " << end_pos << ", targeting " << minY << " <= y < " << maxY << "\n";

    if (minY <= start_pos && maxY >= end_pos) {
        return tree[row][i];
    }

    long long out = 0;
    if (minY < mid_pos) {
        out = gcd(out, y_lookup(i * 2, row + 1, minY, min(maxY, mid_pos), tree));
    }
    if (maxY > mid_pos) {
        out = gcd(out, y_lookup(i * 2 + 1, row + 1, max(mid_pos, minY), maxY, tree));
    }
    return out;

}

long long lookup(long long i, long long row, long long minX, long long maxX, long long minY, long long maxY, const x_tree& tree) {
    long long step_size = 1 << (tree.size() - row - 1);
    long long start_pos = i * step_size;
    long long end_pos = (i + 1) * step_size;
    long long mid_pos = (start_pos + end_pos) / 2;

//    cout << "Considering segtree for " << start_pos << " <= x < " << end_pos << "\n";

    if (minX <= start_pos && maxX >= end_pos) {
        return y_lookup(0, 0, minY, maxY, tree[row][i]);
    }

    long long out = 0;
    if (minX < mid_pos) {
        out = gcd(out, lookup(i * 2, row + 1, minX, min(maxX, mid_pos), minY, maxY, tree));
    }
    if (maxX > mid_pos) {
        out = gcd(out, lookup(i * 2 + 1, row + 1, max(mid_pos, minX), maxX, minY, maxY, tree));
    }
    return out;
}

x_tree tree;

void init(int R, int C) {
    long long y_rows = log2(C) + 2;
    y_tree y_base(y_rows);
    for (long long y_row = 0; y_row != y_rows; ++y_row) {
        y_base[y_row] = vector<long long>(1 << y_row);
    }

    long long x_rows = log2(R) + 2;
    tree = x_tree(x_rows);
    for (long long x_row = 0; x_row != x_rows; ++x_row) {
        tree[x_row] = vector<y_tree>(1 << x_row);
        for (long long i = 0; i != (1 << x_row); ++i) {
            tree[x_row][i] = y_base;
        }
    }
}

void update(int p, int q, long long k) {
    update2(0, 0, k, p, q, tree);
}

long long calculate(int p, int q, int u, int v) {
    return lookup(0, 0, p, u + 1, q, v + 1, tree);
}

//
//int main() {
//    init(2, 3);
//    update(0, 0, 20);
//    update(0, 2, 15);
//    update(1, 1, 12);
//    cout << calculate(0, 0, 0, 2) << "\n";
//    cout << calculate(0, 0, 1, 1) << "\n";
//    update(0, 1, 6);
//    update(1, 1, 14);
//    cout << calculate(0, 0, 0, 2) << "\n";
//    cout << calculate(0, 0, 1, 1) << "\n";
//}
