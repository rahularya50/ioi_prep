#include <bits/stdc++.h>
using namespace std;
int main() {
    int N, M, K;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M >> K;
    vector<int> t;
    vector<int> x;
    t.reserve(N);
    x.reserve(N);
    map<int, int> thresholds;
    for (int i = 0; i != M; ++i) {
        int a, b;
        cin >> a >> b;
        t.push_back(a);
        x.push_back(b);
        ++thresholds[a + b];
    }
    int floor = K + 1, prev_time = 0;
    long long cost = 0;
    int lim = (*thresholds.begin()).first;
    for (int i = 0; i != M; ++i)
    {
        floor = min(floor + (t[i] - prev_time), lim - t[i]);
        cost += static_cast<long long>(x[i] - floor);
        --thresholds[t[i] + x[i]];
        if (thresholds[t[i] + x[i]] == 0){
            thresholds.erase(t[i] + x[i]);
            lim = (*thresholds.begin()).first;
        }
        prev_time = t[i];
    }
    cout << cost;
}
