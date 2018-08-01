#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> out;
vector<vector<int>> H;
vector<vector<int>> V;

int R, C;

int recompute() {
    vector<int> prev(C);
    vector<int> left(C);
    vector<int> right(C);
    vector<int> opt(C);

    for (int dest = 0; dest != C; ++dest) {
        int dist = 0;
        for (int x = dest; x != C; ++x) {
            prev[x] = dist;
            if (x != C - 1) {
                dist += H[R - 1][x];
            }
        }
        dist = 0;
        for (int x = dest; x >= 0; --x) {
            prev[x] = dist;
            if (x != 0) {
                dist += H[R - 1][x - 1];
            }
        }
        for (int r = R - 2; r >= 0; --r) {
            int best = numeric_limits<int>::max();
            for (int c = 0; c != C; ++c) {
                auto x = V[r][c] + prev[c];
                best = min(x, best);
                left[c] = best;
                if (c != C - 1) {
                    best += H[r][c];
                }
            }

            best = numeric_limits<int>::max();
            for (int c = C - 1; c >= 0; --c) {
                auto x = V[r][c] + prev[c];
                best = min(x, best);
                right[c] = best;
                if (c != 0) {
                    best += H[r][c - 1];
                }
            }

            for (int c = 0; c != C; ++c) {
                opt[c] = min(left[c], right[c]);
            }

//            for (auto x : prev) {
//                cout << x << " ";
//            }
//            cout << "\n";
            swap(opt, prev);
        }
//        for (auto x : prev) {
//            cout << x << " ";
//        }
//        cout << "\n\n";
        swap(prev, out[dest]);
    }
}

int main() {
    cin >> R >> C;

    H = vector<vector<int>>(R, vector<int>(C - 1));
    V = vector<vector<int>>(R - 1, vector<int>(C));

    for (int i = 0; i != R; ++i) {
        for (int j = 0; j != C - 1; ++j) {
            cin >> H[i][j];
        }
    }

    for (int i = 0; i != R - 1; ++i) {
        for (int j = 0; j != C; ++j) {
            cin >> V[i][j];
        }
    }

    int E;
    cin >> E;

    out = vector<vector<int>>(C, vector<int>(C)); // need to maintain out

    recompute();

    // assume few changes or few columns i.e. O(R*C^2*N)
    for (int e = 0; e != E; ++e) {
        int x;
        cin >> x;
        if (x == 1) {
            int P, Q, W;
            cin >> P >> Q >> W;
            H[P][Q] = W;
            recompute();
        }
        else if (x == 2) {
            int P, Q, W;
            cin >> P >> Q >> W;
            V[P][Q] = W;
            recompute();
        } else {
            int v1, v2;
            cin >> v1 >> v2;
            cout << out[v2][v1] << "\n";
        }
    }
}
