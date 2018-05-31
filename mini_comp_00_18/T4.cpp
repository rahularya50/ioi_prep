#include <bits/stdc++.h>

using namespace std;

typedef pair<long long, long long> frac;


long long gcd(long long a, long long b)
{
//    cout << "gcding " << a << " " << b << "\n";
    if (b > a)
        return gcd(b, a);

    if (b == 0)
        return a;

    return gcd(b, a % b);
}



frac simplify(long long num, long long denom)
{
//    cout << "Simplifying " << num << " / " << denom << "\n";
//    int X;
//    cin >> X;
    if (num == 0)
        return {0, 1};
    long long x = gcd(abs(num), abs(denom));
    return {num / x, denom / x};
}


frac convert(frac x, frac y, long long p, long long q)
{
    long long a = x.first;
    long long b = x.second;
    long long c = y.first;
    long long d = y.second;

//    cout << "a: " << a << " b: " << b << " c: " << c << " d: " << d << " p: " << p << " q: " << q << "\n";

    return simplify(a*q*d - b*c*p, b*q*d - b*p*d);
}


int main()
{
    int Q;
    cin >> Q;
    for (int i = 0; i != Q; ++i)
    {
        int N, X, p, q;
        cin >> N >> X >> p >> q;

        if (p == 1 && q == 1)
        {
            cout << (X == N ? 0 : 1) << " 1\n";
            continue;
        }

        vector<pair<frac, frac>> subs = { {{0, 1}, {1, 1}},
                                          {{1, 1}, {0, 1}}};
        for (int j = 2; j <= N; ++j)
        {
            subs.push_back({
                           convert(subs[j - 1].first, subs[j - 2].first, p, q),
                           convert(subs[j - 1].second, subs[j - 2].second, p, q),
                           });
        }


        auto a = subs[N].first.first;
        auto b = subs[N].first.second;
        auto c = subs[N].second.first;

        auto d = subs[N].second.second;
        auto k = simplify(-b * c, a * d);

        auto coeffs = subs[X];
        auto kc = coeffs.first;
        auto ic = coeffs.second;

        auto f1 = simplify(kc.first * k.first, kc.second * k.second);
        auto out = simplify(f1.first * ic.second + f1.second * ic.first, f1.second * ic.second);

//        auto out = simplify(kc.first * k.first * ic.second + ic.first * kc.second * k.second, ic.second * kc.second * k.second);

        cout << out.first << " " << out.second << "\n";
    }

    return 0;
}
