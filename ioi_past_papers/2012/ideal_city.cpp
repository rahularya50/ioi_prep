#include <bits/stdc++.h>

using namespace std;

const long long MODULUS = 1000000000;

struct interval {
    long long start_x;
    long long end_x;
    long long y;
    long long parent;
    vector<long long> l_edges; // built
    vector<long long> r_edges; // built
    vector<long long> edges; // built
    vector<long long> num_closest_children[2]; // built
    vector<long long> dist_closest_children[2];
    long long subtree_size; // built
};

vector<interval> intervals;

long long dfs_subtree_size(long long i) {
    auto& a = intervals[i];
    long long out = a.end_x - a.start_x;
    for (auto x : a.edges) {
        if (x == a.parent) {
            continue;
        }
        out += dfs_subtree_size(x);
    }
    a.subtree_size = out % MODULUS;
    return a.subtree_size;
}

void dfs_closest_children(long long i) {
//    cout << "closest_children(" << i << ")\n";
    auto& a = intervals[i];
    a.num_closest_children[0] = vector<long long>(a.end_x - a.start_x);
    a.num_closest_children[1] = vector<long long>(a.end_x - a.start_x);
    a.dist_closest_children[0] = vector<long long>(a.end_x - a.start_x);
    a.dist_closest_children[1] = vector<long long>(a.end_x - a.start_x);

    for (auto x : a.edges) {
        if (x == a.parent) {
            continue;
        }
        dfs_closest_children(x);
    }

    for (long long i = 0; i != 2; ++i) {
        long long curr = 0;
        long long curr_dist = 0;
        const auto& group = (i == 0) ? a.l_edges : a.r_edges;
        if (group.size() == 0) {
            continue;
        }
        if (group.front() != a.parent) {
            const auto& curr_edge = intervals[group.front()];
            for (long long x = curr_edge.start_x; x <= a.start_x; ++x) {
                curr += (curr_edge.num_closest_children[0][x - curr_edge.start_x] +
                        curr_edge.num_closest_children[1][x - curr_edge.start_x] + 1) % MODULUS;
                curr_dist += (curr_edge.dist_closest_children[0][x - curr_edge.start_x] +
                             curr_edge.dist_closest_children[1][x - curr_edge.start_x] +
                             (curr_edge.num_closest_children[0][x - curr_edge.start_x] +
                              curr_edge.num_closest_children[1][x - curr_edge.start_x] + 1) * (a.start_x - x + 1)) % MODULUS;
            }
        }
        a.num_closest_children[i].front() += curr % MODULUS;
        a.dist_closest_children[i].front() += curr_dist % MODULUS;
        long long p = 0;
        long long x = a.start_x + 1;
        while (x < a.end_x - 1) {
            if (p == group.size()) {
                break;
            }
            const auto& curr_edge = intervals[group[p]];
            if (curr_edge.end_x == x || group[p] == a.parent) {
                ++p;
                continue;
            }
            if (curr_edge.start_x <= x) {
                a.num_closest_children[i][x - a.start_x] += (curr_edge.num_closest_children[0][x - curr_edge.start_x] +
                                                            curr_edge.num_closest_children[1][x - curr_edge.start_x] + 1) % MODULUS;
                a.dist_closest_children[i][x - a.start_x] += (curr_edge.dist_closest_children[0][x - curr_edge.start_x] +
                                                             curr_edge.dist_closest_children[1][x - curr_edge.start_x] +
                                                             curr_edge.num_closest_children[0][x - curr_edge.start_x] +
                                                             curr_edge.num_closest_children[1][x - curr_edge.start_x] + 1) % MODULUS;
            }
            ++x;
        }
        curr = 0;
        curr_dist = 0;
        if (group.back() != a.parent) {
            const auto& curr_edge = intervals[group.back()];
            for (long long x = max(a.start_x + 1, a.end_x - 1); x < curr_edge.end_x; ++x) {
                curr += (curr_edge.num_closest_children[0][x - curr_edge.start_x] +
                        curr_edge.num_closest_children[1][x - curr_edge.start_x] + 1) % MODULUS;
                curr_dist += (curr_edge.dist_closest_children[0][x - curr_edge.start_x] +
                             curr_edge.dist_closest_children[1][x - curr_edge.start_x] +
                             (curr_edge.num_closest_children[0][x - curr_edge.start_x] +
                              curr_edge.num_closest_children[1][x - curr_edge.start_x] + 1) * (1 + x - (a.end_x - 1))) % MODULUS;
            }
        }
        a.num_closest_children[i].back() += curr % MODULUS;
        a.dist_closest_children[i].back() += curr_dist % MODULUS;
    }

//    long long curr = 0;
//    for (long long i = 0; i != a.num_closest_children.size(); ++i) {
//        curr += a.num_closest_children[i];
//        a.run_closest_children[i] = curr;
//    }
//    cout << "ret " << i << "\n";
}

