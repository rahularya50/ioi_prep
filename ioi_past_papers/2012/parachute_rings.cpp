#include <bits/stdc++.h>

using namespace std;

const int SINGLETON = -1;
const int PATH = -3;

vector<int> endpoints_candidates[4];
bool valid[4];

array<int, 4> candidates;

vector<vector<int>> graph;

int N;

vector<int> degs;

void build_endpoints(int i) {
    valid[i] = true;
    for (int j = 0; j != N; ++j) {
        if (j == candidates[i]) {
            continue;
        }
        int cnt = 0;
        for (auto x : graph[j]) {
            if (x == candidates[i]) {
                continue;
            }
            ++cnt;
        }
        degs[j] = cnt;
    }
    vector<bool> explored(N, false);
    int prev = -1;
    for (int origin = 0; origin != N; ++origin) {
        if (explored[origin] || degs[origin] != 1 || origin == candidates[i]) {
            continue;
        }
        int pos = origin;
        do {
            if (degs[pos] > 2 || explored[pos]) {
                valid[i] = false;
                return;
            }
            explored[pos] = true;
            endpoints_candidates[i][pos] = PATH;

//            bool changed = false;

            for (auto x : graph[pos]) {
                if (x != candidates[i] && x != prev) {
                    prev = pos;
                    pos = x;
//                    changed = true;
                    break;
                }
            }

//            if (!changed) {
//                valid[i] = false;
//                return;
//            }

        } while (degs[pos] != 1);
        endpoints_candidates[i][origin] = pos;
        endpoints_candidates[i][pos] = origin;
        explored[pos] = true;
//        cout << "Path between " << origin << " -> " << pos << "\n";
    }
    for (int j = 0; j != N; ++j) {
        if (degs[j] == 0 && j != candidates[i]) {
            endpoints_candidates[i][j] = SINGLETON;
        }
        if (degs[j] != 0 && !explored[j] && j != candidates[i]) {
            valid[i] = false;
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int L;
    cin >> N >> L;
    int maxDegree = 0;
    int curr = N;
    vector<int> degrees(N);
    vector<int> endpoints(N, SINGLETON);
    degs = vector<int>(N);
    bool cycle = false;

    graph = vector<vector<int>>(N);

    for (int i = 0; i != 4; ++i) {
        endpoints_candidates[i] = vector<int>(N);
    }

    for (int t = 0; t != L; ++t) {
        int a;
        cin >> a;
        if (a == -1) {
            cout << curr << "\n";
        } else {
            int b;
            cin >> b;

            if (curr == 0) {
                continue;
            }

            graph[a].push_back(b);
            graph[b].push_back(a);
            ++degrees[a];
            ++degrees[b];
            auto oldMaxDegree = maxDegree;
            maxDegree = max(maxDegree, max(degrees[a], degrees[b]));

            if (maxDegree <= 2) {
                if (endpoints[a] == b) {
                    // forming cycle
//                    cout << "forming cycle\n";
                    if (cycle) {
                        curr = 0;
                        continue;
                    }
                    cycle = true;
                    curr = 1;
                    int prev = -1;
                    int pos = a;
                    while (pos != b) {
                        ++curr;
                        if (graph[pos][0] != prev) {
                            prev = pos;
                            pos = graph[pos][0];
                        } else {
                            prev = pos;
                            pos = graph[pos][1];
                        }
                    }
                } else {
                    // linking paths
//                    cout << "linking paths\n";
                    auto a2 = endpoints[a];
                    auto b2 = endpoints[b];
                    if (a2 == SINGLETON && b2 == SINGLETON) {
                        endpoints[a] = b;
                        endpoints[b] = a;
                    } else if (a2 == SINGLETON) {
                        endpoints[a] = b2;
                        endpoints[b2] = a;
                        endpoints[b] = PATH;
                    } else if (b2 == SINGLETON) {
                        endpoints[b] = a2;
                        endpoints[a2] = b;
                        endpoints[a] = PATH;
                    } else {
                        endpoints[a2] = b2;
                        endpoints[b2] = a2;
                        endpoints[a] = PATH;
                        endpoints[b] = PATH;
                    }
                }
            } else if (maxDegree >= 3) {
                if (oldMaxDegree < 3) {
                    // initializing
//                    cout << "initializing \n";
                    int x = (degrees[a] >= 3) ? a : b;
//                    cout << "x = " << x << "\n";
                    candidates[0] = x;
                    for (int i = 0; i != 3; ++i) {
                        candidates[i + 1] = graph[x][i];
                    }
                    curr = 0;
                    for (int i = 0; i != 4; ++i) {
                        build_endpoints(i);
                        curr += valid[i];
                    }
                } else {
                    curr = 0;
                    for (int i = 0; i != 4; ++i) {
                        if (!valid[i]) {
                            continue;
                        }
                        if (a != candidates[i] && b != candidates[i]) {
                            if (endpoints_candidates[i][a] == PATH || endpoints_candidates[i][b] == PATH || endpoints_candidates[i][a] == b) {
                                valid[i] = false;
                            } else {
                                auto a2 = endpoints_candidates[i][a];
                                auto b2 = endpoints_candidates[i][b];
                                if (a2 == SINGLETON && b2 == SINGLETON) {
                                    endpoints_candidates[i][a] = b;
                                    endpoints_candidates[i][b] = a;
                                } else if (a2 == SINGLETON) {
                                    endpoints_candidates[i][a] = b2;
                                    endpoints_candidates[i][b2] = a;
                                    endpoints_candidates[i][b] = PATH;
                                } else if (b2 == SINGLETON) {
                                    endpoints_candidates[i][b] = a2;
                                    endpoints_candidates[i][a2] = b;
                                    endpoints_candidates[i][a] = PATH;
                                } else {
                                    endpoints_candidates[i][a2] = b2;
                                    endpoints_candidates[i][b2] = a2;
                                    endpoints_candidates[i][a] = PATH;
                                    endpoints_candidates[i][b] = PATH;
                                }
                            }
                        }
                        curr += valid[i];
                    }
                }
//                for (int i = 0; i != 4; ++i) {
//                    cout << "i = " << i << ", banned = " << candidates[i] << ": { ";
//                    for (auto x : endpoints_candidates[i]) {
//                        cout << x << ", ";
//                    }
//                    cout << "}\n";
//                }
            }
        }
    }
}
