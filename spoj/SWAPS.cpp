#include <bits/stdc++.h>

using namespace std;

long long MAX_VAL = 50000;

long long smaller(long long x, long long val, long long i, long long row, const vector<vector<vector<long long>>>& main_tree) {
    long long step_size = 1 << (main_tree.size() - row - 1);
    long long start_pos = step_size * i;
    long long end_pos = step_size * (i + 1);
    long long mid_pos = (start_pos + end_pos) / 2;

//    cout << "Searching interval from " << start_pos << " to " << end_pos << " for x = " << x << ", val = " << val << "\n";

    if (end_pos <= x) {
        if (main_tree[row][i].front() > val) {
//            cout << "ret 0\n";
            return 0;
        } else if (main_tree[row][i].back() < val) {
//            cout << "ret " << main_tree[row][i].size() << "\n";
            return main_tree[row][i].size();
        } else {
            auto iter = lower_bound(main_tree[row][i].begin(), main_tree[row][i].end(), val);
//            cout << "ret " << distance(main_tree[row][i].begin(), iter) << "\n";
            return distance(main_tree[row][i].begin(), iter);
        }
    }

    if (step_size == 1) {
        return 0;
    }

    long long out = smaller(x, val, 2 * i, row + 1, main_tree);
    if (x >= mid_pos)  {
        out += smaller(x, val, 2 * i + 1, row + 1, main_tree);
    }
    return out;
}

long long count_invs(vector<long long>& A) {
    if (A.size() <= 1) {
        return 0;
    }
    vector<long long> B;
    vector<long long> C;
    B.reserve(A.size() / 2);
    C.reserve(A.size() / 2);
    for (long long i = 0; i != A.size() / 2; ++i) {
        B.push_back(A[i]);
    }
    for (long long i = A.size() / 2; i != A.size(); ++i) {
        C.push_back(A[i]);
    }
    long long inv_count = 0;
    inv_count += count_invs(B);
    inv_count += count_invs(C);
    long long p1 = 0;
    long long p2 = 0;
    while (p1 != B.size() || p2 != C.size()) {
        if (p1 == B.size() || (p2 != C.size() && C[p2] < B[p1])) {
            A[p1 + p2] = C[p2];
            ++p2;
        } else {
            A[p1 + p2] = B[p1];
            ++p1;
            inv_count += p2;
        }
    }
    return inv_count;
}

