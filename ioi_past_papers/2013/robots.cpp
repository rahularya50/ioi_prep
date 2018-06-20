#include <bits/stdc++.h>

using namespace std;

int main() {
    int A, B, T;
    cin >> A >> B >> T;
    vector<int> X(A);
    for (auto& x : X) {
        cin >> x;
    }
    sort(X.begin(), X.end());
    vector<int> Y(B);
    for (auto& x : Y) {
        cin >> x;
    }
    sort(Y.begin(), Y.end());
    vector<pair<int, int>> toys(T);
    for (auto &x : toys) {
        cin >> x.first >> x.second;
    }

    vector<pair<int, int>> toy_weights(T);
    vector<pair<int, int>> toy_sizes(T);

    for (int i = 0; i != T; ++i) {
        toy_weights[i] = {toys[i].first, i};
        toy_sizes[i] = {toys[i].second, i};
    }
    sort(toy_weights.begin(), toy_weights.end());
    sort(toy_sizes.begin(), toy_sizes.end());

    // assume it's possible

    int low = 0;
    int high = T + 1;
    while (high - low > 1) {
//        cout << low << " < t <= " << high << "\n";
        int t = (low + high) / 2;
//        cout << "Trying t = " << t << "\n";

        vector<bool> skipped(T, true);
        priority_queue<pair<int, int>> todo;
        int i = 0;
        for (int curr = 0; curr != A; ++curr) {
            while (i != T && toy_weights[i].first < X[curr]) {
                todo.push({toys[toy_weights[i].second].second, toy_weights[i].second});
                ++i;
            }
            for (int j = 0; j != t; ++j) {
                if (todo.size() == 0) {
                    break;
                }
                auto x = todo.top();
                skipped[x.second] = false;
                todo.pop();
            }
        }

        bool success = true;
        int curr = B - 1;
        int cnt = 0;
        for (int i = T - 1; i >= 0; --i) {
            if (!skipped[toy_sizes[i].second]) {
                continue;
            }
            if (cnt == t) {
                cnt = 0;
                --curr;
            }
            if (curr >= 0 && toy_sizes[i].first < Y[curr]) {
                ++cnt;
//                cout << "Using small robot #" << curr << " to pick up toy #" << toy_sizes[i].second << "\n";
            } else {
                success = false;
            }
        }

        if (success) {
            high = t;
        } else {
            low = t;
        }
//        cout << (success ? "success" : "fail") << "\n";
    }

    if (high == T + 1) {
        cout << -1 << "\n";
    } else {
        cout << high << "\n";
    }
}
