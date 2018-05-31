#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long N, M, Dir;
    cin >> N >> M >> Dir;
    vector<pair<long long, long long>> vals_1;
    vals_1.reserve(M);
    long long sum = 0;
    for (long long i = 0; i != M; ++i)
    {
        long long X, Y, S;
        cin >> X >> Y >> S;
        if (Dir)
        {
            vals_1.push_back({X - Y, S});
        }
        else
        {
            vals_1.push_back({X, S});
        }
        sum += S;
    }

    sort(vals_1.begin(), vals_1.end());
    vector<pair<long long, long long>> vals;
    vals.reserve(N);
    for (auto x: vals_1)
    {
        if (vals.size() == 0 || vals.back().first != x.first)
        {
            vals.push_back(x);
        }
        else
        {
            vals.back().second += x.second;
        }
    }


    long long total = 0;
    long long prev = -1;
    for (auto x: vals)
    {
        total += x.second;
        if (total*2 == sum + x.second)
        {
            cout << x.first;
            return 0;
        }
        else if (total*2 > sum + x.second)
        {
            if (prev != x.first - 1 && (total*2 == sum + 2*x.second))
            {
                cout << (x.first - 1);
                return 0;
            }
            else
            {
                cout << "OH NO";
                return 0;
            }
        }
        prev = x.first;
    }
    cout << "OH NO";
    return 0;
}
