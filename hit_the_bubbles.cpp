#include <bits/stdc++.h>

using namespace std;

using frac = pair<long long, long long>;
using comb = pair<frac, frac>; // A + B * p[1]

long long gcd(long long a, long long b) {
    if (b > a) {
        return gcd(b, a);
    }
    if (b == 0) {
//        cout << "returning " << a << "\n";
        return a;
    }
    return gcd(b, a % b);
}

frac simplify(frac x) {
    auto n = x.first;
    auto d = x.second;
//    cout << "Simplifying " << n << " / " << d << "\n";
    auto g = gcd(abs(n), abs(d));
    auto s = 2 * (d > 0) - 1;
    return {n * s / g, d * s / g};
}

frac operator+(frac x, frac y) {
//    cout << x.first << " / " << x.second << " * " << y.first << " / " << y.second << "\n";
    return simplify({x.first * y.second + y.first * x.second, x.second * y.second});
}

frac operator-(frac x, frac y) {
//    cout << x.first << " / " << x.second << " * " << y.first << " / " << y.second << "\n";
    return simplify({x.first * y.second - y.first * x.second, x.second * y.second});
}

frac operator*(frac x, frac y) {
//    cout << x.first << " / " << x.second << " * " << y.first << " / " << y.second << "\n";
    return simplify({x.first * y.first, x.second * y.second});
}

frac recip(frac x) {
    return simplify({x.second, x.first});
}

int main() {
    long long Q;
    cin >> Q;
    for (long long _ = 0; _ != Q; ++_) {
        long long N, X, p, q;
        cin >> N >> X >> p >> q;
        if (p == q) {
            cout << ((X == N) ? 0 : 1) << " 1 \n";
            continue;
        }
        frac prob = simplify({p, q});
        frac prob_r = recip(frac({1, 1}) - prob);
        vector<comb> combs = {{{1, 1}, {0, 1}}, {{0, 1}, {1, 1}}};
        for (long long i = 2; i <= N; ++i) {
            auto p2 = combs[i - 1];
            auto p1 = combs[i - 2];

            auto a = p2.first;
            auto b = p2.second;

            auto c = p1.first;
            auto d = p1.second;
//
//            cout << "a = " << a.first << " / " << a.second << "\n";
////            cout << "b = " << b.first << " / " << b.second << "\n";
//            cout << "c = " << c.first << " / " << c.second << "\n";
//            cout << "d = " << d.first << " / " << d.second << "\n";

//            cout << "b - p*c = " << (a - prob * c).first << " / " << (a - prob * c).second << "\n";
            combs.push_back({(a - prob*c) * prob_r, (b - prob*d) * prob_r});
        }

        for (auto x : combs) {
//            cout << x.first.first << " / " << x.first.second << " + " << x.second.first << " / " << x.second.second << " * p[1] \n";
        }

        auto a = combs[N].first;
        auto b = combs[N].second; // a + b * x = 0
        auto x = (frac({0, 1}) - a) * recip(b);

        for (auto c : combs) {
            auto z = c.first + c.second * x;
//            cout << z.first << " " << z.second << "\n";
        }

        auto out = combs[X].first + combs[X].second * x;
        cout << out.first << " " << out.second << "\n";



    }
}
