#include <bits/stdc++.h>

using namespace std;

const long long MODULUS = 1000000007;

pair<long long, long long> lincomb(long long a, long long b) {
    if (b > a) {
        auto x = lincomb(b, a);
        return {x.second, x.first};
    }
    if (b == 1) {
        return {0, 1};
    }
    auto x = lincomb(b, a % b);
    auto y = a / b;
    return {x.second, x.first - y * x.second};
}

long long inverse(long long x, long long m) {
    return lincomb(x, m).first;
}

bool cmp(const pair<pair<int, int>, pair<int, int>>& x, const pair<pair<int, int>, pair<int, int>>& y) {
    if (x.first.first == y.first.first) {
        return x.second.second < y.second.second;
    }
    return x.first.first < y.first.first;
}

long long choose(int n, int k, const vector<long long>& factorials, const vector<long long>& inv_fact) {
    auto out = factorials[n];
    out *= inv_fact[k];
    out %= MODULUS;
    out *= inv_fact[n - k];
    out %= MODULUS;
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;

    const long long LIM = 100000;

    long long two_inv = MODULUS / 2 + 1;

    vector<long long> factorials = {1};
    factorials.reserve(LIM);
    for (long long i = 1; i <= LIM; ++i) {
        factorials.push_back((factorials.back() * i) % MODULUS);
    }

    vector<long long> inv_fact;
    inv_fact.reserve(LIM);
    for (auto x : factorials) {
        inv_fact.push_back(inverse(x, MODULUS));
    }

    vector<pair<pair<int, int>, pair<int, int>>> queries;
    queries.reserve(N);

    for (int i = 0; i != N; ++i) {
        int n, k;
        cin >> n >> k;
        queries.push_back({{-1, i}, {n, k}});
    }
//
//    sort(queries.begin(), queries.end(),
//         [](pair<pair<int, int>, pair<int, int>> x, pair<pair<int, int>, pair<int, int>> y){return x.second < y.second; });

    for (int i = 0; i != N; ++i) {
        queries[i].first.first = sqrt(queries[i].second.first);
    }

    sort(queries.begin(), queries.end(), cmp);

    vector<long long> out(N);

    int curr_n = 0;
    int curr_k = 0;
    long long curr_f = 1;

    for (auto q : queries) {
//        cout << "f(" << curr_n << ", " << curr_k << ") = " << curr_f << "\n";
        auto n = q.second.first;
        auto k = q.second.second;

        while (curr_n != n || curr_k != k) {
            if (curr_n < n) {
                curr_f = (2LL * curr_f - choose(curr_n, curr_k, factorials, inv_fact)) % MODULUS;
                ++curr_n;

            }
            else if (curr_k > k) {
                curr_f = (curr_f - choose(curr_n, curr_k, factorials, inv_fact)) % MODULUS;
                --curr_k;
            }
            else if (curr_n > n && curr_k != curr_n) {
                curr_f = ((curr_f + choose(curr_n - 1, curr_k, factorials, inv_fact)) * two_inv) % MODULUS;
                --curr_n;

            }
            else if (curr_k < k && curr_k != curr_n) {
                curr_f = (curr_f + choose(curr_n, curr_k + 1, factorials, inv_fact)) % MODULUS;
                ++curr_k;
            }
        }

        out[q.first.second] = (curr_f + MODULUS) % MODULUS;
    }

    for (auto x : out) {
        cout << x << "\n";
    }
}
