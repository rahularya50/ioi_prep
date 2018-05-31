#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> paper(1e6);

    map<int, int> vals;
    map<int, int> subseqs; // start -> strict end

    map<int, set<int>> occurrences;

    for (int i = 0; i != N; ++i) {
        string cmd;
        cin >> cmd;
        if (cmd == "write") {
            int x, y;
            cin >> x >> y;
            occurrences[x].insert(y);
            vals[y] = x;
            auto iter = subseqs.upper_bound(y);
            if (iter == subseqs.begin() || prev(iter)->second < y) {
                // not in a subseq
                auto next_subseq = iter;
                if (next_subseq != subseqs.end()) {
                    if (x <= vals[next_subseq->first]) {
                        auto endpos = next_subseq->second;
                        subseqs.erase(next_subseq);
                        subseqs[y] = endpos;
                    } else {
                        subseqs[y] = y;
                    }
                }
                auto prev_subseq = subseqs.find(y);
                if (prev_subseq == subseqs.begin()) {
                    continue;
                }
                advance(prev_subseq, -1);
                if (vals[prev_subseq->second] <= y) {
                    prev_subseq->second = subseqs[y];
                    subseqs.erase(y);
                }

            } else {
                auto my_subseq = prev(iter);

            }

        } else {
            int x, l, r;
            cin >> x >> l >> r;

            if (vals.lower_bound(l) == vals.end() || vals.lower_bound(l)->first > r) {
                cout << "No\n";
                continue;
            }

            auto iter = subseqs.upper_bound(l);
            if (iter == subseqs.begin() || prev(iter)->second < r) {
                cout << "No sort, no search\n";
                continue;
            }

            if (occurrences.find(x) == occurrences.end()) {
                cout << "No\n";
                continue;
            }

            const auto& s = occurrences[x];
            auto lb = s.lower_bound(l);
            if (lb == s.end() || *lb > r ) {
                cout << "No\n";
                continue;
            }

            cout << "Yes\n";
        }
    }
}
