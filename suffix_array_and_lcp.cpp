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

    int N = inp.size();

    vector<suffix> suffixes = {{N, -1, -1}};
    for (int i = 0; i != N; ++i) {
        suffixes.push_back({i, inp[i] - 'a', (i + 1 == N) ? -1 : inp[i + 1] - 'a'});
    }

    sort(suffixes.begin(), suffixes.end(), cmp);

    vector<int> new_order(N + 1);
    vector<int> lookup(N + 1);

    for (int k = 2; k <= N; k *= 2) {
        int curr = 0;
        new_order[0] = 0;
        for (int i = 1; i != suffixes.size(); ++i) {
            if (cmp(suffixes[i - 1], suffixes[i])) {
                ++curr;
            }
            new_order[i] = curr;
            lookup[suffixes[i].pos] = i;
        }

        for (int i = 0; i != suffixes.size(); ++i) {
            suffixes[i].order = new_order[i];
            suffixes[i].new_order = new_order[lookup[min(suffixes[i].pos + k, static_cast<int>(suffixes.size() - 1))]];
        }

        sort(suffixes.begin(), suffixes.end(), cmp);
    }

    for (int i = 0; i != suffixes.size(); ++i) {
        lookup[suffixes[i].pos] = i;
    }

    vector<int> lcp(suffixes.size());
    int curr = 0;

    for (int i = 0; i != N; ++i) {
        auto a = suffixes[lookup[i]];
        auto b = suffixes[lookup[i] - 1];

        while (curr < N - max(a.pos, b.pos)) {
            if (inp[a.pos + curr] == inp[b.pos + curr]) {
                ++curr;
            } else {
                break;
            }
        }

        lcp[lookup[i]] = curr;
        curr = max(0, curr - 1);
    }

    for (auto suffix : suffixes) {
        cout << suffix.pos << " " << lcp[lookup[suffix.pos]] << ": ";
        for (int i = suffix.pos; i != N; ++i) {
            cout << inp[i];
        }
        cout << "\n";
    }
}
