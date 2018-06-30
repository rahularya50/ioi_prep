#include <bits/stdc++.h>

using namespace std;

struct state
{
    int room_ind;
    int room_pos; // -1 means room is locked
    int time_remaining;
};

bool operator <(const state& x, const state& y) {
    return std::tie(x.room_ind, x.room_pos, x.time_remaining) < std::tie(y.room_ind, y.room_pos, y.time_remaining);
}

int main()
{
    int N, T;
    cin >> N >> T;

    vector<pair<int, vector<int>>> bombs;
    for (int i = 0; i != N; ++i)
    {
        int L, M;
        cin >> L >> M;
        vector<int> temp;
        for (int j = 0; j != M; ++j)
        {
            int x;
            cin >> x;
            temp.push_back(x);
        }
        sort(temp.begin(), temp.end());
        bombs.push_back({L, temp});
    }

    map<state, int> cache;
    deque<state> todo = {{0, -1, T}};

    while (todo.size() > 0)
    {
        auto next = *todo.begin();
        todo.pop_front();

        if (cache.find(next) != cache.end())
            continue;

        if (next.room_ind == N)
        {
            cache[next] = 0;
            continue;
        }

        auto disarm_time = (next.room_pos == -1) ? bombs[next.room_ind].first : bombs[next.room_ind].second[next.room_pos];
        if (disarm_time > next.time_remaining || next.room_pos == bombs[next.room_ind].second.size())
        {
            state next_state = {next.room_ind + 1, -1, next.time_remaining};
            if (cache.find(next_state) == cache.end())
            {
                todo.push_front(next);
                todo.push_front(next_state);
            }
            else
            {
                cache[next] = cache[next_state];
//                cout << next.room_ind << " " << next.room_pos << " " << next.time_remaining << " " << cache[next] << "\n";
            }
        }
        else
        {
            state next_state_1 = {next.room_ind + 1, -1, next.time_remaining};
            state next_state_2 = {next.room_ind, next.room_pos + 1, next.time_remaining - disarm_time};

            if (cache.find(next_state_1) == cache.end() || cache.find(next_state_2) == cache.end())
            {
                todo.push_front(next);
                todo.push_front(next_state_1);
                todo.push_front(next_state_2);
            }
            else
            {
                cache[next] = max(cache[next_state_1], cache[next_state_2] + ((next.room_pos == -1) ? 0 : 1));
//                cout << next.room_ind << " " << next.room_pos << " " << next.time_remaining << " " << cache[next] << "\n";
            }
        }
    }

    cout << cache[{0, -1, T}];

    return 0;
}
