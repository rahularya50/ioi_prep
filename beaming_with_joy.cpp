#include <bits/stdc++.h>

using namespace std;

bool go(int i, int covered, int target, vector<vector<char>>& certains, const vector<pair<int, int>>& shooters, const vector<string> grid) {
    if (covered == target) {
        return true;
    }
    if (i == shooters.size()) {
        return false;
    }
    auto shooter = shooters[i];
    int r = shooter.first;
    int c = shooter.second;

    int R = grid.size();
    int C = grid.front().size();

    vector<pair<int, int>> added;
    added.reserve(max(grid.size(), grid.front().size()));
    if (certains[r][c] == '|' || certains[r][c] == 'b') {
        for (int r_temp = r + 1; r_temp != R && grid[r_temp][c] != '#'; ++r_temp) {
            if (certains[r_temp][c] == '0') {
                added.push_back({r_temp, c});
                certains[r_temp][c] = 'x';
            }
        }
        for (int r_temp = r - 1; r_temp >= 0 && grid[r_temp][c] != '#'; --r_temp) {
            if (certains[r_temp][c] == '0') {
                added.push_back({r_temp, c});
                certains[r_temp][c] = 'x';
            }
        }
        if (go(i + 1, covered + added.size(), target, certains, shooters, grid)) {
            certains[r][c] = '|';
            return true;
        }
        for (auto x : added) {
            certains[x.first][x.second] = '0';
        }
        added.clear();
    }

    if (certains[r][c] == '-' || certains[r][c] == 'b') {
        for (int c_temp = c + 1; c_temp != C && grid[r][c_temp] != '#'; ++c_temp) {
            if (certains[r][c_temp] == '0') {
                added.push_back({r, c_temp});
                certains[r][c_temp] = 'x';
            }
        }
        for (int c_temp = c - 1; c_temp >= 0 && grid[r][c_temp] != '#'; --c_temp) {
            if (certains[r][c_temp] == '0') {
                added.push_back({r, c_temp});
                certains[r][c_temp] = 'x';
            }
        }
        if (go(i + 1, covered + added.size(), target, certains, shooters, grid)) {
            certains[r][c] = '-';
            return true;
        }
        for (auto x : added) {
            certains[x.first][x.second] = '0';
        }
//        added.clear();
    }

    return false;
}

int main() {
    int T;
    cin >> T;
    for (int t = 0; t != T; ++t) {
        int R, C;
        cin >> R >> C;
        vector<string> grid;
        for (int r = 0; r != R; ++r) {
            string row;
            cin >> row;
            grid.push_back(row);
//            cout << "row registered\n";
        }

        cout << "Case #" << (t + 1) << ": ";

        vector<vector<char>> certains(R, vector<char>(C, '0'));

        bool possible = true;
        vector<pair<int, int>> shooters;

        int empties = 0;

        for (int r = 0; r != R; ++r) {
            for (int c = 0; c != C; ++c) {
                if (grid[r][c] == '.') {
                    ++empties;
                }

                if (grid[r][c] != '-' && grid[r][c] != '|') {
                    continue;
                }

                shooters.push_back({r, c});

                bool v_possible = true;
                for (int r_temp = r + 1; r_temp != R && grid[r_temp][c] != '#'; ++r_temp) {
                    if (grid[r_temp][c] == '-' || grid[r_temp][c] == '|') {
                        v_possible = false;
                    }
                }
                for (int r_temp = r - 1; r_temp >= 0 && grid[r_temp][c] != '#'; --r_temp) {
                    if (grid[r_temp][c] == '-' || grid[r_temp][c] == '|') {
                        v_possible = false;
                    }
                }

                bool h_possible = true;
                for (int c_temp = c - 1; c_temp >= 0 && grid[r][c_temp] != '#'; --c_temp) {
                    if (grid[r][c_temp] == '-' || grid[r][c_temp] == '|') {
                        h_possible = false;
                    }
                }
                for (int c_temp = c + 1; c_temp != C && grid[r][c_temp] != '#'; ++c_temp) {
                    if (grid[r][c_temp] == '-' || grid[r][c_temp] == '|') {
                        h_possible = false;
                    }
                }

                if (!h_possible && !v_possible) {
                    // Impossible
//                    cout << "IMPOSSIBLE";
                    possible = false;
                } else if (h_possible && !v_possible) {
                    certains[r][c] = '-';
                } else if (!h_possible && v_possible) {
                    certains[r][c] = '|';
                } else {
                    certains[r][c] = 'b';
                }
//                cout << r << " " << c << ": " << certains[r][c] << "\n";
            }
        }

        if (possible && go(0, 0, empties, certains, shooters, grid)) {
            cout << "POSSIBLE\n";
            for (int r = 0; r != R; ++r) {
                for (int c = 0; c != C; ++c) {
                    if (certains[r][c] == '-') {
                        cout << '-';
                    } else if (certains[r][c] == '|') {
                        cout << '|';
                    } else if (certains[r][c] == 'b') {
                        cout << '-';
                    } else {
                        cout << grid[r][c];
                    }
                }
                cout << "\n";
            }
        } else {
            cout << "IMPOSSIBLE\n";
        }







    }
}
