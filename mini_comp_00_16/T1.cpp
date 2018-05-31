#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;

    vector<string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    cout << days[(N + (N - 1997) / 4 - (N - 1901) / 100 + (N - 1601) / 400 + 2) % 7];

    return 0;
}
