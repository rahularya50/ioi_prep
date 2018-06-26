#include <bits/stdc++.h>

using namespace std;

struct fair {
    int t;
    int l;
    int m;
};

int main() {
    int N, U, D, S;
    cin >> N >> U >> D >> S;
    vector<fair> fairs(N);
    for (auto& x : fairs) {
        cin >> x.t >> x.l >> x.m;
    }

    fairs.push_back({0, S, 0});
    sort(fairs.begin(), fairs.end(), [](fair x, fair y) { return x.t < y.t; });

    map<int, int> lefts = {{S, 0}};
    map<int, int> rights = {{S, 0}};

    int val;
    for (int i = fairs.size() - 1; i >= 0; --i) {
        int l_best = numeric_limits<int>::min();
        auto l_iter = lefts.lower_bound(fairs[i].l);
        if (l_iter != lefts.end()) {
            l_best = l_iter->second - (l_iter->first - fairs[i].l) * U;
        }
        int r_best = numeric_limits<int>::min();
        auto r_iter = rights.upper_bound(fairs[i].l);
        if (r_iter != rights.begin()) {
            advance(r_iter, -1);
            r_best = r_iter->second - (fairs[i].l - r_iter->first) * D;
        }

        val = max(l_best, r_best) + fairs[i].m;

        l_iter = lefts.insert({fairs[i].l, val}).first;
        while (l_iter != lefts.begin()) {
            advance(l_iter, -1);
            if (l_iter->second <= val - (fairs[i].l - l_iter->first) * U) {
                l_iter = lefts.erase(l_iter);
            } else {
                break;
            }
        }

        r_iter = rights.insert({fairs[i].l, val}).first;
        advance(r_iter, 1);
        while (r_iter != rights.end()) {
            if (r_iter->second <= val - (r_iter->first - fairs[i].l) * D) {
                r_iter = rights.erase(r_iter);
            } else {
                break;
            }
        }

//        cout << "Lefts: [";
//        for (auto x : lefts) {
//            cout << x.first << ": " << x.second << ", ";
//        }
//        cout << "]\n Rights: [";
//        for (auto x : rights) {
//            cout << x.first << ": " << x.second << ", ";
//        }
//        cout << "]\n";
    }

    cout << val << "\n";
}

