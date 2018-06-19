#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M;
    cin >> N >> M;

    vector<pair<int, int>> teleporters(N);
    vector<int> segstarts = {0};
    for (auto& x : teleporters) {
        cin >> x.first >> x.second;
        segstarts.push_back(x.first);
        segstarts.push_back(x.second);
    }

    sort(segstarts.begin(), segstarts.end());

    vector<int> nexts(2*N + 1, -1);
    for (auto x : teleporters) {
        auto i = lower_bound(segstarts.begin(), segstarts.end(), x.first) - segstarts.begin();
        auto j = lower_bound(segstarts.begin(), segstarts.end(), x.second) - segstarts.begin();
        nexts[j - 1] = i;
        nexts[i - 1] = j;
    }

    vector<bool> visited(2*N + 1, false);
    int path_len = 0;
    int pos = 0;
    visited[0] = true;
    while (pos != 2*N) {
        ++path_len;
        pos = nexts[pos];
        visited[pos] = true;
     }

     vector<int> cycles(M);

     for (int i = 1; i != 2*N + 1; ++i) {
        if (visited[i]) {
            continue;
        }
        int pos = i;
        int cnt = 0;
        while (!visited[pos]) {
            ++cnt;
            visited[pos] = true;
            pos = nexts[pos];
        }
        cycles.push_back(cnt);
//        cout << "Cycle size: " << cnt << "\n";
     }

     int out = path_len;
     sort(cycles.begin(), cycles.end());
     for (int i = 0; i != M; ++i) {
        out += cycles[cycles.size() - i - 1] + 2;
     }

     if (cycles.size() < 2*M && cycles.size() % 2 == 1) {
        --out;
     }

     cout << out << "\n";
}
