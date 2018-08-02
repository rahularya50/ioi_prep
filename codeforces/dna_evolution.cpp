#include <bits/stdc++.h>

using namespace std;

using data = array<int, 4>;
using segtree = vector<vector<data>>;

data lookup(int row, int i, int low, int high, const segtree& tree) {
    int step_size = 1 << (tree.size() - row - 1);
    int start_pos = step_size * i;
    int end_pos = step_size * (i + 1);
    int mid_pos = (start_pos + end_pos) / 2;

    if (low <= start_pos && end_pos <= high) {
        return tree[row][i];
    }

    data out = {};
    if (low < mid_pos) {
        out = lookup(row + 1, 2 * i, low, min(high, mid_pos), tree);
    }

    if (high > mid_pos) {
        auto x = lookup(row + 1, 2 * i + 1, max(low, mid_pos), high, tree);
        for (int j = 0; j != 4; ++j) {
            out[j] += x[j];
        }
    }

    return out;
}

void update(int row, int i, int x, data val, segtree& tree) {
    int step_size = 1 << (tree.size() - row - 1);
    int start_pos = step_size * i;
    int end_pos = step_size * (i + 1);
    int mid_pos = (start_pos + end_pos) / 2;

    if (step_size == 1) {
        tree[row][i] = val;
        return;
    }

    if (x < mid_pos) {
        update(row + 1, 2 * i, x, val, tree);
    } else {
        update(row + 1, 2 * i + 1, x, val, tree);
    }

    for (int j = 0; j != 4; ++j) {
        tree[row][i][j] = tree[row + 1][2 * i][j] + tree[row + 1][2 * i + 1][j];
    }
}

int getVal(char x) {
    switch (x) {
    case 'A':
        return 0;
    case 'T':
        return 1;
    case 'G':
        return 2;
    case 'C':
        return 3;
    }
}

const int MAXLEN = 10;

int main() {
    string S;
    cin >> S;

    int N = S.size();

    int Q;
    cin >> Q;

    vector<vector<segtree>> trees(MAXLEN);
    for (int skip = 1; skip <= MAXLEN; ++skip) {
        trees[skip - 1] = vector<segtree>(skip);
        for (int mod = 0; mod != skip; ++mod) {
//            cout << "building segtree " << mod << " % " << skip << "\n";
            int len = (N) / skip + 1;
//            cout << "len = " << len << "\n";
            int rows = log2(len) + 2;
            trees[skip - 1][mod] = vector<vector<data>>(rows);
            trees[skip - 1][mod].back() = vector<data>(1 << (rows - 1));
            for (int i = 0; skip * i + mod < N; ++i) {
                trees[skip - 1][mod].back()[i][0] = (S[skip * i + mod] == 'A');
                trees[skip - 1][mod].back()[i][1] = (S[skip * i + mod] == 'T');
                trees[skip - 1][mod].back()[i][2] = (S[skip * i + mod] == 'G');
                trees[skip - 1][mod].back()[i][3] = (S[skip * i + mod] == 'C');
            }
//            for (auto x : trees[skip - 1][mod].back()) {
//                cout << "(" << x[0] << ", " << x[1] << ", " << x[2] << ", " << x[3] << "), ";
//            }
//            cout << "\n";
//            cout << "baserow built\n";
            for (int row = rows - 2; row >= 0; --row) {
//                cout << "rows = " << rows << ", row = " << row << " ";
//                cout << "s = " << trees[skip - 1][mod].size() << ", " << (1 << row) << "\n";
                auto x = vector<data>(1 << 0);
//                cout << "ok1.5" << endl;
                trees[skip - 1][mod][row] = vector<data>(1 << row);
//                cout << "ok2" << endl;
                for (int i = 0; i != (1 << row); ++i) {
                    for (int j = 0; j != 4; ++j) {
                        trees[skip - 1][mod][row][i][j] = trees[skip - 1][mod][row + 1][2 * i][j] + trees[skip - 1][mod][row + 1][2 * i + 1][j];
                    }
                }
            }

        }
    }

    for (int q = 0; q != Q; ++q) {
        int t;
        cin >> t;
        if (t == 1) {
            // update
            int x;
            char c;
            cin >> x >> c;
            --x;
            for (int skip = 1; skip <= MAXLEN; ++skip) {
                data val = {};
                int j = getVal(c);
                val[j] = 1;
                update(0, 0, x / skip, val, trees[skip - 1][x % skip]);
            }
        } else {
            // query
            int l, r;
            cin >> l >> r;
            --l;
            --r;
            string e;
            cin >> e;
            int skip = e.size();
            int out = 0;
            for (int i = 0; i != skip; ++i) {
                if (l + i > r) {
                    continue;
                }
                int mod = (l + i) % skip;
                int len = r - l + 1;
                int offset = len % skip;
                int firstI = (l + i) / skip;
                int lastI = (len - offset) / skip + firstI;
                if (i < offset) {
                    ++lastI;
                }
                int delta = lookup(0, 0, firstI, lastI, trees[skip - 1][mod])[getVal(e[i])];
                out += delta;
//                cout << "Number of " << e[i] << "s between " << l << " <= x <= " << r << " (" << firstI << " <= i < " << lastI << ") = " << delta << "\n";
//                cout << "mod = " << mod << "\n";
            }
            cout << out << "\n";
        }
    }
}
