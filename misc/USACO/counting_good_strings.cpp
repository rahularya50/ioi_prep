#include <bits/stdc++.h>

using namespace std;

long long MODULUS = 1e9 + 7;

long long go(string& S, const string& T, int K, int pos, int t_next, pair<int, int> totals)
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
        if (T[t_next] == S[pos])
        {
            t_next += 1;
        }
        if (t_next == T.size())
        {
            return 0;
        }

        return go(S, T, K, pos + 1, t_next, totals);
    }
    else
    {
        S[pos] = '0';
        auto out = go(S, T, K, pos, t_next, totals);
        S[pos] = '1';
        out += go(S, T, K, pos, t_next, totals);
        S[pos] = '?';
        return out % MODULUS;
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
        M = 1;
        T = "x";
    }

    int spacing = max(M, K);
    long long out = 1;

    string built;
    int curr_space = 0;
    for (int i = 0; i != N; ++i)
    {
        built += S[i];
        if (S[i] != '?')
        {
            curr_space += 1;
        }
        else
        {
            curr_space = 0;
        }
        if (curr_space == spacing || i == (N - 1))
        {
            cout << built << "\n";
            out *= go(built, T, K, 0, 0, {0, 0});
            out %= MODULUS;
            built = "";
        }
    }

    cout << out;
}
