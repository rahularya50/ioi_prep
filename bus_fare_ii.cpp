#include <bits/stdc++.h>

using namespace std;

double maximize(const vector<long long>& stops, const vector<int>& a, const vector<int>& b, deque<pair<int, int>>& onboard, int pos, bool maximizing)
{
    if (pos == a.size())
        return 0;

    double out = 0;
    int off = 0;

    while(b[pos] > 0)
    {
        if (off + onboard.front().second < b[pos])
        {
            out += onboard.front().second * pow(stops[pos] - stops[onboard.front().first], 0.5);
            off += onboard.front().second;
            onboard.pop_front();
        }
        else
        {
            int remaining = onboard.front().second - (b[pos] - off);
            int prev_pos = onboard.front().first;

            out += (b[pos] - off) * pow(stops[pos] - stops[onboard.front().first], 0.5);

            onboard.pop_front();
            onboard.push_front({prev_pos, remaining});

            break;
        }
    }

    if (a[pos] > 0)
    {
        if (maximizing)
        {
            onboard.push_back({pos, a[pos]});
        }
        else
        {
            onboard.push_front({pos, a[pos]});
        }
    }

    return out + maximize(stops, a, b, onboard, pos + 1, maximizing);
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;

    vector<int> d;
    for (int i = 0; i != N - 1; ++i)
    {
        int temp;
        cin >> temp;
        d.push_back(temp);
    }

    vector<int> a;
    for (int i = 0; i != N; ++i)
    {
        int temp;
        cin >> temp;
        a.push_back(temp);
    }

    vector<int> b;
    for (int i = 0; i != N; ++i)
    {
        int temp;
        cin >> temp;
        b.push_back(temp);
    }

    long long pos = 0;
    vector<long long> stops = {0};
    for (auto x: d)
    {
        pos += x;
        stops.push_back(pos);
    }

    cout.precision(17);

    deque<pair<int, int>> onboard;
    cout << maximize(stops, a, b, onboard, 0, false) << " ";
    onboard = {};
    cout << maximize(stops, a, b, onboard, 0, true);

    return 0;
}

