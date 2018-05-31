#include <bits/stdc++.h>

using namespace std;


vector<vector<int>> helper(int M, int cap, vector<vector<int>> sofar, int len) {
    if (len == M) {
        return sofar;
    }

    vector<vector<int>> out;
    for (auto x : sofar) {
        for (int i = 0; i != cap; ++i) {
            bool fail = false;
            for (int j = 0; j != 3; ++j) {
                if (len > j && x[len - j - 1] == i) {
                    fail = true;
//                    cout << i << " " << x[len - j] << "\n";
                    break;
                }
            }
            if (!fail) {
                out.push_back(x);
                out.back().push_back(i);
            }
        }
    }

    return helper(M, cap, out, len + 1);
}


vector<vector<int>> make(int M, int cap) {// We will try the top M programmers only.
    return helper(M, cap, {{}}, 0);
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> s;
    for (int i = 0; i != N; ++i) {
        int temp;
        cin >> temp;
        s.push_back(temp);
    }
    vector<int> t;
    for (int i = 0; i != M; ++i) {
        int temp;
        cin >> temp;
        t.push_back(temp);
    }

    vector<int> best_perm;
    long long best_val = -1;

    auto valid_perms = make(M, min(M, N));

    vector<pair<int, int>> p;
    for (int i = 0; i != N; ++i) {
        p.push_back({s[i], i});
    }

    sort(p.begin(), p.end());

    for (auto perm : valid_perms) {
//        for (auto x : perm) {
//            cout << x << " ";
//        }
//        cout << "\n";
        long long score = 0;
        for (int i = 0; i != M; ++i) {
            long long pscore = p[N - 1 - perm[i]].first;
            if (pscore > t[i]) {
                score += t[i] * (pscore - t[i]);
            }
        }
        if (score > best_val) {
            best_perm = perm;
            best_val = score;
        }
    }

    cout << best_val << "\n";
    for (int i = 0; i != M; ++i) {
        cout << p[N - 1 - best_perm[i]].second + 1 << " ";
    }
}

