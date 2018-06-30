#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    long long N;
    cin >> N;
    long long contigious = 0;
    long long out = 0;
    for (long long i = 0; i != N; ++i)
    {
        long long temp;
        cin >> temp;
        out += max(temp - contigious, static_cast<long long>(0));
        contigious = temp;
    }
    cout << out;

}
