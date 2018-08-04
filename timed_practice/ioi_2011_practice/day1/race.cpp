#include <bits/stdc++.h>

using namespace std;

struct edge {
    int dest;
    int len;
};

struct ret {
    int num_delta;
    int len_delta;
    map<int, int> min_nums; // len -> num
};

vector<vector<edge>> graph;

int N, K;

int go(int i, int parent, ret& out) {
    vector<ret> childs;
    int ans = numeric_limits<int>::max();
    for (auto x : graph[i]) {
        if (x.dest == parent) {
            continue;
        }
        childs.push_back({});
        ans = min(ans, go(x.dest, i, childs.back()));
        childs.back().len_delta += x.len;
        childs.back().num_delta += 1;
        if (childs.back().min_nums.find(K - childs.back().len_delta) != childs.back().min_nums.end()) {
            ans = min(ans, childs.back().min_nums[K - childs.back().len_delta] + childs.back().num_delta);
        }
    }

    if (childs.size() == 0) {
        out = {0, 0, {}};
        out.min_nums[0] = 0;
        return ans;
    }

    int maxI = 0;
    for (int i = 0; i != childs.size(); ++i) {
        if (childs[i].min_nums.size() > childs[maxI].min_nums.size()) {
            maxI = i;
        }
    }

    for (int i = 0; i != childs.size(); ++i) {
        if (i == maxI) {
            continue;
        }
        for (auto x : childs[i].min_nums) {
            if (childs[maxI].min_nums.find(K - childs[maxI].len_delta - childs[i].len_delta - x.first) != childs[maxI].min_nums.end()) {
                ans = min(ans, x.second + childs[i].num_delta + childs[maxI].num_delta + childs[maxI].min_nums[K - childs[maxI].len_delta - childs[i].len_delta - x.first]);
            }
        }
        for (auto x : childs[i].min_nums) {
            if (childs[maxI].min_nums.find(x.first + childs[i].len_delta - childs[maxI].len_delta) == childs[maxI].min_nums.end()) {
                childs[maxI].min_nums[x.first + childs[i].len_delta - childs[maxI].len_delta] =
                     x.second + childs[i].num_delta - childs[maxI].num_delta;
            } else {
                childs[maxI].min_nums[x.first + childs[i].len_delta - childs[maxI].len_delta] =
                min(childs[maxI].min_nums[x.first + childs[i].len_delta - childs[maxI].len_delta],
                     x.second + childs[i].num_delta - childs[maxI].num_delta);
            }
        }
    }
    swap(out, childs[maxI]);

    out.min_nums[-out.len_delta] = -out.num_delta;

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> K;

    graph = vector<vector<edge>>(N);
    for (int i = 0; i != N - 1; ++i) {
        int x, y, l;
        cin >> x >> y >> l;
        graph[x].push_back({y, l});
        graph[y].push_back({x, l});
    }

    ret out;
    auto x = go(0, -1, out);
    if (x == numeric_limits<int>::max()) {
        cout << -1 << "\n";
    } else {
        cout << x << "\n";
    }
}
