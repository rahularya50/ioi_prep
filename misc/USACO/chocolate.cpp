#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cout >> N;
    vector<int> vals;
    set<int> remaining;
    for (int i = 0; i != N; ++i)
    {
        int temp;
        cin >> temp;
        vals.push_back(temp);
        remaining.insert(temp);
    }
}
