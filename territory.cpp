#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    map<int, int> c;
    for (int i = 0; i != k; ++i)
    {
        int temp;
        cin >> temp;
        c[temp - 1] = i;
    }
    vector<vector<pair<int, int>>> edges(n);
    for (int i = 0; i != m; ++i)
    {
        int x, y, l;
        cin >> x >> y >> l;
        edges[x - 1].push_back({l, y - 1});
        edges[y - 1].push_back({l, x - 1});
    }

    vector<pair<int, int>> dists(n, {-2, numeric_limits<int>::max()});
    using edge = pair<int, pair<int, int>>; // <final weight, <origin, dest>>
    priority_queue<edge, vector<edge>, greater<edge>> to_explore;
    for (auto x: c)
    {
        to_explore.push({0, {x.first, x.first}});
    }
    while (to_explore.size() > 0)
    {
        auto next_edge = to_explore.top();
        to_explore.pop();

        auto final_weight = next_edge.first;
        auto origin = next_edge.second.first;
        auto dest = next_edge.second.second;

        if (dists[dest].second < final_weight || dists[dest].first == -1 || dists[dest].first == origin)
        {
            continue;
        }
        if (dists[dest].first == -2)
        {
            dists[dest] = {origin, final_weight};
            for (auto x: edges[dest])
            {
                to_explore.push({final_weight + x.first, {origin, x.second}});
            }
        }
        else
        {
            dists[dest] = {-1, final_weight};
            for (auto x: edges[dest])
            {
                to_explore.push({final_weight + x.first, {-1, x.second}});
            }
        }
    }
    for (auto x: dists)
    {
        cout << ((x.first == -1 || x.first == -2) ? 0 : c[x.first] + 1) << " ";
    }
}
