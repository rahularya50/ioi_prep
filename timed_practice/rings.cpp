#include <bits/stdc++.h>

using namespace std;;

const int FAIL = -1;
const int NONE = -2;

int check_chain(vector<vector<int>>& graph, vector<int>& component, vector<int>& comp_sizes) {
    component = vector<int>(graph.size(), -1);
    comp_sizes = vector<int>(graph.size(), -1);
    int cycle = -1;
    for (int i = 0; i != graph.size(); ++i) {
        if (component[i] != -1) {
            continue;
        }
        vector<pair<int, int>> todo = {{i, -1}}; // {node, prev}
        int n = 0;
        while (todo.size() > 0) {
            auto x = todo.back();
            todo.pop_back();
            ++n;
            auto curr = x.first;
            auto prev = x.second;
            if (graph[curr].size() > 2) {
                return FAIL;
            }
            if (component[curr] != -1) {
                if (cycle == -1) {
                    cycle = i;
                    continue;
                } else {
                    // two cycles have been found
                    return FAIL;
                }
            }
            component[curr] = i;
            for (auto x : graph[curr]) {
                if (x == prev) {
                    continue;
                }
                todo.push_back({x, curr});
            }
        }
        comp_sizes[i] = n;
    }
    if (cycle != -1) {
        return cycle;
    }
    return NONE;
}

int get_component(int i, vector<int>& component) {
    if (component[i] == i) {
        return i;
    }
    return get_component(component[i], component);
}

bool add_link(int i, int j, vector<vector<int>>& graph, vector<int>& component, vector<int>& comp_sizes) {
    graph[i].push_back(j);
    graph[j].push_back(i);
    if (graph[i].size() > 2 || graph[j].size() > 2) {
        return false;
    }

    auto a = get_component(i, component);
    auto b = get_component(j, component);

    if (a == b) {
        return false;
    }

    if (comp_sizes[a] > comp_sizes[b]) {
        component[b] = a;
        comp_sizes[a] += comp_sizes[b];
    } else {
        component[a] = b;
        comp_sizes[b] += comp_sizes[a];
    }

    return true;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, L;
    cin >> N >> L;
    int out = N;
    vector<vector<int>> graph(N);
    vector<int> component(N);
    for (int i = 0; i != N; ++i) {
        component[i] = i;
    }
    vector<int> comp_sizes(N, 1);
    int cycle = -1;
    int max_deg = 0;

    int trials[4];
    bool valid[4];
    vector<vector<int>> trial_graphs[4];
    vector<int> trial_component[4];
    vector<int> trial_comp_sizes[4];

    for (int q = 0; q != L; ++q) {
        int x;
        cin >> x;
        if (x == -1) {
            cout << out << "\n";
        } else {
            int a = x;
            int b;
            cin >> b;
            if (max_deg <= 2) {
                auto succ = add_link(a, b, graph, component, comp_sizes);
                if (!succ) {
                    if (graph[a].size() > 2 || graph[b].size() > 2) {
//                        cout << "link created a vertex with deg = 3\n";
                        // aieee!!!
                        // triple vertex created
                        max_deg = 3;
                        if (graph[a].size() == 3) {
                            trials[0] = a;
                        } else {
                            trials[0] = b;
                        }
//                        cout << "deg3v = " << trials[0] << "\n";
                        for (int i = 1; i != 4; ++i) {
                            trials[i] = graph[trials[0]][i - 1];
//                            cout << "trials[" << i << "] = " << trials[i] << "\n";
                        }

                        // time to make the fake graphs!
                        // #fakegraphs #fakenews

                        for (int i = 0; i != 4; ++i) {
                            trial_graphs[i] = graph;
                            trial_graphs[i][trials[i]] = {};
                            for (auto& x : trial_graphs[i]) {
                                vector<int> alt;
                                for (auto y : x) {
                                    if (y != trials[i]) {
                                        alt.push_back(y);
                                    }
                                }
                                swap(x, alt);
                            }
                        }

//                        cout << "newgraphs built!\n";

                        out = 0;
                        for (int i = 0; i != 4; ++i) {
                            auto x = check_chain(trial_graphs[i], trial_component[i], trial_comp_sizes[i]);
                            if (x == NONE) {
                                ++out;
                                valid[i] = true;
                            } else {
                                valid[i] = false;
                            }
                        }

                    } else {
//                        cout << "link created a cycle\n";
                        // cycle created
                        if (cycle != -1) {
//                            cout << "link created a *second* disjoint cycle\n";
                            out = 0;
                            // can't have two cycles, now can we?
                            // note that these cycles must be disjoint, otherwise a triple vertex will exist
                        } else {
                            cycle = get_component(a, component);
                            out = comp_sizes[cycle]; // cycle sizes are fixed
                        }
                    }
                    // either a cycle was created, or the base graph is no longer OK
                }
            } else {
                out = 0;
                for (int i = 0; i != 4; ++i) {
                    if (!valid[i]) {
                        continue;
                    }
                    if (a == trials[i] || b == trials[i] || add_link(a, b, trial_graphs[i], trial_component[i], trial_comp_sizes[i])) {
                        ++out;
                    } else {
                        valid[i] = false;
                    }
                }
            }
        }
    }
}
