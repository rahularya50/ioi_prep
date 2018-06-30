#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, Q;
    cin >> N >> Q;
    unordered_multimap<int, vector<pair<int, int>>> raw_tree;
    for (int i = 0; i != N - 1; ++i)
    {
        int x, y, z;
        cin x >> y >> z;
        raw_tree[x].push_back({y, z});
        raw_tree[y].push_back({x, z});
    }

    unordered_map<int, vector<pair<int, int>, pair<int, int>>>
}
