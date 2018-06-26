#include <bits/stdc++.h>

using namespace std;

int X, A, B, C, D;

void nextX() {
    X = (A*X*X + B*X + C) % D;
}

int T[500][500];
int vals[500*500 + 1];

using y_tree = vector<vector<pair<int, pair<int, int>>>>;
using x_tree = vector<vector<y_tree>>;

x_tree tree;

void insert_y(int row, int i, int x, int y, int val, y_tree& yt) {
    yt[row][i] = min(pair<int, pair<int, int>>({val, {x, y}}), yt[row][i]);
    int step_size = 1 << (yt.size() - 1 - row);
    int start_pos = step_size * i;
    int end_pos = step_size * (i + 1);
    int mid_pos = (start_pos + end_pos) / 2;
//    cout << "inserting in " << start_pos << " <= y < " << end_pos << "\n";

    if (step_size == 1) {
        return;
    }

    if (y < mid_pos) {
        insert_y(row + 1, 2 * i, x, y, val, yt);
    } else {
        insert_y(row + 1, 2 * i + 1, x, y, val, yt);
    }
}

void insert_x(int row, int i, int x, int y, int val) {
    int step_size = 1 << (tree.size() - 1 - row);
    int start_pos = step_size * i;
    int end_pos = step_size * (i + 1);
    int mid_pos = (start_pos + end_pos) / 2;
//    cout << "INSERTING in " << start_pos << " <= x < " << end_pos << "\n";
    insert_y(0, 0, x, y, val, tree[row][i]);

    if (step_size == 1) {
        return;
    }

    if (x < mid_pos) {
        insert_x(row + 1, 2 * i, x, y, val);
    } else {
        insert_x(row + 1, 2 * i + 1, x, y, val);
    }
}

pair<int, pair<int, int>> query_y(int row, int i, int minY, int maxY, y_tree& yt) {
    int step_size = 1 << (yt.size() - 1 - row);
    int start_pos = step_size * i;
    int end_pos = step_size * (i + 1);
    int mid_pos = (start_pos + end_pos) / 2;

    if (minY <= start_pos && end_pos <= maxY) {
        return yt[row][i];
    }

    pair<int, pair<int, int>> best = {numeric_limits<int>::max(), {0, 0}};
    if (minY < mid_pos) {
        best = min(best, query_y(row + 1, 2 * i, minY, min(mid_pos, maxY), yt));
    }
    if (maxY > mid_pos) {
        best = min(best, query_y(row + 1, 2 * i + 1, max(minY, mid_pos), maxY, yt));
    }
    return best;
}

pair<int, pair<int, int>> query_x(int row, int i, int minX, int maxX, int minY, int maxY) {
    int step_size = 1 << (tree.size() - 1 - row);
    int start_pos = step_size * i;
    int end_pos = step_size * (i + 1);
    int mid_pos = (start_pos + end_pos) / 2;

    if (minX <= start_pos && end_pos <= maxX) {
        return query_y(0, 0, minY, maxY, tree[row][i]);
    }

    pair<int, pair<int, int>> best = {numeric_limits<int>::max(), {0, 0}};
    if (minX < mid_pos) {
        best = min(best, query_x(row + 1, 2 * i, minX, min(mid_pos, maxX), minY, maxY));
    }
    if (maxX > mid_pos) {
        best = min(best, query_x(row + 1, 2 * i + 1, max(mid_pos, minX), maxX, minY, maxY));
    }

    return best;
}


int main() {
    int N, M, Q;
    cin >> X >> A >> B >> C >> D >> N >> M >> Q;
    for (int i = 0; i != M*N; ++i) {
        vals[i + 1] = i + 1;
    }
    for (int i = 1; i <= M*N; ++i) {
        nextX();
        swap(vals[i], vals[X % i + 1]);
    }
    for (int q = 0; q != Q; ++q) {
        int u, v;
        cin >> u >> v;
        swap(vals[u], vals[v]);
    }
    for (int i = 0; i != N; ++i) {
        for (int j = 0; j != M; ++j) {
            T[i][j] = vals[i*M+j+1];
        }
    }

    int x_rows = log2(N - 1) + 2;
    int y_rows = log2(M - 1) + 2;
    tree = x_tree(x_rows);
    auto def_y = y_tree(y_rows);
    for (int row = y_rows - 1; row >= 0; --row) {
        def_y[row] = vector<pair<int, pair<int, int>>>(1 << row, {numeric_limits<int>::max(), {0, 0}});
    }
    for (int row = x_rows - 1; row >= 0; --row) {
        tree[row] = vector<y_tree>(1 << row, def_y);
    }

    for (int i = 0; i != N; ++i) {
        for (int j = 0; j != M; ++j) {
//            cout << "inserting (" << i << ", " << j << ") = " << T[i][j] << "\n";
            insert_x(0, 0, i, j, T[i][j]);
        }
    }

//    for (int i = 0; i != N; ++i) {
//        for (int j = 0; j != M; ++j) {
//            cout << query_x(0, 0, 0, i + 1, 0, j + 1).first << " ";
//        }
//        cout << "\n";
//    }


}
