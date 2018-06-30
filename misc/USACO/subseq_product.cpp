#include <bits/stdc++.h>

using namespace std;

int dynamo(vector<int>& x, int prod_target, int max_pos, map<pair<int, int>, int>& cache)
{
    cout << max_pos << "\n";
    if (cache.find({prod_target, max_pos}) != cache.end())
    {
        return cache[{prod_target, max_pos}];
    }
    if (max_pos == 0)
    {
        return (prod_target == x[max_pos]);
    }
    int cnt = dynamo(x, prod_target, max_pos - 1, cache);
    cout << "line two!" << "\n";
    if ((prod_target % x[max_pos]) == 0)
        cnt += dynamo(x, prod_target / max_pos, max_pos - 1, cache);
    cache[{prod_target, max_pos}] = cnt;
    return cnt;
}

int main()
{
    int N, M;
    cin >> N >> M;

    vector<int> x;

    int one_count = 0;

    for (int i = 0; i != N; ++i)
    {
        int temp;
        cin >> temp;
        if (temp == 1)
        {
            one_count += 1;
        }
        else
        {
            x.push_back(temp);
        }
    }

    map<pair<int, int>, int> cache;
    return dynamo(x, M, x.size() - 1, cache);
}
