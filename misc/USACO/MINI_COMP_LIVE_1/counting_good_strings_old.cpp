
#include <bits/stdc++.h>

using namespace std;

int go(string& S, const string& T, int K, int pos, set<int> t_nexts, pair<int, int> totals)
{
//    cout << S << " " << totals.first << " " << totals.second << "\n";
    if (pos == S.size())
    {
//        cout << "yay" << "\n";
        return 1;
    }
    if (S[pos] != '?')
    {
        if (S[pos] == '0')
        {
            totals.second = 0;
            totals.first += 1;
            if (totals.first == K)
            {
                return 0;
            }
        }
        else
        {
            totals.first = 0;
            totals.second += 1;
            if (totals.second == K)
            {
                return 0;
            }
        }
        set<int> new_t_nexts;
        for (auto x: t_nexts)
        {
            if (T[x] == S[pos])
            {
                x += 1;
            }
            new_t_nexts.insert(x);
            if (x == T.size())
            {
                return 0;
            }
        }

        if (S[pos] == T[0])
        {
            new_t_nexts.insert(0);
        }

        return go(S, T, K, pos + 1, new_t_nexts, totals);
    }
    else
    {
        S[pos] = '0';
        int out = go(S, T, K, pos, t_nexts, totals);
        S[pos] = '1';
        out += go(S, T, K, pos, t_nexts, totals);
        S[pos] = '?';
        return out;
    }
}

int main()
{
    int N, M, K;
    cin >> N >> M >> K;
    string S, T;
    cin >> S;
    cin >> T;
    if (M > N)
    {
        T = "x";
    }
    cout << go(S, T, K, 0, {0}, {0, 0});
}
