#include <bits/stdc++.h>

using namespace std;

// DR JONES

int main()
{
    int N, Q;
    cin >> N >> Q;

    vector<vector<int>> graph;
    set<pair<int, int>> unexplored;

    for (int i = 0; i != N; ++i)
    {
        vector<int> temp;
        for (int j = 0; j != N; ++j)
        {
            int x;
            cin >> x;
            temp.push_back(x);
            unexplored.push_back({i, j});
        }
    }

}
