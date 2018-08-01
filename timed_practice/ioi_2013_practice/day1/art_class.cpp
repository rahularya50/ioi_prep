#include <bits/stdc++.h>

using namespace std;

int getR(int RGB) { return (RGB >> 16) & 0xFF; }
int getG(int RGB) { return (RGB >> 8) & 0xFF; }
int getB(int RGB) { return RGB & 0xFF; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
//    T = 1;
    for (int t = 0; t != T; ++t) {
        int H, W;
        cin >> H >> W;
        long long maxes[3] = {0, 0, 0};
        long long mins[3] = {0, 0, 0};
        long long sums[3] = {0, 0, 0};
        long long diffs[3] = {0, 0, 0};
        int prev[3] = {0, 0, 0};
        for (int y = 0; y != H; ++y) {
            for (int x = 0; x != W; ++x) {
                int p;
                cin >> p;
                auto r = getR(p);
                auto g = getG(p);
                auto b = getB(p);
                auto m = max({r, g, b});
                auto s = min({r, g, b});

                maxes[0] += (r == m);
                maxes[1] += (g == m);
                maxes[2] += (b == m);

                mins[0] += (r == s);
                mins[1] += (g == s);
                mins[2] += (b == s);

                sums[0] += r;
                sums[1] += g;
                sums[2] += b;

                diffs[0] += (r - prev[0]) * (r - prev[0]);
                diffs[1] += (g - prev[1]) * (g - prev[1]);
                diffs[2] += (b - prev[2]) * (b - prev[2]);

                prev[0] = r;
                prev[1] = g;
                prev[2] = b;
            }
        }

//        cout << "Maxes: \n";
//        cout << maxes[0] << "\n" << maxes[1] << "\n" << maxes[2] << "\n";
//
//        cout << "Mins: \n";
//        cout << mins[0] << "\n" << mins[1] << "\n" << mins[2] << "\n";
//
//
//        cout << "Sums: \n";
//        cout << sums[0] << "\n" << sums[1] << "\n" << sums[2] << "\n";

        auto diffval = static_cast<long double>(diffs[0] + diffs[1] + diffs[2]) / (H * W);

//        cout << "Diffs: \n";
//        cout << diffval << "\n";

        if (diffval < 200) {
            cout << 4 << "\n";
        } else if (diffval > 3000) {
            cout << 3 << "\n";
        } else if (maxes[2] * 2 < maxes[1] && maxes[2] * 2 < maxes[0]) {
            cout << 2 << "\n";
        } else {
            cout << 1 << "\n";
        }
    }
}
