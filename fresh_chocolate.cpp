#include <bits/stdc++.h>

using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 0; t != T; ++t) {
        int N, P;
        cin >> N >> P;
        vector<int> counts(P);
        for (int i = 0; i != N; ++i) {
            int g;
            cin >> g;
            ++counts[g % P];
        }

        int out;

        if (P == 2) {
            out = counts[0] + (counts[1] + 1) / 2;
        } else if (P == 3) {
            int rem = max(counts[1], counts[2]) - min(counts[1], counts[2]);
            out = counts[0] + min(counts[1], counts[2]) + (rem + 2) / 3;
        } else if (P == 4) {
            int pairs = min(counts[1], counts[3]);
            int rem = max(counts[1], counts[3]) - pairs;
            out = counts[0] + pairs + (counts[2] + 1) / 2;
            if (counts[2] % 2) {
                rem -= 2;
            }
            if (rem) {
                out += (rem + 3) / 4;
            }

        }

        cout << "Case #" << (t + 1) << ": " << out << "\n";
    }
}
