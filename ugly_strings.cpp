#include <bits/stdc++.h>

using namespace std;

string S;

struct suffix {
    long long pos;
    long long order;
    long long new_order;
};

bool cmp(suffix a, suffix b) {
    if (a.order == b.order) {
        return a.new_order < b.new_order;
    }
    return a.order < b.order;
}

bool cmp2(suffix a, const string& s) {
    for (long long i = 0; i != s.size(); ++i) {
        if (a.pos + i == S.size()) {
            return true;
        }
        if (S[a.pos + i] != s[i]) {
            return S[a.pos + i] < s[i];
        }
    }
    return false;
}

int main() {
    ifstream cin("ugly.in");
    ofstream cout("ugly.out");

    cin.tie(0);
    ios::sync_with_stdio(false);

    long long L;
    cin >> L;

    cin >> S;
//    L = S.size();

    long long M;
    cin >> M;

    map<long long, long long> forbidden_lookup;
    vector<string> forbiddens;
    long long pos = 0;
    for (long long i = 0; i != M; ++i) {
        string x;
        cin >> x;
        forbidden_lookup[i] = pos;
        pos += x.size();
        forbiddens.push_back(move(x));
    }

    vector<suffix> suffixes;
    for (long long i = 0; i != L; ++i) {
        suffixes.push_back({i, S[i], ((i == L) - 1 ? S[i + 1] : -1)});
    }
    suffixes.push_back({L, -1, -1});

    sort(suffixes.begin(), suffixes.end(), cmp);
    vector<long long> new_orders(L + 1);
    vector<long long> lookups(L + 1);
    for (long long l = 2; l < 2 * L; l *= 2) {
        long long pos = 0;
        new_orders[0] = 0;
        for (long long i = 0; i != L; ++i) {
            if (cmp(suffixes[i], suffixes[i + 1])) {
                ++pos;
            }
            new_orders[i + 1] = pos;
        }

        for (long long i = 0; i <= L; ++i) {
            suffixes[i].order = new_orders[i];
            lookups[suffixes[i].pos] = i;
        }

        for (long long i = 0; i <= L; ++i) {
            suffixes[i].new_order = suffixes[lookups[min(L, suffixes[i].pos + l)]].order;
        }

        sort(suffixes.begin(), suffixes.end(), cmp);
    }

    vector<long long> lcp(L + 1);
    long long curr = 0;

    for (long long i = 0; i != L; ++i) {
        auto a = suffixes[lookups[i]];
        auto b = suffixes[lookups[i] - 1];

        while (curr < L - max(a.pos, b.pos)) {
            if (S[a.pos + curr] == S[b.pos + curr]) {
                ++curr;
            } else {
                break;
            }
        }

        lcp[lookups[i]] = curr;
        curr = max(0LL, curr - 1);
    }
//
//    for (auto suffix : suffixes) {
//        cout << suffix.pos << " " << lcp[lookups[suffix.pos]] << ": ";
//        for (long long i = suffix.pos; i != L; ++i) {
//            cout << S[i];
//        }
//        cout << "\n";
//    }

    vector<long long> start_pos(L + 1, -1);
    vector<long long> end_pos(L + 1, -1);

    for (auto& f : forbiddens) {
        long long pos = distance(suffixes.begin(), lower_bound(suffixes.begin(), suffixes.end(), f, cmp2));
//        cout << pos << "\n";
        bool ok = true;
        for (long long i = 0; i != f.size(); ++i) {
            if (suffixes[pos].pos + i == L) {
                ok = false;
                break;
            }
            if (S[suffixes[pos].pos + i] != f[i]) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            continue;
        }
        do {
            start_pos[suffixes[pos].pos] = suffixes[pos].pos + f.size();
            end_pos[suffixes[pos].pos + f.size()] = max(end_pos[suffixes[pos].pos + f.size()], suffixes[pos].pos);
            ++pos;
        } while (pos <= L && lcp[pos] >= f.size());
    }
//
//    for (auto x : start_pos) {
//        cout << x << " ";
//    }
//
//    cout << "\n";
//
//    for (auto x : end_pos) {
//        cout << x << " ";
//    }
//
//    cout << "\n";

    long long out = 0;
    long long lpos = 0;
    long long rpos = 0;
    for (; rpos < L; ++rpos) {
        if (start_pos[rpos] != -1) {
            // nothing???
        }
        if (end_pos[rpos] != -1) {
//            cout << lpos << " -> " << rpos << "\n";
            out += (rpos - lpos) * (rpos - lpos - 1) / 2;
//            cout << "delta = " << (rpos - lpos) * (rpos - lpos - 1) / 2 << "\n";
            lpos = max(lpos, end_pos[rpos] + 1);
            long long ldelta = rpos - lpos;
            out -= ldelta * (ldelta - 1) / 2;
        }
    }

    if (end_pos[rpos] != -1 && (end_pos[rpos] + 1) > lpos) {
//            cout << lpos << " -> " << rpos << "\n";
            out += (rpos - lpos) * (rpos - lpos - 1) / 2;
//            cout << "delta = " << (rpos - lpos) * (rpos - lpos - 1) / 2 << "\n";
            lpos = max(lpos, end_pos[rpos] + 1);
            long long ldelta = rpos - lpos;
            out -= ldelta * (ldelta - 1) / 2;
    }
//
//    cout << lpos << " -> " << rpos << "\n";
    out += (rpos - lpos) * (rpos - lpos + 1) / 2;
//    cout << "delta = " << (rpos - lpos) * (rpos - lpos + 1) / 2 << "\n";

    cout << out << "\n";
}
