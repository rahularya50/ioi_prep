#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    vector<int> A_raw;
    vector<int> B_raw;

    cin >> N;

    for (int temp, i = 0; i != N; ++i)
    {
        cin >> temp;
        A_raw.push_back(temp);
    }
    for (int temp, i = 0; i != N; ++i)
    {
        cin >> temp;
        B_raw.push_back(temp);
    }

    vector<int> A_dedup;
    vector<int> B_dedup;

    int i_A = 0, i_B = 0;

    while (i_A != N)
    {
        if (i_B == N)
        {
            A_dedup.push_back(A_raw[i_A]);
            i_A += 1;
        }
        else if (A_raw[i_A] < B_raw[i_B])
        {
            cout << "Impossible";
            return 0;
        }
        else if (A_raw[i_A] > B_raw[i_B])
        {
            B_dedup.push_back(B_raw[i_B]);
            i_B += 1;
        }
        else
        {
            i_A += 1;
            i_B += 1;
        }
    }

    cout << A_dedup.size() << "\n";

    for (int i = 0; i != A_dedup.size(); ++i)
    {
//        cout << A_dedup[i] << " " << B_dedup[i] << "\n";
        cout << (A_dedup[A_dedup.size() - 1 - i] - B_dedup[i]) << "\n";
    }

    return 0;
}
