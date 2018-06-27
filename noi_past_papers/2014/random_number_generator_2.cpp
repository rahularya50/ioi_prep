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
    map<int, pair<int, int>> lims;
    vector<int> points;
    points.reserve(N+M);
    for (int i = 1; i <= N*M && points.size() != N + M - 1; ++i) {
//        cout << "Trying " << i << "\n";
        int x1 = x[i];
        int y1 = y[i];
        auto iter1 = lims.upper_bound(x1);
        if (iter1 != lims.end() && iter1->second.first < y1) {
//            cout << "Too low\n";
            continue;
        }
        auto iter2 = iter1; // one past
        if (iter2 != lims.begin()) {
            advance(iter2, -1); // either equal or one behind
            auto iter3 = iter2;
            if (iter3->first == x1 && iter3 != lims.begin()) { // if equal and not the first
                advance(iter3, -1); // now one behind
            }
            if (iter3->first != x1 && iter3->second.second > y1) { // if not equal
//                cout << "Too high\n";
                continue;
            }
        }
        if (iter2->first != x1) {
            lims[x1] = {y1, y1};
        } else {
            iter2->second = {min(iter2->second.first, y1), max(iter2->second.second, y1)};
        }
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
