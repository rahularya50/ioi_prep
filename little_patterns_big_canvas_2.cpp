#include <bits/stdc++.h>

using namespace std;

int main() {
    while (true) {
    long long N;
    cin >> N;
    vector<long long> p(N);
    vector<int> children(N);
    for (long long i = 0; i != N; ++i) {
        cin >> p[i];
        --p[i];
        if (p[i] != -1) {
            ++children[p[i]];
        }
    }
    vector<long long> s(N, 1);
    for (auto& x : s) {
        cin >> x;
    }
    vector<int> leaves;
    for (int i = 0; i != N; ++i) {
        if (children[i] == 0) leaves.push_back(i);
    }
    int cnt = 0;
    vector<bool> used(N);
    for (int i = 0; i != leaves.size(); ++i) {
        auto x = leaves[i];
        if (p[x] != -1 && !used[x] && !used[p[x]]) {
            ++cnt;
            used[x] = true;
            used[p[x]] = true;
            if (p[p[x]] != -1) {
                --children[p[p[x]]];
                if (children[p[p[x]]] == 0) {
                    leaves.push_back(p[p[x]]);
                }
            }
        }
    }

    cout << N - cnt << "\n";
    }
}
