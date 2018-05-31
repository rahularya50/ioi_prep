#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> place;

vector<place> neighbours(place x, int N, int M)
{
    auto r = x.first;
    auto c = x.second;
    vector<place> out;
    if (r > 0)
        out.push_back({r - 1, c});
    if (c < M - 1)
        out.push_back({r, c + 1});
    if (c > 0)
        out.push_back({r, c - 1});
    if (r < N - 1)
        out.push_back({r + 1, c});
    return out;
}

void min_dist(place origin, int N, int M, const vector< vector<int> >& S, map<pair<place, place>, int>& cache)
{
    set<place> explored;

    struct q_obj {
        place loc;
        int dist;
    };

    auto comparer = [](q_obj a, q_obj b){ return a.dist > b.dist; };
    typedef priority_queue<q_obj, vector<q_obj>, decltype(comparer)> pq;
    pq to_explore(comparer);

    to_explore.push({origin, 0});

    while (!to_explore.empty())
    {
        auto next = to_explore.top();
        to_explore.pop();

        if (explored.find(next.loc) != explored.end())
        {
            continue;
        }

        if (cache.find({origin, next.loc}) != cache.end() && cache[{origin, next.loc}] != next.dist)
            cout << "WHAT? " << origin.first << " " << origin.second << " " <<
                                next.loc.first << " " << next.loc.second << " " <<
                                next.dist << " " << cache[{origin, next.loc}] << " \n";
        cache[{origin, next.loc}] = next.dist;
        explored.insert(next.loc);

        for (auto n: neighbours(next.loc, N, M))
        {
            if (explored.find(n) != explored.end())
                continue;

            to_explore.push({n, next.dist + S[n.first][n.second]});
        }
    }
}

int main()
{
    int N, M, K;
    cin >> N >> M >> K;
    vector< vector<int> > S;
    for (int i = 0; i < N; ++i)
    {
        int x;
        vector<int> temp;
        for (int j = 0; j < M; ++j)
        {
            cin >> x;
            temp.push_back(x);
        }
        S.push_back(temp);
    }

    vector<place> moves;
    for (int i = 0; i <= K; ++i)
    {
        int x, y;
        cin >> x >> y;
        moves.push_back({x - 1, y - 1});
    }

    map<pair<place, place>, int> cache;
    set<place> visited;
    place pos = moves[0];

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            min_dist({i, j}, N, M, S, cache);
        }
    }

    int cost = S[pos.first][pos.second];

    for (auto p: moves)
    {
        cost += cache[{pos, p}];
        pos = p;
    }

    cout << cost;
    return 0;
}
