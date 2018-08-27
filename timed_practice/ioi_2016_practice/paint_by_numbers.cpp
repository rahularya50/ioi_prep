#include "bits/stdc++.h"

using namespace std;

int N;
vector<int> C;
string out;
string S;
vector<vector<int>> cache;

// move forward only!
// TODO: impose bounds checking on pos
bool is_possible(int i, int start_pos) {
    if (cache[i][start_pos] != -1) {
        return cache[i][start_pos];
    }
//    cout << "is_possible[" << i << "][" << start_pos << "] in progress! \n";
    // let's see if we can even place it
    if (start_pos + C[i] > N) {
        cache[i][start_pos] = false;
        return false;
    }
    for (int pos = start_pos; pos != start_pos + C[i]; ++pos) {
        if (S[pos] == '_') {
            cache[i][start_pos] = false;
            return false;
        }
    }
    if (start_pos + C[i] != N && S[start_pos + C[i]] == 'X') {
        cache[i][start_pos] = false;
        return false;
    }
    if (i != C.size() - 1) {
        bool ok = false;
        for (int next_start = start_pos + C[i] + 1; next_start < N; ++next_start) {
            if (is_possible(i + 1, next_start)) {
                ok = true;
                break;
            }
            if (S[next_start] == 'X') {
                // we can't skip this one
                break;
            }
        }
        if (!ok) {
            cache[i][start_pos] = false;
            return false;
        }
    } else {
        for (int pos = start_pos + C[i]; pos != N; ++pos) {
            if (S[pos] == 'X') {
                cache[i][start_pos] = false;
                return false;
            }
        }
    }
    cache[i][start_pos] = true;
    return true;
}

string solve_puzzle(string s, vector<int> c) {
//    cout << "solving!" << "\n";
    N = s.size();
    C = c;
    S = s;
    out = S;
    for (int i = 0; i != N; ++i) {
//        cout << "Considering i = " << i << "\n";
        if (S[i] != '.') {
            continue;
        }
        S[i] = 'X';
        cache = vector<vector<int>>(C.size(), vector<int>(N, -1));
        bool can_black = false;
        for (int pos = 0; pos != N; ++pos) {
            if (is_possible(0, pos)) {
                can_black = true;
//                cout << "pos = " << pos << " is b_feasible!\n";
                break;
            }
            if (S[pos] == 'X') {
                break;
            }
        }
        S[i] = '_';
        bool can_white = false;
        cache = vector<vector<int>>(C.size(), vector<int>(N, -1));
        for (int pos = 0; pos != N; ++pos) {
            if (is_possible(0, pos)) {
                can_white = true;
//                cout << "pos = " << pos << " is w_feasible!\n";
                break;
            }
            if (S[pos] == 'X') {
                break;
            }
        }

        S[i] = '.';
        if (can_black && can_white) {
            out[i] = '?';
        } else if (can_black) {
            out[i] = 'X';
        } else if (can_white) {
            out[i] = '_';
        }
    }

    return out;
}
//
//int main() {
//    string s;
//    cin >> s;
//    int k;
//    cin >> k;
//    vector<int> c(k);
//    for (auto& x : c) {
//        cin >> x;
//    }
//    cout << solve_puzzle(s, c) << "\n";
//}
