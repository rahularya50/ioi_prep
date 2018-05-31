#include <bits/stdc++.h>

using namespace std;

int main()
{
    std::map<std::string, int> names = {
        {"Sowon", 0}, {"Yerin", 1}, {"Eunha", 2}, {"Yuju", 3}, {"SinB", 4}, {"Umji", 5}
    }
    int N;
    cin >> N;

    vector<int> images;
    for (int i = 0; i != N; ++i)
    {
        string line;
        getline(cin, line);
        int elem = 0;
        string name;
        for (char c : line)
        {
            if (c == ',')
            {
                elem += pow(2, names[name]);
                name = "";
                break;
            }
            name += c;
        }
        elem += pow(2, names[name]);
    }

    for (auto val: images)
    {
        cout << val;
    }

    return 0;
}
