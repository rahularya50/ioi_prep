#include <bits/stdc++.h>

using namespace std;

int main() {
    int T;
    cin >> T;
    for (int i = 0; i != T; ++i) {
        int M;
        cin >> M;
        vector<pair<int, int>> needed;
        for (int j = 0; j != M; ++j) {
            int x, y;
            cin >> x >> y;
            needed.push_back({x - 1, y - 1});
        }

        vector<int> A;
        for (int j = 0; j != M; ++j) {
            int temp;
            cin >> temp;
            A.push_back(temp);
        }

        vector<int> tovisit = {0};
        set<int> cyclic;
        set<int> sta;

        while (tovisit.size() > 0) {
            auto next = tovisit.back();
            tovisit.pop_back();
            if (sta.find(next) != sta.end()) {
                sta.remove(next);
                continue;
            }
            sta.insert(next);
            auto need1 = needed[next].first;
            auto need2 = needed[next].second;

            if (sta.find(need1) != sta.end() || sta.find(need2) != sta.end) {
                // cycle
                cyclic.insert(next);
                sta.remove(next);
            }

            tovisit.push_back(need1);
            tovisit.push_back(need2);
        }
    }
}
