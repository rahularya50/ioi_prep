#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> x;
    for (int i = 0; i != N; ++i)
    {
        int temp;
        cin >> temp;
        x.push_back(temp);
    }
    int y = 0;
    int curr = N;
    for (int i = N; i >= 0; --i)
    {
        if (x[i] == curr)
        {
            --curr;
            ++y;
        }
    }
    cout << (N - y);
}
