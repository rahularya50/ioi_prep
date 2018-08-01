#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> parent(N);
    vector<int> children(N);
    for (auto& x : parent) {
        cin >> x;
        --x;
        if (x != -1) {
            ++children[x];
        }
    }
    vector<long long> s(N);
    for (auto& x : s) {
        cin >> x;
    }

    vector<int> leaves;
    for (int i = 0; i != N; ++i) {
        if (children[i] == 0) {
            leaves.push_back(i);
        }
    }

    long long out = 0;
    while (leaves.size() > 0) {
        auto leaf = leaves.back();
        if (parent[leaf] == -1) {
            out += s[leaf];
            leaves.pop_back();
        } else {
            auto n = min(s[leaf], s[parent[leaf]]);
            s[leaf] -= n;
            s[parent[leaf]] -= n;
            out += n;
            leaves.pop_back();
            if (s[leaf] != 0) {
                out += s[leaf];
                s[leaf] = 0;
            }
            --children[parent[leaf]];
            if (children[parent[leaf]] == 0) {
                leaves.push_back(parent[leaf]);
            }
        }
    }

    cout << out;
}