long long go(long long ival) {
    auto& a = intervals[ival];
    long long len = a.end_x - a.start_x;
    long long out = 0;
    for (long long i = 1; i <= len; ++i) {
        out += i * (len - i);
    }

    long long internal = out;

    vector<long long> run_num_sums[3] = {vector<long long>(len + 1), vector<long long>(len + 1), vector<long long>(len + 1)};
    vector<long long> run_prod_num_sums[3] = {vector<long long>(len + 1), vector<long long>(len + 1), vector<long long>(len + 1)};

    for (long long i = 0; i != 2; ++i) {
        long long curr = 0;
        long long curr_prod = 0;
        for (long long j = 0; j != len; ++j) {
            curr += a.num_closest_children[i][j];
            run_num_sums[i][j + 1] = curr;
            curr_prod += j * (a.num_closest_children[i][j]);
            run_prod_num_sums[i][j + 1] = curr_prod;
        }
    }

    long long curr = 0;
    long long curr_prod = 0;
    for (long long j = 0; j != len; ++j) {
        curr += 1;
        run_num_sums[2][j + 1] = curr;
        curr_prod += j;
        run_prod_num_sums[2][j + 1] = curr_prod;
    }

    // child -> child
    for (long long i = 0; i != 2; ++i) {
        const auto& group = (i == 0) ? a.l_edges : a.r_edges;
        for (auto v : group) {
            if (v == a.parent) {
                continue;
            }
            auto& curr_edge = intervals[v];
            for (long long x = max(curr_edge.start_x, a.start_x); x != min(curr_edge.end_x, a.end_x); ++x) {
//                cout << x << "\n";
                long long temp = 0;
                long long d = x - a.start_x;
                auto edge_start = max(0LL, curr_edge.start_x - a.start_x); // the actual point
                auto edge_end = min(len, curr_edge.end_x - a.start_x); // one-past
//                cout << "considering everything EXCEPT " << edge_start << " <= x < " << edge_end << "\n";
                temp += d * run_num_sums[i][edge_start];
                temp -= run_prod_num_sums[i][edge_start];
//                temp += run_prod_num_sums[i].back() - run_prod_num_sums[i][edge_end];
//                temp -= d * (run_num_sums[i].back() - run_num_sums[i][edge_end]);
//                cout << "temp_sameside = " << temp << " " << i << " " << v << " " << x << " " << d << "\n";

                temp += d * run_num_sums[1 - i][d + 1];
                temp -= run_prod_num_sums[1 - i][d + 1];
//                temp += run_prod_num_sums[1 - i].back() - run_prod_num_sums[1 - i][d + 1];
//                temp -= d * (run_num_sums[1 - i].back() - run_num_sums[1 - i][d + 1]);

                temp += d * run_num_sums[2][d + 1];
                temp -= run_prod_num_sums[2][d + 1];
                temp += run_prod_num_sums[2].back() - run_prod_num_sums[2][d + 1];
                temp -= d * (run_num_sums[2].back() - run_num_sums[2][d + 1]);
//                cout << "temp_all = " << temp << " " << i << " " << v << " " << x << " " << d << "\n";

                out += (temp * a.num_closest_children[i][d]) % MODULUS;
//                cout << "total internal = " << (temp * a.num_closest_children[i][d]) % MODULUS << "\n";
                // internal movement calculation completed

//                cout << "end sum = " << run_num_sums[i][edge_end] << "\n";
//                cout << "start sum = " << run_num_sums[i][edge_start] << "\n";
//                cout << "len = " << len << "\n";
//                cout << "opp side = " << run_num_sums[1 - i].back() << "\n";
//                cout << "same side = " << run_num_sums[i].back() << "\n";
                long long num = len + run_num_sums[1 - i].back() + run_num_sums[i].back() - run_num_sums[i][edge_end]
                + run_num_sums[i][edge_start];// - (min(len, curr_edge.end_x - a.start_x) - max(0, curr_edge.start_x - a.start_x - 1)) + 1;

//                cout << "num = " << num << "\n";
                out += (num * a.dist_closest_children[i][d]) % MODULUS;
//                cout << "total external = " << (num * a.dist_closest_children[i][d]) % MODULUS << "\n";
//                cout << "out is now = " << out << "\n";
            }
        }
    }
//    cout << ival << " " << internal << " + " << (out - internal) << " = " << out << "\n";
    return out % MODULUS;
}

