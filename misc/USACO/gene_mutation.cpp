#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> X;
    for (int i = 0; i != N; ++i)
    {
        int temp;
        cin >> temp;
        X.push_back(temp);
    }

    int out = 0;

    for (int start = 0; start != N; ++start)
    {
        int low = N + 1;
        int high = 0;
        for (int delta = 0; delta != N; ++delta)
        {
            auto val = X[(start + delta) % N];
            if (val == N)
                break;
            low = min(low, val);
            high = max(high, val);

            if (high - low == delta)
            {
                out += 1;
            }
        }
    }

    cout << out;
}
