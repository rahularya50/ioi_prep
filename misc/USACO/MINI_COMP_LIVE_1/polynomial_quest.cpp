#include <bits/stdc++.h>

using namespace std;

bool trial(int N, vector<int>& out)
{
    set<int> possible;
    for (auto x: out)
    {
        for (auto y: out)
        {
            if (x + y <= N)
            {
                possible.insert(x + y);
            }
            if (possible.size() == N + 1)
            {
//                cout << "yay";
                return true;
            }
        }
    }
    return possible.size() == (N + 1);
}

bool go(int N, int cap, int so_far, vector<int>& out)
{
//    for (auto x: out)
//    {
//        cout << x << " ";
//    }
//    cout << "\n";
    if (so_far > N || (out.size() + 1)*(out.size() + 1) > cap)
    {
//        cout << "Trialing";
        return trial(N, out);
    }

    if ((out.size() + 1)*(out.size() + 1) <= cap)
    {
        out.push_back(so_far);
        if (go(N, cap, so_far + 1, out))
        {
            return true;
        }
    }
    out.pop_back();
    return go(N, cap, so_far + 1, out);
}

int main()
{
    int N;
    cin >> N;
    vector<int> a;
    bool b = go(N, 4*N + 1, 0, a);
    if (!b)
    {
        cout << "No solution";
        return 0;
    }
    cout << a.size() << "\n";
    for (auto x: a)
    {
        cout << x << " ";
    }
}
