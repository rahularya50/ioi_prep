#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;

    if (N == 0)
    {
        cout << "1\n0";
        return 0;
    }
    if (N == 1)
    {
        cout << "2\n0 1";
        return 0;
    }

    vector<int> out;

    int i = 0;
    for (; (i - 1)*(i - 1) < N; ++i)
    {
        out.push_back(i);
    }

//    cout << "Delta: " << i << "\n";
    int delta = i;
    i = i - 1 + delta;
    for (; i <= N; i += delta)
    {
        out.push_back(i);
    }

    cout << out.size() << "\n";
    for (auto x: out)
    {
        cout << x << " ";
    }
}
