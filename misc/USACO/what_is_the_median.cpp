#include <bits/stdc++.h>

using namespace std;

int main()
{
    priority_queue<long long, vector<long long>, less<long long>> bottom_half;
    priority_queue<long long, vector<long long>, greater<long long>> top_half;

    long long val;
    while (cin >> val)
    {
        if (bottom_half.size() == 0 || val < bottom_half.top())
        {
            bottom_half.push(val);
            if (bottom_half.size() > top_half.size() + 1)
            {
                top_half.push(bottom_half.top());
                bottom_half.pop();
            }
        }
        else
        {
            top_half.push(val);
            if (bottom_half.size() < top_half.size())
            {
                bottom_half.push(top_half.top());
                top_half.pop();
            }
        }

        if (bottom_half.size() > top_half.size())
        {
            cout << bottom_half.top() << "\n";
        }
        else
        {
            cout << (bottom_half.top() + top_half.top()) / 2 << "\n";
        }

//        auto v_bottom_half = bottom_half;
//        auto v_top_half = top_half;
//        cout << "Bottom half: ";
//        while (v_bottom_half.size() > 0)
//        {
//            cout << v_bottom_half.top() << " ";
//            v_bottom_half.pop();
//        }
//        cout << "\nTop half: ";
//        while (v_top_half.size() > 0)
//        {
//            cout << v_top_half.top() << " ";
//            v_top_half.pop();
//        }
//        cout << "\n";
    }

    return 0;
}
