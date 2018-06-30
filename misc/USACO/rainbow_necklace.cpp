#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;

    if (M > N)
    {
        M = N;
    }

    vector<int> c;
    for (int i = 0; i != N; ++i)
    {
        int temp;
        cin >> temp;
        c.push_back(temp);
    }

    map<int, int> contains;
    for (int i = 0; i != M; ++i)
    {
        ++contains[c[i]];
    }
    int best = contains.size();
    for (int i = M; i != N; ++i)
    {
        ++contains[c[i]];
        --contains[c[i - M]];
        if (contains[c[i - M]] == 0)
        {
            contains.erase(c[i - M]);
        }
        if (contains.size() > best)
        {
            best = contains.size();
        }
    }

    cout << best;
}
