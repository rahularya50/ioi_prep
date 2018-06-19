#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, T, P;
    cin >> N >> T >> P;
    vector<int> cnt(T);
    vector<vector<int>> contestants(N);
    for (int i = 0; i != N; ++i) {
        for (int j = 0; j != T; ++j) {
            int x;
            cin >> x;
            if (x == 1) {
                ++cnt[j];
                contestants[i].push_back(j);
            }
        }
    }
    vector<int> c;
    for (int i = 0; i != N; ++i) {
        c.push_back(i);
    }
    stable_sort(c.begin(), c.end(), [&](int a, int b) { return contestants[a].size() > contestants[b].size(); });
    vector<int> scores(N);
    for (int i = 0; i != N; ++i) {
        for (auto x : contestants[i]) {
            scores[i] += (N - cnt[x]);
        }
    }
    stable_sort(c.begin(), c.end(), [&](int a, int b) { return scores[a] > scores[b]; });

    cout << scores[P - 1] << " ";
    for (int i = 0; i != c.size(); ++i) {
        if (c[i] == P - 1) {
            cout << i + 1;
            return 0;
        }
    }
}
