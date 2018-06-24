#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (auto& x : A) {
        cin >> x;
    }
    vector<int> B(N);
    for (auto& x : B) {
        cin >> x;
    }
    int x = 0;
    vector<int> C = {0};
    for (int i = 0; i != N; ++i) {
        C.push_back(C.back() + A[i] - B[i]);
    }

    vector<vector<int>> out(N, vector<int>(N));

//    for (auto x : C) {
//        cout << x << ", ";
//    }
//    cout << "\n";

    for (int l = 0; l != N; ++l) {
        // l is start index
        map<int, int> cnt;
        int curr = 0;
        ++cnt[C[l]];
        for (int r = l + 1; r <= N; ++r) {
            ++cnt[C[r]];
            curr += cnt[C[r]] - 1;
            out[l][r - 1] = curr;
        }
    }

    int Q;
    cin >> Q;

    for (int i = 0; i != Q; ++i) {
        int l, r;
        cin >> l >> r;
        cout << out[l - 1][r - 1] << "\n";
    }
}
