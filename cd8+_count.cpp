#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;

    vector<int> run_diffs = {0};
    run_diffs.reserve(N + 1);

    map<int, int> cnt;

    vector<int> A;
    A.reserve(N);
    vector<int> B;
    B.reserve(N);

    for (int i = 0; i != N; ++i) {
        int x;
        cin >> x;
        A.push_back(x);
    }

    for (int i = 0; i != N; ++i) {
        int x;
        cin >> x;
        B.push_back(x);
    }

    vector<int> sum_squares = {0, 1};
    cnt[0] = 1;
    sum_squares.reserve(N + 2);

    int curr = 0;
    int curr_square_sum = 1;

    for (int i = 0; i != N; ++i) {
        curr += A[i] - B[i];
        run_diffs.push_back(curr);
        curr_square_sum += 2 * cnt[curr] + 1;
        ++cnt[curr];
        sum_squares.push_back(curr_square_sum);
    }
//
//    cout << "[ ";
//    for (auto x : sum_squares) {
//        cout << x << ", ";
//    }
//    cout << "]\n";

    int Q;
    cin >> Q;

    vector<pair<pair<int, int>, pair<int, int>>> pairs; // {{bucket, R}, {L, i}}
    pairs.reserve(Q);

    for (int i = 0; i != Q; ++i) {
        int L, R;
        cin >> L >> R;
        --L;
        pairs.push_back({{static_cast<int>(sqrt(L)), R}, {L, i}});
//        auto prod = (L + R) * (L + R) - sum_squares[L] - sum_squares[R];
//        auto sR = sum_squares[R + 1];
//        auto sL = sum_squares[L];
//        cout << sR << " " << sL << "\n";
//        cout << sR + sL + (L - R - 1) + L + R - 2 * (1 + L) * (1 + R) << "\n";
    }

    sort(pairs.begin(), pairs.end());

    vector<int> dot_prods(Q);

    int lpos = 0;
    int rpos = 0;
    int curr_prod = 0;

    map<int, int> curr_left;
    map<int, int> curr_right;

    for (auto p : pairs) {
        int target_l = p.second.first;
        int target_r = p.first.second + 1;

        while (lpos != target_l || rpos != target_r) {
            if (rpos < target_r) {
                ++rpos;
                ++curr_right[run_diffs[rpos - 1]];
                curr_prod += curr_left[run_diffs[rpos - 1]];
            } else if (lpos > target_l) {
                --curr_left[run_diffs[lpos - 1]];
                curr_prod -= curr_right[run_diffs[lpos - 1]];
                --lpos;
            } else if (rpos > target_r) {
                --curr_right[run_diffs[rpos - 1]];
                curr_prod -= curr_left[run_diffs[rpos - 1]];
                --rpos;
            } else {
                ++lpos;
                ++curr_left[run_diffs[lpos - 1]];
                curr_prod += curr_right[run_diffs[lpos - 1]];
            }
//            cout << lpos << " " << rpos << " " << curr_prod << "\n";
        }

//        cout << target_l << " " << target_r << " " << curr_prod << "\n";

        dot_prods[p.second.second] = curr_prod;
    }

    vector<int> out(Q);

    for (int i = 0; i != Q; ++i) {
        int L = pairs[i].second.first;
        int R = pairs[i].first.second;
        int j = pairs[i].second.second;

        auto sR = sum_squares[R + 1];
        auto sL = sum_squares[L];

//        cout << sR << " " << sL << "\n";

        out[j] =  (sR + sL + (L - R - 1) - 2 * dot_prods[j]) / 2;
    }

    for (auto x : out) {
        cout << x << "\n";
    }
}
