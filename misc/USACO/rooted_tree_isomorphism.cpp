#include <bits/stdc++.h>

using namespace std;

long long getHashVal(int root, int prev, const vector<vector<int>>& tree)
{

}

int main()
{
    int k, n;
    cin >> k >> n;
    vector<vector<vector<int>>> trees(k, vector<vector<int>>(n));
    for (int i = 0; i != k; ++i)
    {
        for (int j = 0; j != n - 1; ++j)
        {
            int a, b;
            cin >> a >> b;
            trees[i][a - 1].push_back(b - 1);
            trees[i][b - 1].push_back(a - 1);
        }
    }
}
