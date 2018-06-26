#include <bits/stdc++.h>

using namespace std;

long long X, A, B, C, D;

void nextX() {
    X = ((((A*X) % D)*X % D) + ((B*X) % D) + C) % D;
}

int T[5000][5000];
int x[5000*5000 + 1];
short y[5000*5000 + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M, Q;
    cin >> X >> A >> B >> C >> D >> N >> M >> Q;
    for (int i = 0; i != M*N; ++i) {
        x[i + 1] = i + 1;
    }
    for (int i = 1; i <= M*N; ++i) {
        nextX();
        swap(x[i], x[X % i + 1]);
    }
    for (int q = 0; q != Q; ++q) {
        int u, v;
        cin >> u >> v;
        swap(x[u], x[v]);
    }
    for (int i = 0; i != N; ++i) {
        for (int j = 0; j != M; ++j) {
            T[i][j] = x[i*M+j+1];
        }
    }

    for (int i = 0; i != N; ++i) {
        for (int j = 0; j != M; ++j) {
            x[T[i][j]] = j;
            y[T[i][j]] = i;
        }
    }

    vector<int> out;
    map<int, int> maxes;
    map<int, int> mins;
    vector<int> points;
    points.reserve(N+M);
    for (int i = 1; i <= N*M && points.size() != N + M - 1; ++i) {
//        cout << "Trying " << i << "\n";
        int x1 = x[i];
        int y1 = y[i];
        auto iter1 = mins.upper_bound(x1);
        if (iter1 != mins.end() && iter1->second < y1) {
//            cout << "Too low\n";
            continue;
        }
        auto iter2 = maxes.lower_bound(x1);
        if (iter2 != maxes.begin()) {
            advance(iter2, -1);
            if (iter2->second > y1) {
//                cout << "Too high\n";
                continue;
            }
        }
        auto dog = maxes.find(x1);
        if (dog == maxes.end()) {
            maxes[x1] = y1;
        } else {
            dog->second = max(dog->second, y1);
        }
//        cout << "maxes[" << x << "] = " << maxes[x] << ", ";
        auto cat = mins.find(x1);
        if (cat == mins.end()) {
            mins[x1] = y1;
        } else {
            cat->second = min(cat->second, y1);
        }
//        cout << "mins[" << x << "] = " << mins[x] << "\n";
        points.push_back(i);
    }

    for (auto x1 : points) {
        cout << x1 << " ";
    }
//    cout << "\n";
//    for (int i = 0; i != N; ++i) {
//        for (int j = 0; j != M; ++j) {
//            if (find(points.begin(), points.end(), T[i][j]) != points.end()) {
//                cout << T[i][j];
//            } else {
//                cout << "___";
//            }
//            cout << " ";
//        }
//        cout << "\n";
//    }
}
