#include <bits/stdc++.h>

using namespace std;

struct obj {
    int x;
    int y;
    int xDelta;
    int yDelta;
    int rand;
};

struct objcmp {
    operator()(obj x, obj y) { return x.rand < y.rand; }
};

int FREE = 0;
int ROCK = 1;
int BUSH = 2;
int PATH = 3;

int M, N, K;

bool valid(int x, int y) {
    if (x < 0 || x >= M) {
        return false;
    }
    if (y < 0 || y >= N) {
        return false;
    }
    return true;
}

int score(const vector<vector<int>>& grid) {
//    cout << "start scoring!\n";
    int out = 0;
    for (int i = 0; i != M; ++i) {
        for (int j = 0; j != N; ++j) {
            if (grid[i][j] != PATH) {
                continue;
            }
            int cnt = 0;
            if (i != 0 && grid[i - 1][j] == PATH) {
                ++cnt;
            }
            if (i != M - 1 && grid[i + 1][j] == PATH) {
                ++cnt;
            }
            if (j != 0 && grid[i][j - 1] == PATH) {
                ++cnt;
            }
            if (j != N - 1 && grid[i][j + 1] == PATH) {
                ++cnt;
            }
            if (cnt == 1) {
                ++out;
            }
        }
    }
//    cout << "score = " << out << "\n";
    return out;
}

int main() {
    cin >> M >> N >> K;

    vector<vector<int>> original_grid(M, vector<int>(N));
    for (auto& x : original_grid) {
        for (auto& y : x) {
            char c;
            cin >> c;
            if (c == '.'){
                y = FREE;
            } else {
                y = ROCK;
            }
        }
    }
//    cout << "K = " << K << "\n";

    int best = 0;
    auto best_grid = original_grid;

    for (int i = 0; i != 20; ++i) {
        auto grid = original_grid;
        // dfs maze construction

        deque<obj> todo;
        todo.push_back({rand() % M, rand() % N, 0, 1, rand()});
        while (todo.size() > 0) {
            auto pos = todo.front();
            todo.pop_front();

            if (grid[pos.x][pos.y] == PATH) {
                grid[pos.x][pos.y] = BUSH;
                continue;
            }

            auto leftX = pos.x - pos.yDelta;
            auto leftY = pos.y + pos.xDelta;
            auto rightX = pos.x + pos.yDelta;
            auto rightY = pos.y - pos.xDelta;
            auto nextX = pos.x + pos.xDelta;
            auto nextY = pos.y + pos.yDelta;

            bool fail;
            if (valid(leftX, leftY) && grid[leftX][leftY] == PATH) {
                fail = true;
            } else if (valid(rightX, rightY) && grid[rightX][rightY] == PATH) {
                fail = true;
            } else if (valid(nextX, nextY) && grid[nextX][nextY] == PATH) {
                fail = true;
            } else {
                fail = false;
            }

            if (fail) {
                grid[pos.x][pos.y] = BUSH;
                continue;
            }

            grid[pos.x][pos.y] = PATH;

            if (valid(leftX, leftY) && grid[leftX][leftY] == FREE) {
                todo.push_back({leftX, leftY, -pos.yDelta, pos.xDelta, rand()});
            }
            if (valid(rightX, rightY) && grid[rightX][rightY] == FREE) {
                todo.push_back({rightX, rightY, pos.yDelta, -pos.xDelta, rand()});
            }
            if (valid(nextX, nextY) && grid[nextX][nextY] == FREE) {
                todo.push_back({nextX, nextY, pos.xDelta, pos.yDelta, 0});
            }
        }

        for (auto& x : grid) {
            for (auto& y : x) {
                if (y == 0) {
                    y = BUSH;
                }
            }
        }

        auto curr = score(grid);
        if (curr > best) {
//            cout << curr << "\n";
            best_grid = grid;
            best = curr;
        }
    }

//    cout << "done!\n";

    for (auto& x : best_grid) {
        for (auto& y : x) {
            if (y == BUSH) {
                cout << "X";
            } else if (y == PATH) {
                cout  << ".";
            } else {
                cout << "#";
            }
        }
        cout << "\n";
    }

}