int main() {
//    ios::sync_with_stdio(false);
    long long N;
    cin >> N;
    vector<long long> A;
    A.reserve(N);
    for (long long i = 0; i != N; ++i) {
        long long x;
        cin >> x;
        A.push_back(x);
    }

    set<long long> changing;
    vector<pair<long long, long long>> changes;
    long long M;
    cin >> M;
    for (long long i = 0; i != M; ++i) {
        long long x, y;
        cin >> x >> y;
        --x;
        changes.push_back({x, y});
        changing.insert(x);
//        cout << "ignoring index = " << x << "\n";
    }

    vector<pair<pair<long long, long long>, vector<pair<long long, long long>>>> buckets = {{{-1, 0}, {}}};
    buckets.reserve(static_cast<long long>(sqrt(changing.size() - 1)) + 1);
    long long cnt = 0;
    long long i = 0;
    for (auto x : changing) {
        buckets.back().second.push_back({x, A[x]});
        if (buckets.back().first.first == -1) {
            buckets.back().first.first = x;
        }
        ++cnt;
        if (cnt * cnt >= changing.size()) {
            cnt = 0;
            i += 1;
            buckets.back().first.second = x;
            buckets.push_back({{-1, 0}, {}});
        }
    }
    buckets.back().first.second = *(changing.rbegin());

    for (long long i = 0; i != buckets.size(); ++i) {
//        cout << "Bucket #" << i << " of size=" << buckets[i].second.size() << "\n";
        sort(buckets[i].second.begin(), buckets[i].second.end(), [](pair<long long, long long> x, pair<long long, long long> y){return x.second < y.second; });
    }

    long long rows = log2(N - 1) + 2;
    vector<vector<vector<long long>>> tree(rows);
    tree.back().reserve(1 << (rows - 1));
    for (long long i = 0; i != (1 << (rows - 1)); ++i) {
        if (i >= N || changing.find(i) != changing.end()) {
            tree.back().push_back({0});
        } else {
            tree.back().push_back({A[i]});
        }
    }

    for (long long row = rows - 2; row >= 0; --row) {
        tree[row].reserve(1 << row);
        for (long long i = 0; i != (1 << row); ++i) {
            tree[row].push_back({});
            tree[row].back().reserve(1 << (rows - row - 1));
            long long p1 = 0;
            long long p2 = 0;
            while (p1 != tree[row + 1][2 * i].size() || p2 != tree[row + 1][2 * i + 1].size() ) {
                if (p1 == tree[row + 1][2 * i].size() ||
                    (p2 != tree[row + 1][2 * i + 1].size() && tree[row + 1][2 * i][p1] > tree[row + 1][2 * i + 1][p2])) {
                    tree[row].back().push_back(tree[row + 1][2 * i + 1][p2]);
                    ++p2;
                } else {
                    tree[row].back().push_back(tree[row + 1][2 * i][p1]);
                    ++p1;
                }
            }
        }
    }

    auto B = A;
    long long inv_count = count_invs(B);

//
//    for (long long row = 0; row != rows; ++row) {
//        for (long long i = 0; i != (1 << row); ++i) {
//            cout << "( ";
//            for (auto x : tree[row][i]) {
//                cout << x << ", ";
//            }
//            cout << "), ";
//        }
//        cout << "\n";
//    }

//    cout << "Inv: " << inv_count << "\n";

    long long stable = N - changing.size();

    for (auto change : changes) {
        long long pos = change.first;
        long long new_val = change.second;
        long long old_val = A[pos];
        A[pos] = new_val;

        long long out = inv_count;

        long long old_right_inv = smaller(N, old_val, 0, 0, tree) - smaller(pos, old_val, 0, 0, tree) - 1;
        long long old_left_inv = pos - smaller(pos, old_val + 1, 0, 0, tree);

//        cout << "old_smaller = " << old_smaller << "\n";
//        cout << "old_left_smaller = " << old_left_smaller << "\n";
//
//        cout << "old_left_inv = " << old_left_inv << "\n";
//        cout << "old_right_inv = " << old_right_inv << "\n";

        long long new_right_inv = smaller(N, new_val, 0, 0, tree) - smaller(pos, new_val, 0, 0, tree) - 1;
        long long new_left_inv = pos - smaller(pos, new_val + 1, 0, 0, tree);

//        cout << "new_left_inv = " << new_left_inv << "\n";
//        cout << "new_right_inv = " << new_right_inv << "\n";

        out += new_left_inv + new_right_inv - old_left_inv - old_right_inv;

//        cout << "static delta: " << new_left_inv + new_right_inv - old_left_inv - old_right_inv << "\n";
//        cout << "static inverses complete\n";

        for (auto& bucket : buckets) {
//            cout << "next bucket between x = " << bucket.first.first << " and x = " << bucket.first.second << "\n";
            if (bucket.first.second < pos) {
//                cout << "left bucket\n";
                auto iter_old = upper_bound(bucket.second.begin(), bucket.second.end(), old_val, [](long long y, pair<long long, long long> x){return y < x.second;});
                auto iter_new = upper_bound(bucket.second.begin(), bucket.second.end(), new_val, [](long long y, pair<long long, long long> x){return y < x.second;});
//                cout << "delta = " << -distance(iter_old, iter_new) << "\n";
                out -= distance(iter_old, iter_new);
            } else if (bucket.first.first > pos) {
//                cout << "right bucket\n";
                auto iter_old = lower_bound(bucket.second.begin(), bucket.second.end(), old_val, [](pair<long long, long long> x, long long y){return x.second < y;});
                auto iter_new = lower_bound(bucket.second.begin(), bucket.second.end(), new_val, [](pair<long long, long long> x, long long y){return x.second < y;});

//                cout << "delta = " << distance(iter_old, iter_new) << "\n";
                out += distance(iter_old, iter_new);
            } else {
//                cout << "curr bucket\n";
                long long old_inv = 0;
                long long new_inv = 0;
                for (auto& v : bucket.second) {
                    if (v.first < pos && v.second > old_val) {
                        ++old_inv;
                    }
                    if (v.first > pos && v.second < old_val) {
                        ++old_inv;
                    }
                    if (v.first < pos && v.second > new_val) {
                        ++new_inv;
                    }
                    if (v.first > pos && v.second < new_val) {
                        ++new_inv;
                    }
                    if (v.first == pos) {
                        v.second = new_val;
                    }
                }
//                cout << "old = " << old_inv << "\n";
//                cout << "new = " << new_inv << "\n";
                out += new_inv - old_inv;
//                cout << "delta = " << new_inv - old_inv << "\n";
                sort(bucket.second.begin(), bucket.second.end(), [](pair<long long, long long> x, pair<long long, long long> y){return x.second < y.second; });
            }
        }

        cout << out << "\n";
        inv_count = out;
    }


}
