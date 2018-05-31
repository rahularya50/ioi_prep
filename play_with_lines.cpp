#include <bits/stdc++.h>
#include <cstdlib>

using namespace std;

int main() {
    long long n, p;
    cin >> n >> p;
    vector<pair<long long, long long>> points;
    points.reserve(n);
    std::random_device rd;     //Get a random seed from the OS entropy device, or whatever
    std::mt19937_64 eng(rd()); //Use the 64-bit Mersenne Twister 19937 generator
    std::uniform_int_distribution<long long> distr(0, n-1);

    for (int i = 0; i != n; ++i) {
        long long x, y;
        cin >> x >> y;
        points.push_back({x, y});
    }

    if (n == 1) {
        cout << "possible\n";
        return 0;
    }

    for (int i = 0; i != 3000; ++i) {
        auto p1 = points[distr(eng)];
        auto p2 = points[distr(eng)];
        auto dx = p1.first - p2.first;
        auto dy = p1.second - p2.second;
        if (!dx && !dy) {
            continue;
        }
        long long c = 0;
        for (auto p : points) {
            auto x = p.first;
            auto y = p.second;
            if ((y - p1.second) * dx == (x - p1.first) * dy) {
                ++c;
            }
        }
        if (c * 100LL >= n * p) {
//            cout << p1.first << " " << p1.second << " " << p2.first << " " << p2.second << "\n";
            cout << "possible\n";
            return 0;
        }
    }

    cout << "impossible\n";
    return 0;
}
