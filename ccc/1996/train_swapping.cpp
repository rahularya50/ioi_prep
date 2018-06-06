#include <bits/stdc++.h>

using namespace std;

int solve(vector<int>& vals) {
    if (vals.size() <= 1) {
        return 0;
    }
    vector<int> a;
    vector<int> b;
    for (int i = 0; i != vals.size() / 2; ++i) {
        a.push_back(vals[i]);
    }
    for (int i = vals.size() / 2; i != vals.size(); ++i) {
        b.push_back(vals[i]);
    }
    int out = solve(a) + solve(b);
    int p1 = 0;
    int p2 = 0;
    while (p1 != a.size() || p2 != b.size()) {
        if (p1 == a.size() || p2 != b.size() && a[p1] > b[p2]) {
            out += (a.size() - p1);
            vals[p1 + p2] = b[p2];
            ++p2;
        } else {
            vals[p1 + p2] = a[p1];
            ++p1;
        }
    }
    return out;
}

int main() {
    int N;
    cin >> N;

    for (int i = 0; i != N; ++i) {
        int L;
        cin >> L;
        vector<int> vals;
        for (int j = 0; j != L; ++j) {
            int x;
            cin >> x;
            vals.push_back(x);
        }
        cout << "Optimal train swapping takes " << solve(vals) << " swap(s).\n";
    }
}
