#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;

    bool in_kiss = false;
    int out = 0;
    int temp = 0;

    for (int i = 0; i != N; ++i)
    {
        temp = 0;
        in_kiss = false;
        string line;
        getline(cin, line);
        if (line.size() == 0)
        {
            i -= 1;
            continue;
        }
        for (auto x: line)
        {
            if (in_kiss)
            {
                if (x == '<')
                {
                    out += temp;
                    temp = 0;
                    in_kiss = false;
                }
                else if (x == '3')
                {
                    temp += 1;
                }
                else
                {
                    temp = 0;
                    in_kiss = false;
                }
            }

            if (!in_kiss)
            {
                if (x == '>')
                {
                    in_kiss = true;
                }
            }
        }
    }

    cout << out;

    return 0;
}
