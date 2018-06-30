#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;

    vector<vector<bool>> levels;
    for (int i = 0; i != N; ++i)
    {
        levels.push_back({});
        for (int j = 0; j != M; ++j)
        {
            char temp;
            cin >> temp;
            levels.back().push_back(temp == 's');
        }
    }

    vector<vector<int>> dists;
    for (int i = 0; i != N; ++i)
    {
        int target = -1;
        dists.push_back({});
        for (int pos = 0; pos != M; ++pos)
        {
            if (pos > target)
            {
                while (!levels[i][++target % M]) { }
            }
            dists.back().push_back(target - pos);
        }
    }

    for (int i = 0; i != N; ++i)
    {
        int target = M;
        for (int pos = M - 1; pos >= 0; --pos)
        {
            if (pos < target)
            {
                while (!levels[i][(--target + M) % M]) { }
            }
            dists[i][pos] = min(dists[i][pos], pos - target);
        }
    }

    unsigned int best = -1;
    for (int i = 0; i != M; ++i)
    {
        int cost = 0;
        for (int j = 0; j != N; ++j)
        {
            cost += dists[j][i];
        }
//        cout << i << " " << cost << "\n";
        best = min(static_cast<unsigned int>(cost), best);
    }

    cout << best;
}
