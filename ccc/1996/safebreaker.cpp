#include <bits/stdc++.h>

using namespace std;

pair<int, int> compare(int num, int guess) {
    int correct = 0;
    int n = num;
    int g = guess;
    array<int, 10> n_counts = {};
    array<int, 10> g_counts = {};

    for (int i = 0; i != 4; ++i) {
        if (n % 10 == g % 10) {
            ++correct;
        }
        ++n_counts[n % 10];
        ++g_counts[g % 10];
        n /= 10;
        g /= 10;
    }

    int misplaced = 0;
    for (int i = 0; i != 10; ++i) {
        misplaced += min(n_counts[i], g_counts[i]);
    }

    misplaced -= correct;
//    cout << num << " " << guess << " " << correct << " " << misplaced << "\n";
    return {correct, misplaced};
}

int main() {
    int N;
    cin >> N;
    for (int t = 0; t != N; ++t) {
        int G;
        cin >> G;
        vector<bool> valid(10000, true);
        int possibilities = 10000;
        for (int g = 0; g != G; ++g) {
            int guess;
            cin >> guess;
            char c_correct;
            cin >> c_correct;
            char slash;
            cin >> slash;
            char c_misplaced;
            cin >> c_misplaced;
            int correct = c_correct - '0';
            int misplaced = c_misplaced - '0';
            for (int trial = 0; trial != 10000; ++trial) {
                if (!valid[trial]) {
                    continue;
                }
                auto x = compare(trial, guess);
                if (x.first != correct || x.second != misplaced) {
                    valid[trial] = false;
                    --possibilities;
                }
            }
        }
        if (possibilities == 0) {
            cout << "impossible\n";
        } else if (possibilities > 1) {
            cout << "indeterminate\n";
        } else {
            for (int i = 0; i != 10000; ++i) {
                if (valid[i]) {
                    cout << setfill('0') << setw(4) << i << "\n";
                    break;
                }
            }
        }
    }
}
