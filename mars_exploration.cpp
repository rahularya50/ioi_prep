#include <bits/stdc++.h>

using namespace std;

//vector<pair<int, int>> neighbours(pair<int, int> coord, int N)
//{
//    vector<pair<int, int>> borders;
//    int i = coord.first;
//    int j = coord.second;
//    if (i != 0)
//        borders.push_back({i - 1, j});
//    if (i != N - 1)
//        borders.insert({i + 1, j});
//    if (j != 0)
//        borders.insert({i, j - 1});
//    if (j != N - 1)
//        borders.insert({i, j + 1});
//    return borders;
//}

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<vector<long long>> H;
    for (int i = 0; i != N; ++i)
    {
        H.push_back({});
        for (int j = 0; j != N; ++j)
        {
            long long temp;
            cin >> temp;
            H.back().push_back(temp);
        }
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> K;
    for (int i = 0; i != Q; ++i)
    {
        int temp;
        cin >> temp;
        K.push({temp, i});
    }

    map<int, vector<pair<int, int>>> region_list;
    map<pair<int, int>, int> region_lookup;
    map<int, long long> region_sizes;

    using edge = pair<long long, pair<pair<int, int>, pair<int, int>>>;
    priority_queue<edge, vector<edge>, greater<edge>> edges;

    multiset<long long> sizes;

    for (int i = 0; i != N; ++i)
    {
        for (int j = 0; j != N; ++j)
        {
            region_list[N * i + j] = {{i, j}};
            region_lookup[{i, j}] = N * i + j;
            sizes.insert(0);
            region_sizes[N * i + j] = 0;
            if (i != N - 1)
            {
                edges.push({abs(H[i + 1][j] - H[i][j]), {{i, j}, {i + 1, j}}});
            }
            if (j != N - 1)
            {
                edges.push({abs(H[i][j + 1] - H[i][j]), {{i, j}, {i, j + 1}}});
            }
        }
    }
    vector<pair<long long, long long>> out(Q);

    while (K.size() > 0)
    {
        auto k_pair = K.top();
        K.pop();
        while (edges.size() > 0)
        {
            auto next = edges.top();
            if (next.first > k_pair.first)
            {
                break;
            }
            edges.pop();

            auto r1 = region_lookup.at(next.second.first);
            auto r2 = region_lookup.at(next.second.second);

            if (r1 == r2)
            {
                continue;
            }

            sizes.erase(sizes.find(region_sizes.at(r1)));
            sizes.erase(sizes.find(region_sizes.at(r2)));
            auto new_size = region_sizes.at(r1) + region_sizes.at(r2) + next.first;
            sizes.insert(new_size);

            // Merging using this edge!
            if (region_list.at(r1).size() > region_list.at(r2).size())
            {
                for (auto x: region_list[r2])
                {
                    region_list.at(r1).push_back(x);
                    region_lookup.at(x) = r1;
                }
                region_list.erase(r2);
                region_sizes.at(r1) = new_size;
                region_sizes.erase(r2);
            }
            else
            {
                for (auto x: region_list[r1])
                {
                    region_list.at(r2).push_back(x);
                    region_lookup.at(x) = r2;
                }
                region_list.erase(r1);
                region_sizes.erase(r1);
                region_sizes.at(r2) = new_size;
            }
        }
//        for (auto x: region_list)
//        {
//            for (auto y: x.second)
//            {
//                cout << "(" << y.first << ", " << y.second << "), ";
//            }
//            cout << "\n";
//        }
//        cout << "\n";
        out[k_pair.second] = {region_list.size(), *sizes.rbegin()};
    }

    for (auto x: out)
    {
        cout << x.first << " " << x.second << "\n";
    }

    return 0;
}
