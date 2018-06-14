#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, M, W;
    cin >> N >> M >> W;
    vector<int> cars(N);
    vector<int> cnt(M);
    for (int i = 0; i != N; ++i) {
        int x;
        cin >> x;
        cars[i] = x;
        ++cnt[x - 1];
    }
    vector<int> nexts(M);
    for (int i = 1; i != M; ++i) {
        nexts[i] = nexts[i - 1] + cnt[i - 1];
    }
    vector<int> vals(N);
    for (int i = 0; i != N; ++i) {
        vals[i] = nexts[cars[i] - 1];
        ++nexts[cars[i] - 1];
    }
//    for (auto x : vals) {
//        cout << x << " ";
//    }
//    cout << "\n";

    int emptied = 0;
    vector<vector<int>> out;
    while (emptied != N) {
        vector<int> starts;
        vector<int> ends;
        int active_i = emptied;
        int active_val = vals[active_i];
        vals[active_i] = -1;
        for (int i = 0; i != W; ++i) {
            while (active_i != N && (active_val == -1 || active_val == active_i)) {
                ++active_i;
                emptied = active_i;
                if (active_i != N) {
                active_val = vals[active_i];
                vals[active_i] = -1;
                }
            }
            if (active_i == N) {
                break;
            }
            starts.push_back(active_i);
            int dest;
            if (i == W - 1) {
                dest = emptied;
            } else {
                dest = active_val;
            }
            ends.push_back(dest);

//            cout << "moving from " << active_i << " to " << dest << "\n";
            active_i = dest;
            int temp = active_val;
            active_val = vals[dest];
            vals[dest] = temp;
        }

        if (starts.size() > 0) {
            out.push_back({});
            out.back().push_back(starts.size());
            for (int i = 0; i != starts.size(); ++i) {
                out.back().push_back(starts[i] + 1);
                out.back().push_back(ends[i] + 1);
            }
        }
    }

    cout << out.size() << "\n";
    for (auto& x : out) {
        for (auto y : x) {
            cout << y << " ";
        }
        cout << "\n";
    }
}
