#include <bits/stdc++.h>

using namespace std;

int tryCombination(int S[]);

void answer(int S[], int D[]);

void exploreCave(int N) {
    vector<int> S(N);
    vector<int> D(N);

    vector<int> fixed(N, -1); // doors fixed open

    vector<int> submission(N);

    for (int i = 0; i != N; ++i) {
        // figure out whether the switch should be raised or lowered
        for (int j = 0; j != N; ++j) {
            if (fixed[j] != -1) {
                submission[j] = fixed[j];
            } else {
                submission[j] = 0; // let's try 0 (up)
            }
        }

        auto x = tryCombination(submission.data());

        int pos;
        if (x == i) {
            pos = 1;
        } else {
            pos = 0;
        }

        // figure out who opens door i and how to open it
        int low = 0;
        int high = N;
        while (low + 1 < high) {
            int mid = (low + high) / 2;
            for (int j = 0; j != N; ++j) {
                if (fixed[j] != -1) {
                    submission[j] = fixed[j];
                } else if (j < mid) {
                    submission[j] = pos;
                } else {
                    submission[j] = 1 - pos;
                }
            }

            auto x = tryCombination(submission.data());
            if (x == i) {
                low = mid;
            } else {
                high = mid;
            }
        }

        D[low] = i;
        fixed[low] = pos;
        S[low] = pos;
    }

    answer(&S[0], &D[0]);
}
