#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    int max_exp = static_cast<int>(log2(N));
    vector<int> counts(max_exp + 1);
    int remain = N;
    int cnt = 0;
    while (remain) {
        int exp = static_cast<int>(log2(remain));
        ++counts[exp];
        remain -= (1 << exp);
        ++cnt;
    }
    while (cnt < M) {
        --counts[max_exp];
        counts[max_exp - 1] += 2;
        if (counts[max_exp] == 0) {
            --max_exp;
        }
        ++cnt;
    }
    for (int i = 0; i != counts.size(); ++i) {
        for (int j = 0; j != counts[i]; ++j) {
            cout << (1 << i) << "\n";
        }
    }
}
