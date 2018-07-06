#include <bits/stdc++.h>

using namespace std;

int grid[2001][2001];
int explored[2001][2001];
int root[100002];
int rootsize[100002];

//vector<vector<int>> grid;
//vector<vector<bool>> explored;
//vector<int> root;
//vector<int> rootsize;

int cnt;

vector<pair<int, int>> border;
vector<pair<int, int>> new_border;
vector<int> updates;
int N, K;

inline int getRoot(int p) {
    int p2 = p;
    while (root[p2] != p2) p2 = root[p2];
    while (root[p] != p) {
        auto p3 = root[p];
        root[p] = p2;
        p = p3;
    }
    return p2;
}

inline void join(int x, int y, int a, int b) {
    if (a < 0 || a >= N || b < 0 || b >= N) return;
    if (explored[a][b] || grid[x][y] == grid[a][b]) return;
    explored[a][b] = true;
    if (grid[a][b] == 0) {
        updates.push_back(grid[x][y]);
        new_border.push_back({a, b});
        int p1 = getRoot(grid[a][b]);
        ++rootsize[p1];
    } else {
        int p1 = getRoot(grid[a][b]);
        int p2 = getRoot(grid[x][y]);
        if (p1 == p2) return;
        if (rootsize[p1] > rootsize[p2]) {
            root[p2] = p1;
            rootsize[p1] += rootsize[p2];
        }
        else {
            root[p1] = p2;
            rootsize[p2] += rootsize[p1];
        }
        --cnt;
    }
}

int main() {
    scanf("%d %d", &N, &K);
    cnt = K;
    border = vector<pair<int, int>>(K);
    for (int i = 0; i != K; ++i) {
        scanf("%d %d", &border[i].first, &border[i].second);
        --border[i].first;
        --border[i].second;
        grid[border[i].first][border[i].second] = i + 1;
        root[i + 1] = i + 1;
        rootsize[i + 1] = 1;
    }
    int t = 0;
    while (cnt > 1) {
        for (int i = 0; i != border.size(); ++i) {
            auto p = border[i];
            auto x = p.first;
            auto y = p.second;
//            cout << "Exploring " << x << ", " << y << "\n";
            join(x, y, x + 1, y);
            join(x, y, x - 1, y);
            join(x, y, x, y + 1);
            join(x, y, x, y - 1);
        }
        for (int i = 0; i != updates.size(); ++i) {
            grid[new_border[i].first][new_border[i].second] = updates[i];
            explored[new_border[i].first][new_border[i].second] = false;
        }
        updates.clear();
        swap(border, new_border);
        new_border.clear();
        ++t;
    }
    printf("%d", t - 1);
}

