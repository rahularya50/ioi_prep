#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i != T; ++i)
    {
        int N;
        cin >> N;
        vector<int> evens;
        vector<int> odds;
        for (int j = 0; j != N; ++j)
        {
            int x;
            cin >> x;
            if (j % 2)
            {
                odds.push_back(x);
            }
            else
            {
                evens.push_back(x);
            }
        }

        sort(evens.begin(), evens.end());
        sort(odds.begin(), odds.end());

        bool done = false;
        cout << "Case #" << i + 1 << ": ";

        vector<int> f;
        auto prev = evens[0];
        for (int j = 0; j != N; ++j)
        {
            int curr;
            if (j % 2)
            {
                curr = odds[j / 2];
            }
            else
            {
                curr = evens[j / 2];
            }
            if (curr < prev)
            {
                cout << j - 1 << "\n";
                done = true;
                break;
            }
            prev = curr;
        }

        if (!done)
        {
            cout << "OK" << "\n";
        }
    }
}
