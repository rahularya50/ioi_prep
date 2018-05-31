#include <bits/stdc++.h>

using namespace std;

int solve(int a, int b, const vector<int>& t1, const vector<int>& t2, map<pair<int, int>, int>& cache, bool nocache) {
    if (!nocache && cache.find({a, b}) != cache.end()) {
        return cache[{a, b}];
    }

    if (a == 0) {
        return b;
    }

    if (b == 0) {
        return a;
    }

    if (t1[a - 1] != t2[b - 1]) {
        auto temp = 1 + solve(a - 1, b - 1, t1, t2, cache, true);
        if (!nocache) {
            cache[{a, b}] = temp;
        }
        return temp;
    }

    auto temp = 1 + min(solve(a - 1, b, t1, t2, cache, false), solve(a , b - 1, t1, t2, cache, false));
    if (!nocache) {
        cache[{a, b}] = temp;
    }
    return temp;
}

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> t1;
    t1.reserve(n);
    for (int i = 0; i != n; ++i) {
        int temp;
        cin >> temp;
        t1.push_back(temp);
    }

    vector<int> t2;
    t2.reserve(n);
    for (int i = 0; i != n; ++i) {
        int temp;
        cin >> temp;
        t2.push_back(temp);
    }

    map<pair<int, int>, int> cache;
    cache[{0, 0}] = 0;

    cout << solve(n, n, t1, t2, cache, false);
}
