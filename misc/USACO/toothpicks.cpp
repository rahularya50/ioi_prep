#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;

    vector<pair<pair<int, int>, bool>> points_x_y;
    vector<pair<pair<int, int>, bool>> points_y_x;

    long long out = 0;

    for (int i = 0; i != N; ++i)
    {
        long long a, b, c, d;
        cin >> a >> b >> c >> d;

        points_x_y.push_back({{a, b}, true});
        points_x_y.push_back({{a, d}, false});
        points_x_y.push_back({{c, b}, true});
        points_x_y.push_back({{c, d}, false});

        points_y_x.push_back({{b, a}, true});
        points_y_x.push_back({{d, a}, true});
        points_y_x.push_back({{b, c}, false});
        points_y_x.push_back({{d, c}, false});

        out += (d - b) * (c - a - 1) + (c - a) * (d - b - 1);

    }

    sort(points_x_y.begin(), points_x_y.end());
    sort(points_y_x.begin(), points_y_x.end());

    int state = 0;
    int x_pos = -486766;
    int y_pos = -456543;

    for (auto p: points_x_y)
    {
//        cout << p.first.first << " " << p.first.second << " " << (p.second ? "True" : "False") << "\n";
        if (p.first.first != x_pos)
        {
            state = 0;
            x_pos = p.first.first;
        }

        if (state != 0)
        {
            out += (p.first.second - y_pos);
//            cout << (p.first.second - y_pos) << "\n";
        }
        y_pos = p.first.second;
        state += (2*p.second-1);
    }

    state = 0;
    x_pos = -546557;
    y_pos = -654654;

    for (auto p: points_y_x)
    {
//        cout << p.first.second << " " << p.first.first << " " << (p.second ? "True" : "False") << "\n";
        if (p.first.first != y_pos)
        {
            state = 0;
            y_pos = p.first.first;
        }

        if (state != 0)
        {
            out += (p.first.second - x_pos);
//            cout << (p.first.second - x_pos) << "\n";
        }

        x_pos = p.first.second;
        state += (2*p.second-1);
    }

    cout << out;

    return 0;
}
