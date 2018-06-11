#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, K;
    cin >> N >> K;
    int best = 0;
    int curr = 0;
    deque<int> T;
    for (int i = 0; i != N; ++i) {
        int x;
        cin >> x;
        T.push_back(x);
        curr += x;
        if (i >= K) {
            curr -= T.front();
            T.pop_front();
        }
        best = max(best, curr);
    }
    cout << best << "\n";
}
