#include <bits/stdc++.h>

using namespace std;

int main()
{
    set<int> v1;
    set<int> v2;
    for (int i = 0; i != 6; ++i)
    {
        int temp;
        cin >> temp;
        v1.insert(temp);
        if (temp == 6)
            v1.insert(9);
        if (temp == 9)
            v1.insert(6);
    }
    for (int i = 0; i != 6; ++i)
    {
        int temp;
        cin >> temp;
        v2.insert(temp);
        if (temp == 6)
            v2.insert(9);
        if (temp == 9)
            v2.insert(6);
    }

    set<int> possibles;
    for (auto x: v1)
    {
        for (auto y: v2)
        {
            possibles.insert(10*x + y);
            possibles.insert(10*y + x);
        }
    }

    int Q;
    cin >> Q;
    for (int i = 0; i != Q; ++i)
    {
        int q;
        cin >> q;
        cout << (possibles.find(q) == possibles.end() ? "No" : "Yes") << "\n";
    }

    return 0;
}