int main() {
    long long N;
    cin >> N;
    set<pair<long long, long long>> points;
    for (long long i = 0; i != N; ++i) {
        long long x, y;
        cin >> x >> y;
        points.insert({y, x});
    }
    long long prev_x = -1;
    long long prev_y = -1;
    interval curr;
    curr.parent = -1;

    long long isFirst = true;
    for (auto p : points) {
        auto x = p.second;
        auto y = p.first;
        if (y != prev_y || x != prev_x + 1) {
            // end of prev interval
            if (!isFirst) {
                intervals.push_back(curr);
            }
            curr.start_x = x;
            curr.end_x = x;
            curr.y = y;
        }
        ++curr.end_x;
        prev_x = x;
        prev_y = y;
        isFirst = false;
    }
    intervals.push_back(curr);

    long long curr_i = 0;
    long long target_i = 0;
    while (curr_i != intervals.size() && target_i != intervals.size()) {
        auto& curr_interval = intervals[curr_i];
        auto& target_interval = intervals[target_i];
        if (target_interval.y <= curr_interval.y || (curr_interval.y + 1 == target_interval.y && curr_interval.start_x >= target_interval.end_x)) {
            ++target_i;
        } else if (target_interval.y == curr_interval.y + 1 &&
                   curr_interval.start_x < target_interval.end_x &&
                   target_interval.start_x <= curr_interval.end_x) {
            curr_interval.edges.push_back(target_i);
            curr_interval.r_edges.push_back(target_i);
            target_interval.edges.push_back(curr_i);
            target_interval.l_edges.push_back(curr_i);
            if (curr_interval.end_x < target_interval.end_x) {
                ++curr_i;
            } else {
                ++target_i;
            }
        } else {
            ++curr_i;
        }
    }

    vector<long long> todo = {0};
    while (todo.size() > 0) {
        auto a = todo.back();
        todo.pop_back();
        for (auto b : intervals[a].edges) {
            if (intervals[a].parent == b) {
                continue;
            }
            intervals[b].parent = a;
            todo.push_back(b);
        }
    }

    dfs_subtree_size(0);
    dfs_closest_children(0);
//
//    for (auto i : intervals) {
//        cout << "{" << i.start_x << ", " << i.end_x << ", " << i.y << ", " << i.subtree_size << " { ";
//        for (long long j = 0; j != i.num_closest_children[0].size(); ++j) {
//            cout << i.num_closest_children[1][j] << ": " << i.dist_closest_children[1][j] << ", ";
//        }
//        cout << "} }\n";
//    }

    long long out = 0;
    for (long long i = 0; i != intervals.size(); ++i) {
        out += go(i);
    }
    cout << (out + MODULUS) % MODULUS;

}
