#include <bits/stdc++.h>

using namespace std;

vector<int> dp;
vector<pair<int, int>> parent;
vector<vector<pair<int, int>>> graph;
vector<int> num_children;

int N, C;

int dfs(int i, int best, vector<int>& skip, const vector<int>& pre) {
//    cout << "DFSing " << i << "\n";
//    cout << "Pre[" << i << "] = " << pre[i] << "\n";
//    cout << "Best = " << best << "\n";
    vector<int> todo = {best};
    for (auto x : graph[i]) {
        int b = x.second;
        if (b == parent[i].first) {
            continue;
        }
        todo.push_back(b);
    }
    for (int j = todo.size() - 1; j != 0; --j) {
        dfs(todo[j], (j == 1) ? best : pre[todo[j - 1]], skip, pre);
    }
//    cout << "skip[pre[" << i << "]] = " << best << "\n";
    skip[pre[i]] = best;
    return best;
}

int go(int i);

int go2(int min_i, int to_remove, vector<vector<int>>& dp2, const vector<int>& skip, const vector<int>& pre_order) {
//    cout << "evaluating dp2[" << min_i << "][" << to_remove << "] \n";
    if (to_remove <= 0) {
//        cout << "success! \n";
        return 0;
    }
    if (min_i == pre_order.size() || min_i == -1) {
//        cout << "failure :( \n";
        return -2;
    }
    if (dp2[min_i][to_remove] != -1) {
//        cout << "dp2[" << min_i << "][" << to_remove << "] = " << dp2[min_i][to_remove] << "\n";
        return dp2[min_i][to_remove];
    }
    auto a = go2(min_i + 1, to_remove, dp2, skip, pre_order);
    int lower = pre_order[min_i];
    int upper = parent[lower].first;
    int cost = parent[lower].second;
    int recurse_cost = go(lower);
    auto b = go2(skip[min_i], to_remove - num_children[pre_order[min_i]], dp2, skip, pre_order);
    if (recurse_cost == -2 || b == -2) {
        dp2[min_i][to_remove] = a;
//        cout << "dp2[" << min_i << "][" << to_remove << "] = " << dp2[min_i][to_remove] << "\n";
        return dp2[min_i][to_remove];
    }
    if (a == -2) {
        dp2[min_i][to_remove] = b + recurse_cost + cost;
//        cout << "dp2[" << min_i << "][" << to_remove << "] = " << dp2[min_i][to_remove] << "\n";
        return dp2[min_i][to_remove];
    }
    dp2[min_i][to_remove] = min(a, b + cost + recurse_cost);
//    cout << "dp2[" << min_i << "][" << to_remove << "] = " << dp2[min_i][to_remove] << "\n";
    return dp2[min_i][to_remove];
}

int go(int i) {
//    cout << "Dping " << i << "\n";
    if (dp[i] != -1) {
        return dp[i];
    }
    vector<int> pre_order;
    vector<int> pre(N);
    vector<int> tovisit = {i};
    while (tovisit.size() > 0) {
        int a = tovisit.back();
        tovisit.pop_back();
        pre_order.push_back(a);
        pre[a] = pre_order.size() - 1;
//        cout << "pre[" << a << "] = " << pre[a] << "\n";
        for (auto x : graph[a]) {
            int b = x.second;
            if (b == parent[a].first) {
                continue;
            }
            tovisit.push_back(b);
        }
    }

//    cout << "Building skips\n";

    vector<int> skip(pre_order.size(), -1);
    dfs(i, -1, skip, pre);

//    cout << "Beginning second dp\n";

    if (pre_order.size() <= C) {
        dp[i] = 0;
//        cout << "dp[" << i << "] = " << dp[i] << "\n";
        return 0;
    }

    vector<vector<int>> dp2(pre_order.size(), vector<int>(pre_order.size() - C + 1, -1));
    dp[i] = go2(1, pre_order.size() - C, dp2, skip, pre_order);
//    cout << "dp[" << i << "] = " << dp[i] << "\n";
    return dp[i];
}

int count_children(int i) {
    int a = 1;
    for (auto x : graph[i]) {
        int b = x.second;
        if (b == parent[i].first) {
            continue;
        }
        a += count_children(b);
    }
    num_children[i] = a;
//    cout << "num[" << i << "] = " << a << "\n";
    return a;
}

int main() {
    cin >> N >> C;
//    vector<vector<pair<int, int>>> graph;
    graph = vector<vector<pair<int, int>>>(N);
    for (int i = 0; i != N - 1; ++i) {
        int a, b, l;
        cin >> a >> b >> l;
        graph[a - 1].push_back({l, b - 1});
        graph[b - 1].push_back({l, a - 1});
    }

    parent = vector<pair<int, int>>(N, {-1, -1});
    num_children = vector<int>(N);
    vector<int> tovisit = {0};
    while (tovisit.size() > 0) {
        int a = tovisit.back();
        tovisit.pop_back();
        for (auto x : graph[a]) {
            int b = x.second;
            if (b == parent[a].first) {
                continue;
            }
            parent[b] = {a, x.first};
            tovisit.push_back(b);
        }
    }
    count_children(0);

    dp = vector<int>(N, -1);
    cout << go(0);
}
