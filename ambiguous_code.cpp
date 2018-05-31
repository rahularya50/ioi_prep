#include <bits/stdc++.h>

using namespace std;

struct node {
    int left;
    int right;
    int depth;
    bool is_terminal;
};

int main() {
    int N;
    cin >> N;
    vector<node> trie;
    vector<pair<int, int>> terminals;
    trie.push_back({-1, -1, 0, false});
    for (int i = 0; i != N; ++i) {
        string codeword;
        cin >> codeword;
        int pos = 0;
        for (int j = 0; j != codeword.size(); ++j) {
            auto x = codeword[j];
//            cout << pos << ", ";
            int& new_pos = (x == '0') ? trie[pos].left : trie[pos].right;
//            cout << new_pos << ", ";
            if (new_pos == -1) {
//                cout << trie.size() << ", ";
                new_pos = trie.size();
                pos = new_pos;
                trie.push_back({-1, -1, j + 1, false});
            } else {
                pos = new_pos;
            }
//            cout << pos << ", ";
//            cout << "\n";
        }
        trie[pos].is_terminal = true;
        terminals.push_back({pos, codeword.size()});
    }

    vector<vector<pair<int, int>>> recs(trie.size());
    vector<vector<int>> dp(trie.size(), vector<int>(trie.size(), -1));

    for (int i = 0; i != trie.size(); ++i) {
        vector<pair<pair<int, int>, int>> tovisit = {{{0, i}, trie[i].depth}};
        int best = -1;
        while (tovisit.size() > 0) {
            auto a = tovisit.back().first;
            auto b = tovisit.back().second;
            tovisit.pop_back();
            if (a.first == -1 || a.second == -1) {
                continue;
            }
//            cout << "Visiting (" << a.first << ", " << a.second << ")\n";
            if (trie[a.first].is_terminal && trie[a.second].is_terminal) {
                best = (best == -1) ? b : min(best, b);
            } else {
                if (trie[a.first].is_terminal) {
//                    cout << "Recursing: (" << a.first << ", " << a.second << ") -> " << "(0, " << a.second << ") + " << b << ")\n";
                    recs[i].push_back({a.second, b});
                }
                if (trie[a.second].is_terminal) {
//                    cout << "Recursing: (" << a.first << ", " << a.second << ") -> " << "(0, " << a.first << ") + " << b << ")\n";
                    recs[i].push_back({a.first, b});
                }
            }
            tovisit.push_back({{trie[a.first].left, trie[a.second].left}, b + 1});
            tovisit.push_back({{trie[a.first].right, trie[a.second].right}, b + 1});
        }
        dp[0][i] = best;
        cout << "dp[0][" << i << "] = " << best << "\n";
    }

    for (int i = 1; i != trie.size(); ++i) {
        for (int j = 0; j != trie.size(); ++j) {
            int best = dp[i - 1][j];
            for (auto x : recs[j]) {
                if (dp[i - 1][x.first] == -1) {
                    continue;
                }
                auto val = (dp[i - 1][x.first] + x.second);
                best = (best == -1) ? val : min(best, val);
            }
            dp[i][j] = best;
            cout << "dp[" << i << "][" << j << "] = " << best << "\n";
        }
    }

    for (auto t : terminals) {
        cout << dp[trie.size() - 1][t.first] << " ";
    }

}
