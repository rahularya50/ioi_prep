#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, M, K;
    cin >> N >> M >> K;
    vector<int> t;
    vector<int> x;

    map<int, int> thresholds;

    for (int i = 0; i != M; ++i)
    {
        int a, b;
        cin >> a >> b;
        t.push_back(a);
        x.push_back(b);
        ++thresholds[a + b];
    }

    int time = 0;
    int floor = K + 1;
    int cost = 0;

    for (int time = 0; time <= t.back(); ++time)
    {
        if (time == t[i])
        {
            cost += (x[i] - floor);
            --thresholds[time + x[i]];
            if (thresholds[time + x[i]] == 0)
            {
                thresholds.erase(time + x[i]);
            }
            ++i;
        }

        if (floor + time == (*thresholds.begin()).first)
        {
            floor -= 1;
        }
        else if (floor + time == (*thresholds.begin()).first - 1)
        {
            // pass
        }
        else
        {
            floor += 1;
        }
    }

    cout << cost;
}
