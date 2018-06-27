#include <bits/stdc++.h>

using namespace std;

struct suffix {
    int pos;
    int order;
    int new_order;
};

bool cmp(suffix x, suffix y) {
    if (x.order == y.order) {
        return x.new_order < y.new_order;
    }
    return x.order < y.order;
}

string S;

const int SIZE = 1e6 + 3;
suffix suffixes[SIZE];
int new_orders[SIZE];
int lookups[SIZE];
int lcp[SIZE];
int min_lcp[SIZE];
long long diffs[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int t = 0; t != T; ++t) {
        cin >> S;
        int L = S.size();
        for (int i = 0; i != L; ++i) {
            suffixes[i] = {i, S[i] - 'a', -1};
        }
        suffixes[L] = {L, -1, -1};
        sort(begin(suffixes), begin(suffixes) + L + 1, cmp);
        for (int len = 1; len <= 2 * L; len *= 2) {
            int curr = 0;
            for (int i = 1; i != L + 1; ++i) {
                if (cmp(suffixes[i - 1], suffixes[i])) {
                    ++curr;
                }
                new_orders[i] = curr;
            }
            for (int i = 0; i != L + 1; ++i) {
                suffixes[i].order = new_orders[i];
                lookups[suffixes[i].pos] = i;
            }
            for (int i = 0; i != L + 1; ++i) {
                suffixes[i].new_order = suffixes[lookups[min(suffixes[i].pos + len, L)]].order;
            }
            sort(begin(suffixes), begin(suffixes) + L + 1, cmp);
        }

        int val = 0;
        for (int i = 0; i != L + 1; ++i) {
            int pos = lookups[i];
            while (val < (L - suffixes[pos - 1].pos) && val < (L - suffixes[pos].pos)
                   && S[suffixes[pos - 1].pos + val] == S[suffixes[pos].pos + val]) { ++val; }
            lcp[pos] = val;
            --val;
            val = max(val, 0);
        }

        int curr = L;
        for (int i = lookups[0] + 1; i != L + 1; ++i) {
            curr = min(curr, lcp[i]);
            min_lcp[i] = curr;
        }
        curr = L;
        for (int i = lookups[0] - 1; i != 0; --i) {
            curr = min(curr, lcp[i + 1]);
            min_lcp[i] = curr;
        }

//        for (int i = 0; i <= L; ++i) {
//            cout << suffixes[i].pos << ", " << lcp[i] << ", " << min_lcp[i] << ": ";
//            for (int j = suffixes[i].pos; j != S.size(); ++j) {
//                cout << S[j];
//            }
//            cout << "\n";
//        }

        for (int i = 0; i != L + 1; ++i) {
            diffs[i] = 0;
        }

        for (int i = 0; i != L + 1; ++i) {
            int curr_start = suffixes[i].pos;
            int max_len = min_lcp[i];
            max_len = min(max_len, curr_start);
            int curr_end = curr_start + max_len;
            ++diffs[curr_start];
            --diffs[curr_end];
        }

        long long out = 1;
        long long c = 0;
        for (int i = 0; i != L; ++i) {
            c += diffs[i];
            out *= (c + 1LL);
            out %= 1000000007;
        }
        cout << out << "\n";
    }
}
