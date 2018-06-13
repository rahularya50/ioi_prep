#include <bits/stdc++.h>

using namespace std;

const long long INVALID = -2;
const long long UNDEF = -1;

const long long MODULUS = 1000000009;

long long T, N;

long long getOffset(const vector<long long>& seq) {
    long long offset = UNDEF;
    set<long long> vals;
    for (long long i = 0; i != N; ++i) {
        long long x = seq[i];
        if (x <= N) {
            if (offset == UNDEF) {
                offset = (x - i + N) % N;
            } else if ((x - i + N) % N != offset) {
                return INVALID;
            }
        } else {
            if (vals.find(x) != vals.end()) {
                return INVALID;
            }
            vals.insert(x);
        }
    }
    return offset;
}

long long power(long long a, long long x) {
//    cout << a << "^" << x << "=";
    long long out = 1;
    long long curr = a;
    if (x != 0) {
        for (long long i = 0; i <= static_cast<long long>(log2(x)); ++i) {
            if ((1LL << i) & x) {
                out *= curr;
                out %= MODULUS;
            }
            curr *= curr;
            curr %= MODULUS;
        }
    }
//    cout << out << "\n";
    return out;
}

int main() {
//    ios::sync_with_stdio(false);
//    cin.tie(0);
    cin >> T >> N;
    vector<long long> seq(N);
    for (long long i = 0; i != N; ++i) {
        long long x;
        cin >> x;
        seq[i] = x;
    }
    if (T <= 3) {
        cout << (getOffset(seq) != INVALID ? 1 : 0);
    } else if (T <= 6) {
        long long offset = getOffset(seq);
        vector<pair<long long, long long>> mapping(N);
        for (long long i = 0; i != N; ++i) {
            mapping[i] = {(i + offset + N - 1) % N + 1, seq[i]};
        }
        sort(mapping.begin(), mapping.end(), [](pair<long long, long long> a, pair<long long, long long> b){ return a.second < b.second; });
        vector<long long> out;
        long long curr = N;
        for (long long i = 0; i != N; ++i) {
            while (curr < mapping[i].second) {
                out.push_back(mapping[i].first);
                ++curr;
                mapping[i].first = curr;
            }
        }
        cout << out.size() << "\n";
        for (auto x : out) {
            cout << x << " ";
        }
    } else {
        long long out = 1;
        long long offset = getOffset(seq);
        if (offset == INVALID) {
            cout << 0;
            return 0;
        }
        vector<pair<long long, long long>> mapping(N);
        for (long long i = 0; i != N; ++i) {
            mapping[i] = {(i + offset + N - 1) % N + 1, seq[i]};
        }
        sort(mapping.begin(), mapping.end(), [](pair<long long, long long> a, pair<long long, long long> b){ return a.second < b.second; });
        long long curr = N;
        for (long long i = 0; i != N; ++i) {
            auto delta = mapping[i].second - curr;
            if (delta <= 0) {
                continue;
            }
            out *= power(N - i, delta - 1);
            out %= MODULUS;
            curr = mapping[i].second;
        }
        if (offset == UNDEF) {
            out *= N;
            out %= MODULUS;
        }
        cout << out << "\n";
    }
}
