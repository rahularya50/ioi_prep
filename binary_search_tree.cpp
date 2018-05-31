#include <bits/stdc++.h>

using namespace std;

struct node {
    int val;
    int left;
    int right;
};

int main() {
    int N;
    cin >> N;
    vector<int> a;
    a.reserve(N);
    for (int i = 0; i != N; ++i) {
        int x;
        cin >> x;
        a.push_back(x);
    }
    vector<node> tree = {{a[0], -1, -1}};
    vector<int> lookup(N, -1);
    map<int, int> valposes;
    lookup[0] = 0;
    valposes[0] = 0;
    valposes[a[0]] = 0;
    for (int i = 1; i != N; ++i) {
//        cout << "ok\n";
        auto x = valposes.lower_bound(a[i]);
        advance(x, -1);
        int prev = (*x).second;
        int curr = tree.size();
        tree.push_back({a[i], -1, -1});
        if (a[i] < tree[prev].val) {
            tree[prev].left = curr;
            valposes[(*x).first] = curr;
            valposes[a[i]] = curr;
        } else {
            tree[prev].right = curr;
            valposes[(*x).first] = curr;
            valposes[a[i]] = curr;
        }

//        for (auto y : valposes) {
//            cout << y.first << "->" << y.second << ", ";
//        }
//        cout << "\n";
        lookup[i] = curr;

//        cout << "Inserting " << a[i] << " below " << prev << "\n";
    }
    for (int i = 0; i != N; ++i) {
        cout << ((tree[lookup[i]].left == -1) ? 0 : tree[tree[lookup[i]].left].val) << " ";
        cout << ((tree[lookup[i]].right == -1) ? 0 : tree[tree[lookup[i]].right].val) << "\n";
    }
}
