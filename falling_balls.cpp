#include <bits/stdc++.h>

using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 0; t != T; ++t) {
        int C;
        cin >> C;

        vector<int> top;
        for (int i = 0; i != C; ++i) {
            int x;
            cin >> x;
            top.push_back(x);
        }

        cout << "Case #" << (t + 1) << ": ";

        if (top.front() == 0 || top.back() == 0) {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        vector<pair<pair<int, int>, int>> mapping; // interval -> target pos mapping
        int curr = 0;
        for (int i = 0; i != C; ++i) {
            if (top[i] == 0) {
                continue;
            }
            mapping.push_back({{curr, curr + top[i]}, i});
            curr += top[i];
        }

        if (curr != C) {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        bool fail = false;

        vector<vector<char>> rows;
        for (auto x : mapping) {
            int needed = max(x.first.second - x.second - 1, x.second - x.first.first);
            int lbound = x.first.first;
            int rbound = x.first.second;
            for (int i = 0; i != needed; ++i) {
                if (rows.size() == i) {
                    rows.push_back(vector<char>(C, 'x'));
                }
                for (int j = lbound; j < rbound; ++j) {
                    if (rows[i][j] != 'x') {
                        fail = true;
                    }
                    if (j < x.second) {
                        rows[i][j] = '\\';
                    } else if (j == x.second) {
                        rows[i][j] = '.';
                    } else {
                        rows[i][j] = '/';
                    }
                }
                if (x.second > lbound) {
                    ++lbound;
                } else if (x.second < lbound) {
                    --lbound;
                }
                if (x.second < (rbound - 1)) {
                    --rbound;
                } else if (x.second > (rbound - 1)) {
                    ++rbound;
                }
            }
//            cout << "setting maxX = " << maxX << "\n";

//            cout << "RIGHT NOW: \n";
//            for (auto x : rows) {
//                for (int i = 0; i != x.size(); ++i) {
//                    cout << ((x[i] == 'x') ? '.' : x[i]);
//                }
//                for (int i = x.size(); i != C; ++i) {
//                    cout << '.';
//                }
//                cout << "\n";
//            }

        }
        rows.push_back(vector<char>(C, '.'));

        if (fail) {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        cout << rows.size() << "\n";
        for (auto x : rows) {
            for (int i = 0; i != x.size(); ++i) {
                cout << ((x[i] == 'x') ? '.' : x[i]);
            }
            for (int i = x.size(); i != C; ++i) {
                cout << '.';
            }
            cout << "\n";
        }
    }
}
