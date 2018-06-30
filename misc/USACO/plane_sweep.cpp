#include <bits/stdc++.h>

using namespace std;

using point = pair<int, int>;
using rect = pair<point, point>;

int main() {
    int N;
    cin >> N;
    vector<rect> rects;
    vector<point> points;
    for (int i = 0; i != N; ++i) {
        int lx, ly, hx, hy;
        cin >> lx >> ly >> hx >> hy;
        rects.push_back({lx, ly}, {hx, hy});
        points.push_back({lx, ly});
        points.push_back({lx, hy});
        points.push_back({hx, ly});
        points.push_back({hx, hy});
    }

    sort(points.begin(), points.end());
}
