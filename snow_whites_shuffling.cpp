#include <bits/stdc++.h>

using namespace std;

int main()
{
    int M, K;
    cin >> M >> K;
    deque<int> first;
    deque<int> second;

    for (int i = 0; i != M; ++i)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int x;
            cin >> x;
            first.push_front(x);
            if (first.size() >= K)
            {
                second.push_front(first.back());
                first.pop_back();
            }
        }
        else if (type == 2)
        {
            first.push_front(second.front());
            second.pop_front();
            second.push_front(first.back());
            first.pop_back();
        }
        else if (type == 3)
        {
//            cout << "test";
            int y;
            cin >> y;
            y -= 1;
            if (y >= K - 1)
            {
                cout << second[y - K + 1] << "\n";
            }
            else
            {
                cout << first[y] << "\n";
            }
        }
    }
}
