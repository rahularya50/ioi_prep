#include "bits/stdc++.h"

using namespace std;

vector<int> find_subset(int l, int u, vector<int> w) {
    auto N = w.size();

    vector<pair<int, int>> labelled(N);
    for (int i = 0; i != N; ++i) {
        labelled[i] = {w[i], i};
    }
    sort(w.begin(), w.end());
    sort(labelled.begin(), labelled.end());

    vector<long long> run_sum(N + 1);
    for (int i = 1; i <= N; ++i) {
        run_sum[i] = run_sum[i - 1] + w[i - 1]; // sum of [0, i)
//        cout << run_sum[i] << "\n";
    }

    for (int i = 0; i != N; ++i) {
//        cout << "i = " << i << "\n";
        auto goal = run_sum[i] + l;
        auto iter = lower_bound(run_sum.begin(), run_sum.end(), goal);
//        if (iter == run_sum.end()) {
//            cout << "no sum possible\n";
//        } else {
//            cout << "[" << i << ", " << distance(run_sum.begin(), iter) << ")\n";
//        }
        if (iter != run_sum.end() && *iter <= run_sum[i] + u) {
            int onepast = distance(run_sum.begin(), iter); // first index that's not considered
            vector<int> out;
            for (int j = i; j != onepast; ++j) {
                out.push_back(labelled[j].second);
            }
            return out;
        }
    }

    return {};
}
//
//int main() {
//    int n, l, u;
//    cin >> n >> l >> u;
//    vector<int> w(n);
//    for (auto& x : w) {
//        cin >> x;
//    }
//    auto ret = find_subset(l, u, w);
//    cout << ret.size() << "\n";
//    for (auto x : ret) {
//        cout << x << ", ";
//    }
//    cout << "\n";
//}
