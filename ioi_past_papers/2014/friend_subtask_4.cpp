#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> children;
vector<int> confidence;
vector<int> dp;

int go(int i) {
    if (dp[i] != -1) {
        return dp[i];
    }
    int a = 0;
    a += confidence[i];
    for (auto x : children[i]) {
        for (auto y : children[x]) {
            a += go(y);
        }
    }

    int b = 0;
    for (auto x : children[i]) {
        b += go(x);
    }

    dp[i] = max(a, b);
    return dp[i];
}

int main() {
    int N;
    cin >> N;
    confidence = vector<int>(N);
    dp = vector<int>(N, -1);
    for (int i = 0; i != N; ++i) {
        int x;
        cin >> x;
        confidence[i] = x;
    }
    children = vector<vector<int>>(N);
    vector<int> parent(N);
    for (int i = 0; i != N - 1; ++i) {
        int host, protocol;
        int next = i + 1;
        cin >> host >> protocol;
        if (protocol != 1) {
            children[host].push_back(next);
            parent[next] = host;
        }
    }

    cout << go(0);
}
