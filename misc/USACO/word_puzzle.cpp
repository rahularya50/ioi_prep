#include <bits/stdc++.h>

using namespace std;

bool works(int x, int y, string target, vector< vector<char> >& grid)
{
    for (auto x_delta : {-1, 0, 1})
    {
        for (auto y_delta : {-1, 0, 1})
        {
            auto x_pos = x;
            auto y_pos = y;
            if (x_delta == 0 && y_delta == 0){
                    continue;
            }

            bool flag = true;
            for (auto a : target)
            {
                if (x_pos < 0 || x_pos >= grid.size() || y_pos < 0 || y_pos >= grid[0].size() || a != grid[x_pos][y_pos])
                {
                        flag = false;
                        break;
                }
                x_pos += x_delta;
                y_pos += y_delta;
            }
            if (flag)
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    int N;
    cin >> N;
    vector< vector<char> > grid(N, vector<char>(N));

    for (int i = 0; i != N; ++i)
    {
        for (int j = 0; j != N; ++j)
        {
            char temp;
            cin >> temp;
            grid[i][j] = temp;
        }
    }

    string target;
    cin >> target;

    vector<pair<int, int>> out;

    for (int x = 0; x != N; ++x)
    {
        for (int y = 0; y != N; ++y)
        {
            if (works(x, y, target, grid))
            {
                out.push_back({x, y});
            }
        }
    }

    cout << out.size() << "\n";
    for (auto x : out)
    {
        cout << x.first + 1 << " " << x.second + 1 << "\n";
    }
}
