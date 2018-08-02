#include <bits/stdc++.h>

using namespace std;

struct toy {
    int x;
    int y;
};

struct ycmp {
    bool operator()(toy t1, toy t2) {
        return t1.y < t2.y;
    }
};

int main() {
    int A, B, T;
    cin >> A >> B >> T;

    vector<int> X(A);
    vector<int> Y(B);

    for (auto& x : X) {
        cin >> x;
    }
    for (auto& x : Y) {
        cin >> x;
    }

    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());

    vector<toy> toys(T);

    for (auto& x : toys) {
        cin >> x.x >> x.y;
    }

    for (auto t : toys) {
        if ((A == 0 || t.x >= X.back()) && (B == 0 || t.y >= Y.back())) {
            cout << -1 << "\n";
            return 0;
        }
    }

    sort(toys.begin(), toys.end(), [](toy t1, toy t2) { return t1.x < t2.x; });

    int low = 0;
    int high = T;
    while (low + 1 < high) {
//        cout << low << " < t <= " << high << "\n";
        int mid = (low + high + 1) / 2;
        priority_queue<toy, vector<toy>, ycmp> y_toys;
        int i = 0;
        for (auto& x : X) {
            while (i != T && toys[i].x < x) {
                y_toys.push(toys[i]);
                ++i;
            }
            for (int j = 0; j != mid && y_toys.size() != 0; ++j) {
                y_toys.pop();
            }
        }
        while (i != T) {
            y_toys.push(toys[i]);
            ++i;
        }

        bool fail = false;

        for (int k = B - 1; k >= 0; --k) {
            for (int j = 0; j != mid && y_toys.size() != 0; ++j) {
                auto t = y_toys.top();
                if (t.y >= Y[k]) {
                    fail = true;
                    goto stop;
                } else {
                    y_toys.pop();
                }
            }
        }

        if (y_toys.size() != 0) {
            fail = true;
        }

        stop:

        if (fail) {
            low = mid;
        } else {
            high = mid;
        }
    }

    cout << high << "\n";
}
