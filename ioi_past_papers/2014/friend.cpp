#include <bits/stdc++.h>

using namespace std;

struct operation {
    int host;
    int protocol;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<int> confidence(N);
    for (int i = 0; i != N; ++i) {
        int x;
        cin >> x;
        confidence[i] = x;
    }
    vector<operation> ops(N - 1);
    for (int i = 0; i != N - 1; ++i) {
        int h, p;
        cin >> h >> p;
        ops[i] = {h, p};
    }

    int delta = 0;
    while (ops.size() > 0) {
        int curr = ops.size();
        auto op = ops.back();
        ops.pop_back();
        if (op.protocol == 0) {
            delta += confidence[curr];
            confidence[op.host] -= confidence[curr];
            confidence[op.host] = max(confidence[op.host], 0);
        } else if (op.protocol == 1) {
            confidence[op.host] += confidence[curr];
        } else {
            confidence[op.host] = max(confidence[op.host], confidence[curr]);
        }
    }
    cout << confidence[0] + delta;
}
