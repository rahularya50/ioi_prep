#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<pair<int, int>> points(N);
    const int DELTA = 1000;
    for (int i = 0; i != N; ++i) {
        int x, y;
        cin >> x >> y;
        points[i] = {x + DELTA, y + DELTA};
    }

    const int SIZE = 2001;

    vector<int> dp_x(SIZE);
    vector<int> dp_y(SIZE);

    for (int x = 0; x != SIZE; ++x) {
        dp_x[x] = abs(x - DELTA);
        dp_y[x] = abs(x - DELTA);
    }

    vector<int> new_dp_x(SIZE);
    vector<int> new_dp_y(SIZE);
    for (int i = 0; i != N; ++i) {
        int prev_x = (i == 0) ? DELTA : points[i - 1].first;
        int prev_y = (i == 0) ? DELTA : points[i - 1].second;
//        cout << prev_x << ", " << prev_y << "\n";
        for (int x = 0; x != SIZE; ++x) {
            int y = points[i].second;
            new_dp_x[x] = min(dp_x[x] + abs(y - prev_y), dp_y[y] + abs(x - prev_x));
        }
        for (int y = 0; y != SIZE; ++y) {
            int x = points[i].first;
            new_dp_y[y] = min(dp_x[x] + abs(y - prev_y), dp_y[y] + abs(x - prev_x));
        }
        swap(dp_x, new_dp_x);
        swap(dp_y, new_dp_y);
    }

    auto a = *min_element(dp_x.begin(), dp_x.end());
    auto b = *min_element(dp_y.begin(), dp_y.end());

    cout << min(a, b);
}
