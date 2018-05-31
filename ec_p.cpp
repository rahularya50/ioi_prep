#include <bits/stdc++.h>

using namespace std;

int make_low(int i, const vector<vector<int>>& graph, const vector<int>& pre, const vector<int>& parent, vector<int>& low) {
    if (low[i] != -1) {
        return low[i];
    }

//    cout << "Low of " << i << "with parent " << parent[i] << "\n";

    int best = pre[i];
    for (auto x : graph[i]) {
        if (pre[x] > pre[i]) {
//            cout << "Recursing " << x << "\n";
            best = min(best, make_low(x, graph, pre, parent, low));
        }
        else if (x != parent[i]) {
//            cout << "Back edge " << x << "\n";
            best = min(best, pre[x]);
        }
    }

    low[i] = best;
//    cout << "Returning " << best << " for i = " << i << "\n";
    return best;
}

int main() {
    int NC;
    cin >> NC;
    for (int i = 0; i != NC; ++i) {
        int N, M;
        cin >> N >> M;
        vector<vector<int>> graph(N);
        for (int j = 0; j != M; ++j) {
            int a, b;
            cin >> a >> b;
            graph[a - 1].push_back(b - 1);
            graph[b - 1].push_back(a - 1);
        }

        vector<int> parent(N, -1);

        vector<int> pre(N, -1);

        vector<int> todo = {0};
        int cnt = 0;
        while (todo.size() > 0) {
            int next = todo.back();
            todo.pop_back();
            if (pre[next] != -1) {
                continue;
            }
            pre[next] = cnt;
            ++cnt;
            for (auto x : graph[next]) {
                if (pre[x] == -1) {
                    parent[x] = next;
                    todo.push_back(x);
                }
            }
        }

        vector<int> low(N, -1);
        make_low(0, graph, pre, parent, low);

        vector<pair<int, int>> out;
        for (int j = 1; j != N; ++j) {
//            cout << j << ": " << low[j] << " " << pre[j] << "\n";
            if (low[j] >= pre[j]) {
                int par = parent[j];
                out.push_back({min(j, par), max(j, par)});
            }
        }

        sort(out.begin(), out.end());

        cout << "Caso #" << (i + 1) << "\n";

        if (out.size() == 0) {
            cout << "Sin bloqueos";
        } else {
            cout << out.size();
        }

        cout << "\n";

        for (auto x : out) {
            cout << (x.first + 1) << " " << (x.second + 1) << "\n";
        }
    }
}
