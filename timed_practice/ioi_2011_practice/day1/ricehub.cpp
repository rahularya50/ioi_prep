#include <bits/stdc++.h>

using namespace std;

int SHIFT = 20;

int main() {
    long long R, L, B;
    cin >> R >> L >> B;

    vector<long long> X(R);
    for (auto& x : X) {
        cin >> x;
    }

    vector<long long> run_sum = {0};
    for (auto x : X) {
        run_sum.push_back(run_sum.back() + x);
    }

    vector<long long> X_nondup = X;
    for (long long i = 0; i != R; ++i) {
        X_nondup[i] <<= SHIFT;
        X_nondup[i] += i;
    }

    long long best = 0;

    for (long long i = 0; i != R; ++i) {
        auto center = X_nondup[i];
//        cout << "center = " << center << "\n";
        long long low = -1;
        long long high = L << SHIFT;
        long long curr;
        while (low + 1 < high) {
            long long mid = (low + high) / 2;
//            cout << "trying d = " << mid << " ";
//            cout << "(" << center - mid << " <= x <= " << center + mid << ")\n";
            auto x = distance(X_nondup.begin(), lower_bound(X_nondup.begin(), X_nondup.end(), center - mid)); // smallest number >= that's lower_bound
            auto y = distance(X_nondup.begin(), upper_bound(X_nondup.begin(), X_nondup.end(), center + mid)) - 1; // largest number <= that's upper_bound - 1

//            cout << "low = " << X[x] << ", high = " << X[y] << "\n";


            auto cost = X[i] * (i - x) - (run_sum[i] - run_sum[x]) + (run_sum[y + 1] - run_sum[i + 1]) - X[i] * (y - i);
//            cout << "cost = " << cost << "\n";

            if (cost > B) {
                high = mid;
            } else {
                curr = y - x + 1;
//                cout << "curr = " << curr << "\n";
                low = mid;
            }
        }

        best = max(best, curr);
    }

    cout << best << "\n";
}
