#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;

    vector<vector<pair<int, int>>> graph(N);

    for (int i = 0; i != M; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u - 1].push_back({w, v - 1});
        graph[v - 1].push_back({w, u - 1});
    }

    int weight = 0;
    unordered_set<int> tree;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> edges;
    edges.push({0, 0});

    while (tree.size() != N)
    {
        auto next_edge = edges.top();
        edges.pop();
        if (tree.find(next_edge.second) != tree.end())
        {
            continue;
        }

        tree.insert(next_edge.second);
        weight += next_edge.first;

        for (auto x: graph[next_edge.second])
        {
            if (tree.find(x.second) == tree.end()) // TODO: delete and see speed delta
            {
                edges.push(x);
            }
        }
    }

    cout << weight;
    return 0;
}
