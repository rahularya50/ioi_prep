#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long N, K;
    cin >> N >> K;
    vector<long long> a;
    for (long long i = 0; i != N; ++i)
    {
        long long temp;
        cin >> temp;
        a.push_back(temp);
    }

    map<long long, int> vals = {{a.front(), 1}};
    long long p2 = 0;
    long long out = 0;

    for (long long p1 = 0; p1 != N; ++p1)
    {
        while (abs((*vals.begin()).first - (*vals.rbegin()).first) <= K && p2 != N)
        {
            ++p2;
            ++vals[a[p2]];
        }
        out += (p2 - p1);
//        cout << p1 << " " << p2 << "\n";
        --vals[a[p1]];
        if (vals[a[p1]] == 0)
        {
            vals.erase(a[p1]);
        }
    }

    cout << out;
    return 0;
}


