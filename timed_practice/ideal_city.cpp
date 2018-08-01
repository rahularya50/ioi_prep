#include <bits/stdc++.h>

using namespace std;

using point = pair<int, int>;

struct interval {
    int l;
    int r; // l <= x < r
    int y;
};

vector<pair<int, int>> points;

vector<vector<int>> graph;
vector<int> int_size;
vector<int> subtree_size;
vector<int> parent;

int dfs_subtree_size(int i) {
    if (subtree_size[i] != -1) {
        return subtree_size[i];
    }
    int out = int_size[i];
    for (auto x : graph[i]) {
        if (x == parent[i]) {
            continue;
        }
        parent[x] = i;
        out += dfs_subtree_size(x);
    }
    subtree_size[i] = out;
    return out;
}

long long go() {
        // sort first by x, then y, so the array will be in reading order
    stable_sort(points.begin(), points.end(), [](point x, point y){return x.first < y.first; });
    stable_sort(points.begin(), points.end(), [](point x, point y){return x.second < y.second; });

    interval curr_int = {-1, -1, -1};

    vector<interval> intervals;

    for (auto x : points) {
        if (x.second != curr_int.y) {
            if (curr_int.l != -1) {
                intervals.push_back(curr_int);
            }
            curr_int = {x.first, x.first, x.second};
        }
        if (x.first != curr_int.r) {
            // interval ended
            intervals.push_back(curr_int);
            curr_int = {x.first, x.first + 1, x.second};
        }
        curr_int.r = x.first + 1;
    }
    intervals.push_back(curr_int);

//    for (auto i : intervals) {
//        cout << "{" << i.l << ", " << i.r << ", " << i.y << "}\n";
//    }

    int_size = vector<int>(intervals.size());
    for (int i = 0; i != intervals.size(); ++i) {
        int_size[i] = intervals[i].r - intervals[i].l;
    }

    graph = vector<vector<int>>(intervals.size());
    int curr_i = 0;
    int trial_i = 0;
    while (curr_i != intervals.size() && trial_i != intervals.size()) {
        if (intervals[trial_i].y <= intervals[curr_i].y) {
            ++trial_i;
        } else if (intervals[trial_i].y > intervals[curr_i].y + 1) {
            ++curr_i;
        } else if (intervals[trial_i].r <= intervals[curr_i].l) {
            ++trial_i;
        } else if (intervals[trial_i].l >= intervals[curr_i].r) {
            ++curr_i;
        } else if (intervals[trial_i].r >= intervals[curr_i].r) {
            graph[curr_i].push_back(trial_i);
            graph[trial_i].push_back(curr_i);
            ++curr_i;
        } else {
            graph[curr_i].push_back(trial_i);
            graph[trial_i].push_back(curr_i);
            ++trial_i;
        }
    }

//    for (int i = 0; i != graph.size(); ++i) {
//        cout << i << ": {";
//        for (auto x : graph[i]) {
//            cout << x << ", ";
//        }
//        cout << "}\n";
//    }

    parent = vector<int>(graph.size(), -1);
    subtree_size = vector<int>(graph.size(), -1);
    dfs_subtree_size(0);

//    for (auto x : subtree_size) {
//        cout << x << ", ";
//    }
//    cout << "\n";

    long long out = 0;
    for (int i = 1; i != graph.size(); ++i) {
        out += static_cast<long long>(subtree_size[i]) * static_cast<long long>(subtree_size[0] - subtree_size[i]);
        out %= 1000000000;
    }
//    cout << "Out = " << out << "\n";
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    points = vector<pair<int, int>>(N);
    for (auto& x : points) {
        cin >> x.first >> x.second;
    }

    long long out = 0;
    out += go();
    for (auto& x : points) {
        swap(x.first, x.second);
    }
    out += go();
    cout << (out % 1000000000) << "\n";
}
