#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;


    vector<vector<pair<int, int>>> graph(N);

    for (int i = 0; i != N - 1; ++i) {
        int a, b, l;
        cin >> a >> b >> l;
        graph[a - 1].push_back({l, b - 1});
        graph[b - 1].push_back({l, a - 1});
    }

    vector<int> preds(N);

    for (int i = 0; i != Q; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        vector<pair<int, int>> do_next = {{u, -1}};
        while (do_next.size() > 0) {
            auto x = do_next.back();
            do_next.pop_back();
            for (auto y : graph[x.first]) {
                if (y.second == x.second) {
                    continue;
                }
                do_next.push_back({y.second, x.first});
            }
            preds[x.first] = x.second;
//            cout << "preds[" << x.first << "] = " << x.second << "\n";
            if (x.first == v) {
                break;
            }
        }

        vector<bool> cycle(N);
        vector<int> sp(N, -1);
        int curr = v;
        vector<pair<int, int>> to_explore;
        int worst = 0;
        while (curr != -1) {
            cycle[curr] = true;
            to_explore.push_back({0, curr});
            curr = preds[curr];
        }

        while (to_explore.size() > 0) {
            auto n = to_explore.back();
            to_explore.pop_back();
            if (sp[n.second] != -1) {
                continue;
            }
            sp[n.second] = n.first;
            worst = max(worst, n.first);
            for (auto edge : graph[n.second]) {
                if (cycle[edge.second] || sp[edge.second] != -1) {
                    continue;
                }
                to_explore.push_back({n.first + edge.first, edge.second});
            }
        }


        cout << worst << "\n";
    }
}
