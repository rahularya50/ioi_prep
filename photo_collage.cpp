#include <bits/stdc++.h>

using namespace std;

int main()
{
    std::map<std::string, int> names = {
        {"Sowon", 0}, {"Yerin", 1}, {"Eunha", 2}, {"Yuju", 3}, {"SinB", 4}, {"Umji", 5},
    };

    int N;
    cin >> N;
    cin.ignore();

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
                continue;
            }
            name += c;
        }
        elem += pow(2, names[name]);
        images.push_back(elem);
//        cout << elem << "\n";
    }

    vector<unsigned long long> prev;
    for (int max_index = 0; max_index < N; ++max_index)
    {
        vector<unsigned long long> next;
        for (int target = 0; target < pow(2, 6); ++target)
        {
            if (target == 0)
            {
                next.push_back(1);
                continue;
            }
            if (max_index == 0)
            {
                next.push_back(target == images[max_index]);
                continue;
            }
            if ((images[max_index] & target) == images[max_index])
            {
                next.push_back(prev[target] + prev[target - images[max_index]]);
            }
            else
            {
                next.push_back(prev[target]);
            }
        }
//        for (auto elem: next)
//        {
//            cout << elem << " ";
//        }
//        cout << "\n";
        prev = next;
    }

    cout << prev[pow(2, 6) - 1];

    return 0;
}
