#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, M, Q;
    cin >> N >> M >> Q;

    vector<vector<int>> F;
    map<int, set<int>> who_wants;

    for (int i = 0; i != N; ++i)
    {
        int d_i;
        cin >> d_i;
        vector<int> temp;
        for (int j = 0; j != d_i; ++j)
        {
            int temp2;
            cin >> temp2;
            temp.push_back(temp2);
            who_wants[temp2].insert(i); // i is between 0 and N - 1 (inclusive)
        }
        F.push_back(temp);
    }

    for (int i = 0; i != Q; ++i)
    {
        int L, R, X;
        cin >> L >> R >> X;

        if (L <= R)
        {
            cout <<
                 ((
                      who_wants[X].lower_bound(L - 1) == who_wants[X].end()
                      || *who_wants[X].lower_bound(L - 1) > (R - 1)
                  ) ? "No" : "Yes");
        }
        else
        {
            cout <<
                 ((
                      who_wants[X].lower_bound(L - 1) == who_wants[X].end()
                      && (who_wants[X].lower_bound(0) == who_wants[X].end()
                          || *who_wants[X].lower_bound(0) > (R - 1))
                  ) ? "No" : "Yes");
        }

        cout << "\n";
    }


    return 0;
}
