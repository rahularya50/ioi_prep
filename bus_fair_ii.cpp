#include <bits/stdc++.h>

using namespace std;

int dig_sum(long long n)
{
    if (n < 10)
        return n;

    return (n % 10) + dig_sum(n / 10);
}

int main()
{
    long long N;
    cin >> N;

    int out = dig_sum(N);
    long long out2;
    auto counter = N;

    for (int i = 0; i != N*100; ++i)
    {
        if (out > dig_sum(counter))
        {
            out = dig_sum(counter);
            out2 = counter;
        }
        counter += N;
    }

    cout << out2;
    return 0;
}
