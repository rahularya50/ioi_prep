#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> S(N);
    for (auto& x : S) {
        cin >> x;
    }
    int M;
    cin >> M;
    vector<pair<int, int>> swaps(M);
    for (auto& x : swaps) {
        cin >> x.first >> x.second;
    }
    int low = -1;
    int high = M + 1;
    while (high - low > 1) {
//        cout << low << " < moves <= " << high << "\n";
        int mid = (low + high) / 2;
        vector<int> mapping(N);
        for (int i = 0; i != N; ++i) {
            mapping[i] = i;
        }
        for (int pos = mid - 1; pos >= 0; --pos) {
            swap(mapping[swaps[pos].first], mapping[swaps[pos].second]);
        }
        vector<int> dests(N); // dests[i] = target position of element of value i
        for (int i = 0; i != N; ++i) {
            dests[mapping[i]] = i;
        }
//        for (auto x : dests) {
//            cout << x << " ";
//        }
//        cout << "\n";
        int cnt = 0;
        vector<int> start = S;
        vector<int> pos(N);
        for (int i = 0; i != N; ++i) {
            pos[start[i]] = i;
        }
        for (int i = 0; i != N; ++i) {
            if (pos[i] == dests[i]) {
                continue;
            }
            int val = i;
            int origin = pos[i];
            int dest = dests[i];
            int destVal = start[dests[i]];
            start[dest] = val;
            start[origin] = destVal;
            pos[val] = dest;
            pos[destVal] = origin;
            ++cnt;
//            cout << "Swap start[" << origin << "] = " << val << " to S[" << dest << "] = " << destVal << "\n";
        }
        if (cnt > mid) {
            low = mid;
        } else {
            high = mid;
        }
    }
    cout << high << "\n";

    vector<pair<int, int>> finalSwaps;
    vector<int> mapping(N);
    for (int i = 0; i != N; ++i) {
        mapping[i] = i;
    }
    for (int pos = high - 1; pos >= 0; --pos) {
        swap(mapping[swaps[pos].first], mapping[swaps[pos].second]);
    }
    vector<int> dests(N); // dests[i] = target position of element of value i
    for (int i = 0; i != N; ++i) {
        dests[mapping[i]] = i;
    }
//        for (auto x : dests) {
//            cout << x << " ";
//        }
//        cout << "\n";
    vector<int> start = S;
    vector<int> pos(N);
    for (int i = 0; i != N; ++i) {
        pos[start[i]] = i;
    }
    for (int i = 0; i != N; ++i) {
        if (pos[i] == dests[i]) {
            continue;
        }
        int val = i;
        int origin = pos[i];
        int dest = dests[i];
        int destVal = start[dests[i]];
        start[dest] = val;
        start[origin] = destVal;
        pos[val] = dest;
        pos[destVal] = origin;
        finalSwaps.push_back({val, destVal});
//        cout << "Swap start[" << origin << "] = " << val << " with S[" << dest << "] = " << destVal << "\n";
    }

    for (int i = 0; i != N; ++i) {
        pos[S[i]] = i;
    }
    for (int i = 0; i != high; ++i) {
//        for (auto x : pos) {
//            cout << x << ", ";
//        }
//        cout << "\n";
        swap(pos[S[swaps[i].first]], pos[S[swaps[i].second]]);
        swap(S[swaps[i].first], S[swaps[i].second]);

        if (finalSwaps.size() <= i) {
            cout << 0 << " " << 0 << "\n";
            break;
        }
        cout << pos[finalSwaps[i].first] << " " << pos[finalSwaps[i].second] << "\n";
        swap(S[pos[finalSwaps[i].first]], S[pos[finalSwaps[i].second]]);
        swap(pos[finalSwaps[i].first], pos[finalSwaps[i].second]);
    }
}
