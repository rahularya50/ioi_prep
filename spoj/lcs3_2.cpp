#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A;
    A.reserve(N);
    for (int i = 0; i != N; ++i) {
        int x;
        cin >> x;
        A.push_back(x);
    }

    int Q;
    cin >> Q;
    vector<pair<vector<int>, int>> possibles;
    vector<vector<pair<int, int>>> lookups(10002);
    vector<vector<int>> bests(Q);

    for (int q = 0; q != Q; ++q) {
        int M;
        cin >> M;
        vector<int> query;
        for (int i = 0; i != M; ++i) {
            int x;
            cin >> x;
            query.push_back(x);
        }
        for (int i = 1; i != (1 << M); ++i) {
            vector<int> temp;
            for (int j = 0; j != M; ++j) {
                if (i & (1 << j)) {
                    temp.push_back(query[j]);
                }
            }
            lookups[temp[0]].push_back({possibles.size(), 0});
            possibles.push_back({move(temp), q});
        }
    }

    for (auto x : A) {
        vector<pair<int, int>> rep;
        for (auto y : lookups[x]) {
            pair<int, int> a = {y.first, y.second + 1};
            if (a.second == possibles[a.first].first.size()) {
                if (bests[possibles[a.first].second].size() < a.second || (bests[possibles[a.first].second].size() == a.second && possibles[a.first].first < bests[possibles[a.first].second])) {
                    bests[possibles[a.first].second] = move(possibles[a.first].first);
                }
            }
            else {
                if (possibles[a.first].first[a.second] == x) {
                    rep.push_back(a);
                } else {
                    lookups[possibles[a.first].first[a.second]].push_back(a);
                }
            }
        }
        lookups[x] = move(rep);
    }

    for (int i = 0; i != Q; ++i) {
        cout << bests[i].size() << " ";
        for (auto x : bests[i]) {
            cout << x << " ";
        }
        cout << "\n";
    }
}
