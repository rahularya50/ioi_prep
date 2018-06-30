#include <bits/stdc++.h>

using namespace std;

long long go(string S, string T, int K, map<pair<int, int>, long long>& cache, int s_pos, int t_pos, bool kval, int k_len)
{
    if (cache.find({s_pos, t_pos, k_val, k_len}) != cache.end())
    {
        return cache[{s_pos, t_pos, k_val, k_len}];
    }

    if (t_pos == T.size())
    {
        return 0;
    }

    if (s_pos == S.size())
    {
        return 1;
    }

    int new_t_pos = (S[s_pos] == T[t_pos]) ? t_pos + 1 : t_pos

    long long out = 0;
    out += go(S, T, K, cache, s_pos - 1, new_t_pos, 0, 0);



    if (S[s_pos] = T[t_pos])
    {
        go(S, T, K, cache, s_pos - 1, t_pos - 1, kval, k_len - 1)
    }
}

int main()
{
    int N, M, K;
    cin >> N >> M >> K;

    map<pair<int, int>, long long> cache;
    go(S, T, K, cache)
}
