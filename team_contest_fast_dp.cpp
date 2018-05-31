#include <bits/stdc++.h>

using namespace std;

int PROGS = 8;

int main() {
    ios::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;

    vector<pair<long long, int>> s;
    s.reserve(N);
    for (int i = 0; i != N; ++i) {
        long long temp;
        cin >> temp;
        s.push_back({temp, i});
    }

    vector<long long> t;
    t.reserve(M);
    for (int i = 0; i != M; ++i) {
        long long temp;
        cin >> temp;
        t.push_back(temp);
    }

    sort(s.begin(), s.end(), greater<pair<int, int>>());

    vector<long long> bests;
    for (int i = 0; i != PROGS && i != s.size(); ++i) {
        bests.push_back(s[i].first);
    }

    int num = bests.size();
//  getchar();

    vector<vector<pair<long long, int>>> dp(M + 1, vector<pair<long long, int>>(num * num * num, {-1, -1}));
    dp[0] = vector<pair<long long, int>>(num * num * num, {0, -1});

    for (int i = 0; i != M; ++i) {
        for (int j = 0; j != num * num * num; ++j) {
            int first = j % num;
            int second = (j / num) % num;
            int third = (j / num / num) % num;
//            cout << i << " " << first << second << third << " " << dp[i][j].first << " " << dp[i][j].second << "\n";

            for (int next_prog = 0; next_prog != num; ++next_prog) {
                if (next_prog == first || next_prog == second || next_prog == third) {
                    continue;
                }
                int next_j = (j * num) % (num * num * num) + next_prog;
                long long prog_score = (bests[next_prog] < t[i]) ? 0 : t[i] * (bests[next_prog] - t[i]);
//                cout << prog_score << "\n";
                dp[i + 1][next_j] = max(dp[i + 1][next_j], {dp[i][j].first + prog_score, j});
            }
        }
//        getchar();
    }

    auto h = (max_element(dp.back().begin(), dp.back().end()) - dp.back().begin());

    cout << dp.back()[h].first << "\n";

    vector<int> progs;
    progs.reserve(M);
    for (int i = M; i > 0; --i) {
        progs.push_back(h % num);
        h = dp[i][h].second;
    }

    for (int i = progs.size() - 1; i >= 0; --i) {
        cout << (s[progs[i]].second + 1) << " ";
    }
}
