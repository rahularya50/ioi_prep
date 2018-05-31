#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, M, K;
    cin >> N >> M >> K;

    vector<pair<int, int>> crows;
    crows.reserve(K);
    for (int i = 0; i != K; ++i) {
        int r, c;
        cin >> r >> c;
        crows.push_back({r, c});
    }

    vector<vector<int>> cost(N, vector(-1, M));
    int visited = 0;
    deque<pair<pair<int, int>, pair<int, int>>> to_visit;
    for (auto crow : crows) {
        to_visit.push_back({{0, 0}, crow});
    }

    while (visited < N * M) {
        auto todo = to_visit.front();
        to_visit.pop_front();
        int dist, dir, x, y;
        dist = todo.first.first;
        dir = todo.first.second;
        x = todo.second.first;
        y = todo.second.second;

        if (cost[x][y] == -1) {
            continue;
        }
        cost[x][y] = dist;

    }

}
