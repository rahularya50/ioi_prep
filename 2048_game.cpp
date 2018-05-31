#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long T;
    cin >> T;
    for (long long i = 0; i != T; ++i)
    {
        long long N;
        cin >> N;
        vector<long long> vals;
        for (long long j = 0; j != N; ++j)
        {
            long long a;
            cin >> a;
            if (a & (a - 1))
            {
                continue;
            }
            long long x = 0;
            while (a >>= 1)
            {
                ++x;
            }
        }
                    vals.push_back(x);
        if (vals.size() != N)
        {
            cout << "Impossible\n";
            continue;
        }
        sort(vals.begin(), vals.end(), greater<long long>());
        vector<long long> counts(vals.front() + 1);
        for (auto x: vals)
        {
            counts[x] += 1;
        }
        long long two_count = counts[1];
        bool flag = true;
        for (long long delta = 1; delta < vals.front(); ++delta)
        {
            if (two_count == 0)
            {
                cout << "Impossible\n";
                flag = false;
                break;
            }
            --two_count;
            two_count += (1LL << delta) * counts[delta + 1];
//            cout << two_count << " ";
        }
        if (flag)
        {
            cout << "Possible\n";
        }
    }
}
