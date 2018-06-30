#include <bits/stdc++.h>

using namespace std;

int solve(vector<int> x)
{
    vector<pair<int, int>> start_finish;
    int left = x.size() - 1;
    int right = x.size() - 1;
    while (left >= 0)
    {
        if (right == x.size() - 1 || x[right + 1] < x[left])
        {
            start_finish.push_back({left, right});
            left -= 1;
            if (left == 0)
                break;
            if (x[left] > x[left + 1])
            {
                right = left;
            }
        }
        else
        {
            right += 1;
        }
    }


}

int main()
{
    int n;
    cin >> n;
    int out = 0;
    vector<vector<int>> matrix;
    for (int i = 0; i != n; ++i)
    {
        matrix.push_back({});
        for (int j = 0; j != n; ++j)
        {
            int temp;
            cin >> temp;
            matrix.back().push_back(temp);
        }
        out += solve(matrix.back());
    }
    for (int i = 0; i != n; ++i)
    {
        vector<int> x;
        for (int j = 0; j != n; ++j)
        {
            x.push_back(matrix[j][i]);
        }
        out += solve(x);
    }
    cout << out;
    return 0;
}
