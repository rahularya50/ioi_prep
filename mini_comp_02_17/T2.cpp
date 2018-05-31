#include <bits/stdc++.h>

using namespace std;

long long tenfactors(long long N, int& p, int& q)
{
    if (N % 2 == 0)
    {
        p += 1;
        return tenfactors(N / 2, p, q);
    }
    else if (N % 5 == 0)
    {
        q += 1;
        return tenfactors(N / 5, p, q);
    }

    return N;
}

int dig_sum(long long N)
{
    if (N < 10)
        return N;

    return (N % 10) + dig_sum(N / 10);
}

long long int_pow(long long N, long long exp)
{
    if (exp == 0)
        return 1;

    return N * int_pow(N, exp - 1);
}

int main()
{
    while (true) { cout << "\n";
    long long N;
    cin >> N;

    int p = 0;
    int q = 0;
    long long k = tenfactors(N, p, q);

    long long best = k;

    for (int i = 1; i < 1e6; ++i)
    {
//        cout << i*k << " " << dig_sum(i*k) << "\n";
        if (dig_sum(best) > dig_sum(i * k))
        {
            best = i * k;
        }

        if (((k + 8) % 9 + 1) == dig_sum(i * k))
        {
            best = i * k;
            cout << "thing";
            break;
        }
    }

    best *= int_pow(10, max(p, q));
    cout << best;
}
    return 0;
}

