#include <bits/stdc++.h>

using namespace std;

long long gcd(long long a, long long b) {
    if (b > a) {
        return gcd(b, a);
    }
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

long long phi(long long n, long long start) {
    for (; start * start <= n; ++start) {
        if (n % start == 0) {
            long long div = 1;
            while (n % start == 0) {
                n /= start;
                div *= start;
            }
            return (div - (div / start)) * phi(n, start + 1);
        }
    }
    return max(1LL, n - 1);
}

long long powmod(long long a, long long b, long long m) {
    long long out = 1;
    long long curr = a;
    for (long long i = 1, j = 0; i <= b; i *= 2, j += 1) {
        if ((1 << j) & b) {
            out = (out * curr) % m;
        }
        curr = (curr * curr) % m;
    }
    return out;
}

long long powmod2(long long a, long long b, long long m) {
    a %= m;
    long long g = gcd(a, m);
    if (g == 1) {
        return powmod(a, b, m);
    }
    if (b == 1) {
        return a;
    }
    return (powmod(a / g, b, m) * powmod2(g, b - 1, m / g) * g) % m;
}

int main() {
    long long n, m;
    cin >> n >> m;
    vector<long long> a;
    a.reserve(n);
    for (long long i = 0; i != n; ++i) {
        long long x;
        cin >> x;
        a.push_back(x ? x : -1);
    }
    vector<long long> phis = {m};
    phis.reserve(n);
//    cout << "phis = [";
//    cout << phis.back() << ", ";
    while (phis.size() != n) {
        phis.push_back(phi(phis.back(), 2));
//        cout << phis.back() << ", ";
    }
//    cout << "]\n";

//    cout << "a-ok\n";

    vector<long long> phipows(n, -1);
    phipows[n - 1] = a[n - 1] ? a[n - 1] : -1;
    for (long long i = n - 2; i >= 0; --i) {
        long long base = a[i];
        long long exp = phipows[i + 1];
        long long mod = phis[i];
        if (exp == -1) {
            phipows[i] = 1;
            continue;
        }
        if (base == -1) {
            phipows[i] = -1;
            continue;
        }

        if (exp == 0) {
            exp = phis[i + 1];
        }

        phipows[i] = powmod2(base, exp, mod);
    }
    cout << ((phipows[0] == -1) ? 0 : phipows[0]);
}
