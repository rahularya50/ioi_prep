#include <bits/stdc++.h>

using namespace std;

int dp[51][51][51][51];
int raisins[50][50];
//int xcounts[51][51];
int ycounts[51][51];

int go(int minX, int minY, int maxX, int maxY) {
    if (dp[minX][minY][maxX][maxY] != 0) {
        return dp[minX][minY][maxX][maxY];
    }
    if (minX + 1 == maxX && minY + 1 == maxY) {
        return 0;
    }
    int best = numeric_limits<int>::max();
    for (int xCut = minX + 1; xCut < maxX; ++xCut) {
        best = min(best, go(minX, minY, xCut, maxY) + go(xCut, minY, maxX, maxY));
    }
    for (int yCut = minY + 1; yCut < maxY; ++yCut) {
        best = min(best, go(minX, minY, maxX, yCut) + go(minX, yCut, maxX, maxY));
    }
    for (int x = minX; x != maxX; ++x) {
        best += ycounts[x][maxY - 1];
        if (minY != 0) {
            best -= ycounts[x][minY - 1];
        }
    }
    dp[minX][minY][maxX][maxY] = best;
    return best;
}

int main() {
    int N, M;
    cin >> N >> M;
    for (int i = 0; i != N; ++i) {
        int cnt = 0;
        for (int j = 0; j != M; ++j) {
            cin >> raisins[i][j];
            cnt += raisins[i][j];
            ycounts[i][j] = cnt;
        }
    }
    cout << go(0, 0, N, M);
}
