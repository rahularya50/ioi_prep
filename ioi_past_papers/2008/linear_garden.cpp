#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> dp[3][3];

int num(int maxV, int lastV, int rest) {
    if (rest == 0) {
        return 1;
    }
    if (dp[maxV][lastV][rest] != -1) {
        return dp[maxV][lastV][rest];
    }
    int out = 0;
    if (maxV == 2) {
        if (lastV > 0) {
            out += num(maxV, lastV - 1, rest - 1);
        }
        if (lastV < maxV) {
            out += num(maxV, lastV + 1, rest - 1);
        }
    } else {
        out += num(max(maxV, lastV + 1), lastV + 1, rest - 1);
        if (lastV == 0) {
            out += num(maxV + 1, 0, rest - 1);
        } else {
            out += num(maxV, lastV - 1, rest - 1);
        }
    }
    dp[maxV][lastV][rest] = out % M;
    return dp[maxV][lastV][rest];
}

int main() {
    cin >> N >> M;
    for (int i = 0; i != 3; ++i) {
        for (int j = 0; j != 3; ++j) {
            dp[i][j] = vector<int>(N + 1, -1);
        }
    }
    string garden;
    cin >> garden;
    int out = 0;
    int curr = 0; // #P - #L
    int minV = 0;
    int maxV = 0;
    for (int i = 0; i != N; ++i) {
        if (garden[i] == 'P') {
            // imagine we're counting all of the L---
            int minV = min(minV, curr - 1);
//            cout << "i = " << i << " max = " << maxV << " min = " << x << "\n";
            if (maxV - minV <= 2) {
                out += num(maxV - minV, curr - 1 - minV, N - i - 1);
                out %= M;
//                cout << "i = " << i << ", delta = " << num(maxV - x, curr - 1 - x, N - i - 1) << "\n";
            }
        }
        curr += (garden[i] == 'P') ? 1 : -1;
        minV = min(minV, curr);
        maxV = max(maxV, curr);
//        cout << "i = " << i << ", curr = " << curr << "\n";
    }
    cout << (out + 1) % M << "\n";
}
