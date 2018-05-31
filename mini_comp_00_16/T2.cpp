#include <bits/stdc++.h>

using namespace std;

int target_color(int i)
{
    auto x = max(abs((i % 5) - 2), abs((i / 5) - 2));
    return 3 - x;
}

int main()
{
    vector<int> rows;
    int target;
    for (int i = 0; i != 25; ++i)
    {
        int temp;
        cin >> temp;
        rows.push_back(temp);
        if (temp == 3)
            target = i;
    }

    int out = 0;

    if (rows[5 * 2 + 2] != 3)
    {
        out += 2;
        rows[target] = rows[5 * 2 + 2];
        rows[5 * 2 + 2] = 3;
    }

    for (int i = 0; i != 25; ++i)
    {
        if (rows[i] != target_color(i))
        {
            out += 1;
        }
    }

    cout << (out / 2);

    return 0;
}
