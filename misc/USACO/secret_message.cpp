#include <bits/stdc++.h>

using namespace std;

int main()
{
    string b;
    cin >> b;
    auto c = b;
    sort(c.begin(), c.end());
    map<char, vector<char>> mapping;
    for (int i = 0; i != b.size(); ++i)
    {
        mapping[c[i]].push_back(b[i]);
    }
    string out;
    char curr = '.';
    while (mapping[curr] != '.')
    {
        out.push_back(mapping[curr]);
        curr = mapping[curr];
    }
    reverse(out.begin(), out.end());
    cout << out << '.';

    return 0;
}
