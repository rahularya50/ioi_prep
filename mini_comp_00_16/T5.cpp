#include <bits/stdc++.h>

using namespace std;

int value(pair<int, int> trial, const vector<vector<char>>& grid, set<pair<int, int>>& possible_starts)
{
    int x = trial.first;
    int y = trial.second;
    if (grid[x][y] == '.')
    {
        return 0;
    }

    int delta = 1;
    while (grid[x + delta][y + 1] == '.')
    {
        delta += 1;
    }

    int width = delta * 2 + 1;

    delta = 1;
    while (grid[x + 1][y + delta] == '.')
    {
        delta += 1;
    }

    int height = delta * 2 + 1;

//    cout << width << " " << height << "\n";


    for (int a = x; a != (x + width); ++a)
    {
        for (int b = y; b != (y + height); ++b)
        {
//            cout << "meh: " << a << " " << b << "\n";
            if (a == x && b == y)
                continue;

            possible_starts.erase(possible_starts.find({a, b}));
        }
    }
//    cout << width << " " << height << "\n";
    return width * height;
}

int main()
{
    int N, M;
    cin >> N >> M;
    set<pair<int, int>> possible_starts;
    vector<vector<char>> grid;

    for (int i = 0; i != N; ++i)
    {
        grid.push_back({});
        for (int j = 0; j != M; ++j)
        {
            char x;
            cin >> x;
            grid.back().push_back(x);
            possible_starts.insert({i, j});
        }
    }

    int out_val = 0;
    pair<int, int> out_pos;

    while (possible_starts.size() > 0)
    {
        auto x = possible_starts.begin();
        auto val = *x;
//        cout << val.first << " " << val.second << "\n";
        possible_starts.erase(x);

        int y = value(val, grid, possible_starts);

        if (y > out_val)
        {
            out_val = y;
            out_pos = val;
        }
    }

    cout << out_val;

    return 0;

}
