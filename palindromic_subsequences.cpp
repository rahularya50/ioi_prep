#include <bits/stdc++.h>
using namespace std;
string S;
pair<long long, long long> go(int a, int b, const vector<pair<long long, long long>>& prev1, const vector<pair<long long, long long>>& prev2) {
    if (a > b) {
        return {0, 0};
    }
    pair<long long, long long> out = {0, 0};
    if (S[a] == S[b]) {
        auto x = prev2[a + 1];
        out.first += x.first + static_cast<long long>(a == b);
        out.second += x.second + static_cast<long long>(a != b);
    }
        auto x = prev1[a + 1];
        auto y = prev1[a];
        auto z = prev2[a + 1];
        out.first += x.first + y.first - z.first;
        out.second += x.second + y.second - z.second;
    out.first %= 1000000007;
    out.second %= 1000000007;
    return out;
}
int main() {
    ios::sync_with_stdio(false);
    getline(cin, S);
    int N = S.size();
    vector<pair<long long, long long>> prev1(N + 1);
    vector<pair<long long, long long>> prev2(N + 1);
    vector<pair<long long, long long>> curr(N + 1);
    for (int i = 0; i != N; ++i) {
        for (int j = 0; i + j != N; ++j) {
            curr[j] = go(j, i + j, prev1, prev2);
        }
        prev2 = move(prev1);
        prev1 = move(curr);
        curr = vector<pair<long long, long long>>(N + 1);
    }
    cout << ((prev1[0].first + 1000000007) % 1000000007) << " " << ((prev1[0].second + 1000000007) % 1000000007);
}
