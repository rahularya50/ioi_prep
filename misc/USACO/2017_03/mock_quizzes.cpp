#include <bits/stdc++.h>

using namespace std;

const long long MODULUS = 1e9 + 7;

pair<long long, long long> lin_comb(long long a, long long b)
{
    if (a < b)
    {
        auto x = lin_comb(b, a);
        return {x.second, x.first};
    }
    if (b == 0)
    {
        return {1, 0};
    }

    auto x = lin_comb(b, a % b);
    auto y = x.first;
    auto z = x.second;

    long long k = a / b;

    return {z, ((y - k * z) % MODULUS + MODULUS) % MODULUS };
}

long long invert(long long N)
{
    auto x = lin_comb(N % MODULUS, MODULUS);
    return x.first;
}

int main()
{
    vector<long long> facts = {1};
    vector<long long> inv_facts = {1};
    long long prod = 1;
    long long inv_prod = 1;
    for (int i = 1; i < 10; ++i)
    {
        prod *= i;
        inv_prod *= invert(i);
        prod %= MODULUS;
        inv_prod %= MODULUS;
        facts.push_back(prod);
        inv_facts.push_back(inv_prod);
    }

//    vector<long long> inv_prod_sum = {0};
//    long long sum = 0;
//    for (auto x: inv_prod)
//    {
//
//    }

    int N;
    cin >> N;

    for (int i = 0; i != N; ++i)
    {
        int a, b;
        cin >> a >> b;
        cout << ((facts[a] * inv_facts[b] * inv_facts[a - b]) % MODULUS) << "\n";
    }

    return 0;
}
