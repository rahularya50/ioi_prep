#include <bits/stdc++.h>

using namespace std;

const int BLOCK_SIZE = 1;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long N, Q;
    cin >> N >> Q;
    vector<vector<map<pair<long long, long long>, long long>>> lookups;
    map<pair<long long, long long>, long long> specials;
    vector<map<pair<long long, long long>, long long>> x_specials;
    vector<map<pair<long long, long long>, long long>> y_specials;
    for (long long i = 0; i != N; ++i) {
        long long x, y, v;
        cin >> x >> y >> v;
        auto lx = static_cast<long long>(log2(x));
        auto ly = static_cast<long long>(log2(y));
        auto a = 1LL << lx;
        auto b = 1LL << ly;
        int target_lx = ((lx + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE;
        int target_ly = ((ly + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE;
        while (lookups.size() <= target_lx / BLOCK_SIZE) {
            lookups.push_back({});
        }
        while (lookups[target_lx / BLOCK_SIZE].size() <= target_ly / BLOCK_SIZE) {
            lookups[target_lx / BLOCK_SIZE].push_back({});
        }

//        cout << lx << " -> " << target_lx << ", " << ly << " -> " << target_ly << "\n";

        for (int lx_delta = 0; lx_delta != 1 << (target_lx - lx); ++lx_delta) {
            for (int ly_delta = 0; ly_delta != 1 << (target_ly - ly); ++ly_delta) {
//                cout << lx_delta << " " << ly_delta << "\n";
                lookups[target_lx / BLOCK_SIZE][target_ly / BLOCK_SIZE][{x % a + lx_delta * a, y % b + ly_delta * b}] += v;
            }
        }
//        lookups[lx][ly][{x % a, y % b}] += v;


        specials[{x % a, y % b}] += v;
        while (x_specials.size() <= target_lx / BLOCK_SIZE) {
            x_specials.push_back({});
        }
        for (int lx_delta = 0; lx_delta != 1 << (target_lx - lx); ++lx_delta) {
            x_specials[target_lx / BLOCK_SIZE][{x % a + lx_delta * a, y % b}] -= v;
        }
        while (y_specials.size() <= target_ly / BLOCK_SIZE) {
            y_specials.push_back({});
        }
        for (int ly_delta = 0; ly_delta != 1 << (target_ly - ly); ++ly_delta) {
            y_specials[target_ly / BLOCK_SIZE][{x % a, y % b + ly_delta * b}] -= v;
        }

//        cout << "deducting " << v << " from (" << (x % a) << ", " << y << ") \n";
    }

    for (long long i = 0; i != Q; ++i) {
        long long r, c;
        cin >> r >> c;
        long long out = 0;
        for (long long i = 0; i < lookups.size(); ++i) {
            for (long long j = 0; j < lookups[i].size(); ++j) {
                auto iter = lookups[i][j].find({r % (1LL << (i * BLOCK_SIZE)), c % (1LL << (j * BLOCK_SIZE))});
                if (iter != lookups[i][j].end()) {
                    out += iter->second;
                }
            }
        }
        auto iter = specials.find({r, c});
        if (iter != specials.end()) {
            out += iter->second;
        }
        for (long long i = 0; i != x_specials.size(); ++i) {
            auto iter = x_specials[i].find({r % (1LL << (i * BLOCK_SIZE)), c});
            if (iter != x_specials[i].end()) {
                out += iter->second;
            }
        }
        for (long long i = 0; i != y_specials.size(); ++i) {
            auto iter = y_specials[i].find({r, c % (1LL << (i * BLOCK_SIZE))});
            if (iter != y_specials[i].end()) {
                out += iter->second;
            }
        }

        cout << out << "\n";
    }
}
