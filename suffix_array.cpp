#include <bits/stdc++.h>

using namespace std;

struct suffix {
    int pos;
    int order;
    int new_order;
};

bool cmp(suffix a, suffix b) {
    if (a.order == b.order) {
        return a.new_order < b.new_order;
    }
    return a.order < b.order;
}

int main() {
    string inp;
    cin >> inp;

    vector<suffix> suffixes;
    for (int i = 0; i != inp.size(); ++i) {
        suffixes.push_back({i, inp[i] - 'a', (i + 1) == inp.size() ? -1 : inp[i + 1] - 'a'});
    }

    suffixes.push_back({inp.size(), -1, 0});

    vector<int> new_orders(suffixes.size());
    vector<int> lookup(suffixes.size());

    sort(suffixes.begin(), suffixes.end(), cmp);
    for (int k = 2; k < 2 * inp.size(); k *= 2) {
        int curr = 0;
        new_orders[0] = curr;
        for (int i = 1; i != suffixes.size(); ++i) {
            if (cmp(suffixes[i - 1], suffixes[i])) {
                ++curr;
            }
            new_orders[i] = curr;
        }

        for (int i = 0; i != suffixes.size(); ++i) {
            suffixes[i].order = new_orders[i];
            lookup[suffixes[i].pos] = i;
        }

        for (int i = 0; i != suffixes.size(); ++i) {
            suffixes[i].new_order = suffixes[lookup[min(suffixes[i].pos + k, static_cast<int>(suffixes.size() - 1))]].order;
        }

        sort(suffixes.begin(), suffixes.end(), cmp);
    }

    for (auto suffix : suffixes) {
        int pos = suffix.pos;
        cout << pos << " ";
        for (int x = pos; x != inp.size(); ++x) {
            cout << inp[x];
        }
        cout << "\n";
    }
}
