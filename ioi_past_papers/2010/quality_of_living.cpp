#include <bits/stdc++.h>

using namespace std;

int Q[3000][3000];
int S[3000][3000];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int R, C, H, W;
    cin >> R >> C >> H >> W;
    for (int i = 0; i != R; ++i) {
        for (int j = 0; j != C; ++j) {
            cin >> Q[i][j];
        }
    }
    int low = 0;
    int high = R*C;
     while (low + 1 < high) {
        int target = (low + high) / 2;
        for (int j = 0; j != C; ++j) {
            int s = 0;
            for (int i = 0; i != R; ++i) {
                if (Q[i][j] > target) {
                    s += 1;
                } else if (Q[i][j] == target) {

                } else {
                    s -= 1;
                }
                S[i][j] = s;
            }
        }

        int best = numeric_limits<int>::max();
        for (int i = 0; i + H <= R; ++i) {
            int curr = 0;
            for (int j = 0; j != W; ++j) {
                curr += S[i + H - 1][j];
                if (i != 0) {
                    curr -= S[i - 1][j];
                }
            }
//            cout << curr << " ";
            best = min(best, curr);
            for (int j = W; j != C; ++j) {
                curr += S[i + H - 1][j];
                curr -= S[i + H - 1][j - W];
                if (i != 0) {
                    curr -= S[i - 1][j];
                    curr += S[i - 1][j - W];
                }
//                cout << curr << " ";
                best = min(best, curr);
            }
//            cout << "\n";
        }

//        cout << "best = " << best << "\n";

        if (best > 0) {
            low = target;
        } else if (best == 0) {
            low = target;
            high = target;
        } else {
            high = target;
        }
    }

    cout << high << "\n";
}
