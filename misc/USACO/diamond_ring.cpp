#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> v;
    for (int i = 0; i != N; ++i)
    {
        int temp;
        cin >> temp;
        v.push_back(temp);
    }

    vector<int> best_maxes = {0};

    for (auto x: v)
    {
        best_maxes.push_back(x + max(0, best_maxes.back()));
    }

    auto total = accumulate(v.begin(), v.end(), 0);

    vector<int> best_mins = {0};
    for (auto x: v)
    {
        best_mins.push_back(x + min(0, best_mins.back()));
    }

    cout << max(*max_element(best_maxes.begin(), best_maxes.end()), total - *min_element(best_mins.begin(), best_mins.end()));
}
