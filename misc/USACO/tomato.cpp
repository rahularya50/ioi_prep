#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, T, M;
    cin >> N >> T >> M;
    vector<pair<int, int>> poses;
    poses.reserve(M);
    for (int i = 0; i != M; ++i)
    {
        int temp;
        cin >> temp;
        poses.push_back({temp, temp});
    }
    sort(poses.begin(), poses.end());
    for (int i = 0; i != T; ++i)
    {
        vector<pair<int, int>> new_poses;
        int out = 0;
        for (auto x: poses)
        {
            if (new_poses.size() == 0 || new_poses.back().second < x.first - 1)
            {
                out += min(x.second + 1, N) - max(1, x.first - 1) + 1;
                new_poses.push_back({max(1, x.first - 1), min(x.second + 1, N)});
            }
            else
            {
                out += min(x.second + 1, N) - new_poses.back().second;
                new_poses.back().second = min(x.second + 1, N);
            }
        }
        poses = new_poses;
        cout << out << "\n";
    }
}
