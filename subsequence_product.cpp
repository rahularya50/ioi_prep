#include <bits/stdc++.h>

using namespace std;

long long solve(int pos, long long target, const vector<long long>& x, map<pair<int, long long>, long long>& cache)
{
    if (cache.find({pos, target}) != cache.end())
    {
        return cache[{pos, target}];
    }

    if (pos == x.size())
    {
        return (target == 1);
    }

    long long out = solve(pos + 1, target, x, cache);
    if (target % x[pos] == 0)
    {
        out += solve(pos + 1, target / x[pos], x, cache);
    }

    out %= (long long)(1e9 + 7);

    cache[{pos, target}] = out;
    return out;

}

int main()
{
    int N;
    long long M;
    cin >> N >> M;

    vector<long long> x;
    for (int i = 0; i != N; ++i)
    {
        long long temp;
        cin >> temp;
        x.push_back(temp);
    }

    map<pair<int, long long>, long long> cache;

    cout << solve(0, M, x, cache);

    return 0;
}
