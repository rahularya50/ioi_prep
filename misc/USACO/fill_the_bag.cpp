#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int N, K;
    cin >> N >> K;
    vector<int> weight_count(100);
    for (int i = 0; i != N; ++i)
    {
        int temp;
        cin >> temp;
        weight_count[temp] += 1
    }
    vector<int> cache = { 0 };
}
