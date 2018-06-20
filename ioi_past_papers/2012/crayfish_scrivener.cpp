#include <bits/stdc++.h>

using namespace std;

struct state {
    vector<int> parents;
    char val;
    int depth;
};

vector<state> tree;

int getAncestor(int i, int delta) {
//    cout << "Searching for " << delta << "th ancestor of i = " << i << "\n";
    if (delta == 0) {
//        cout << "end\n";
        return i;
    }
    int index = log2(delta);
//    cout << "index = " << index << "\n";
    return getAncestor(tree[i].parents[index], delta - (1 << index));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    tree = {{{}, 'R', 0}};
    tree.reserve(N);
    vector<int> pos = {0};
    pos.reserve(N);
}
    for (int i = 0; i != N; ++i) {
        char cmd;
        cin >> cmd;
        if (cmd == 'T') {
            char val;
            cin >> val;
            state new_state = {{pos.back()}, val, tree[pos.back()].depth + 1};
            for (int delta = 2; delta <= new_state.depth; delta *= 2) {
                new_state.parents.push_back(getAncestor(new_state.parents.back(), delta / 2));
            }
            tree.push_back(new_state);
            pos.push_back(tree.size() - 1);
//            cout << (tree.size() - 1) << ": { { ";
//            for (auto x : new_state.parents) {
//                cout << x << ", ";
//            }
//            cout << "}, " << val << ", " << new_state.depth << "}\n";
        } else if (cmd == 'P') {
            int i;
            cin >> i;
            cout << tree[getAncestor(pos.back(), tree[pos.back()].depth - i - 1)].val << "\n";
        } else {
            int num;
            cin >> num;
            pos.push_back(pos[pos.size() - num - 1]);
        }
    }
}
