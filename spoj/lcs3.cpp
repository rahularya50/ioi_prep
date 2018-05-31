#include <bits/stdc++.h>

using namespace std;

struct suffix {
    int pos;
    int order;
    int new_order;
};

bool cmp(suffix a, suffix b) {
    if (a.order == b.order) {
        return a.new_order < b.new_order;
    }
    return a.order < b.order;
}

bool cmp2(suffix a, int x, int y, const vector<int>& q, const vector<int>& A) {
    for (int i = x; i != y; ++i) {
        if (a.pos + i == A.size()) {
            return true;
        }
        if (A[a.pos + i] != q[i]) {
            return A[a.pos + i] < q[i];
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

    vector<int> A;
    A.reserve(N);

    for (int i = 0; i != N; ++i) {
        int x;
        cin >> x;
        A.push_back(x);
    }

    vector<suffix> suffixes;
    for (int i = 0; i != N; ++i) {
        suffixes.push_back({i, A[i], 0});
    }
    suffixes.push_back({N, -1, 0});
    sort(suffixes.begin(), suffixes.end(), cmp);

    vector<int> lookup(N + 1);
    vector<int> new_order(N + 1);

    for (int len = 1; len < 2 * N; len *= 2) {
        int curr = 0;

        suffixes[0].order = curr;
        for (int j = 1; j <= N; ++j) {
            if (cmp(suffixes[j - 1], suffixes[j])) {
                ++curr;
            }
            new_order[j] = curr;
        }

        for (int j = 0; j <= N; ++j) {
            suffixes[j].order = new_order[j];
            lookup[suffixes[j].pos] = j;
        }

        for (int j = 0; j <= N; ++j) {
            suffixes[j].new_order = suffixes[lookup[min(suffixes[j].pos + len, N)]].order;
        }

        sort(suffixes.begin(), suffixes.end(), cmp);
    }

    for (auto& x : suffixes) {
        cout << x.pos << ": ";
        for (int i = x.pos; i != N; ++i) {
            cout << A[i] << " ";
        }
        cout << "\n";
    }


    int Q;
    cin >> Q;
    vector<int> B;
    B.reserve(6);
    for (int q = 0; q != Q; ++q) {
        int M;
        cin >> M;
        for (int i = 0; i != M; ++i) {
            int x;
            cin >> x;
            B[i] = x;
        }

        int best = 0;
        suffix best_out;

        for (int x = 0; x != M; ++x) {
            auto match = *lower_bound(suffixes.begin(), suffixes.end(), B, [&](suffix a, const vector<int>& B){ return cmp2(a, x, M, B, A); });
            cout << "match found at pos = " << match.pos << "\n";
            int len = 0;
            for (int i = x; i != M; ++i) {
                if (match.pos + i == A.size()) {
                    break;
                }
                if (A[match.pos + i] != B[i]) {
                    break;
                }
                ++len;
            }
            if (len >= best) {
                best = len;
                best_out = match;
            }
        }

        cout << best << "\n";
        for (int i = 0; i != best; ++i) {
            cout << A[best_out.pos + i] << " ";
        }
        cout << "\n";


    }

}
