#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    for (int i = 0; i != T; ++i)
    {
        int A;
        cin >> A;

        pair<int, int> origin = {1, 1};
        pair<int, int> target = {3, ((A + 8) / 9) * 3};

        for (int x = origin.second + 1; x < target.second; x += 3)
        {
            set<pair<int, int>> curr_block;

            while (curr_block.size() < 9)
            {
                cout << 2 << " " << x << endl;

                int a, b;
                cin >> a >> b;

                if (a == -1)
                {
                    return 0;
                }

                if (a == 0)
                {
                    break;
                }

                curr_block.insert({a, b});
            }
        }
    }
}
