#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long N;
    cin >> N;
    priority_queue<long long, vector<long long>, greater<long long>> stuff;
    for (long long i = 0; i != N; ++i)
    {
        long long temp;
        cin >> temp;
        stuff.push(temp);
    }
    long long out = 0;
    while (stuff.size() > 1)
    {
        auto x = stuff.top();
        stuff.pop();
        auto y = stuff.top();
        stuff.pop();
        out += x + y;
        stuff.push(x + y);
    }
    cout << out;
    return 0;
}
