#include <bits/stdc++.h>

using namespace std;

pair<int, int> go(int node, int curr_len, int max_len, vector<vector<tuple<int, int, int>>& edges)
{
    if (curr_len <= 0)
    {
        return {0, 0};
    }
    int x = 0;

}


int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<tuple<int, int, int>>> edges (n);
    for (int i = 0; i != n - 1; ++i)
    {
        int x, y, l, h;
        edges[x].push_back(make_tuple(y, l, h));
        edges[y].push_back(make_tuple(x, l, h));
    }

    cout << go()
}
