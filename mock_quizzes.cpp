#include <bits/stdc++.h>

using namespace std;

pair<long long, long long> lincomb(long long a, long long b) {
//    cout << a << " " << b << "\n";
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
//    cout << x << "^(-1) = " << lincomb(x, m).first << " (mod " << m << ")\n";
    return lincomb(x, m).first;
}

int main() {
    int N;
    cin >> N;
    const long long LIM = 100000;
    const long long MODULUS = 193; //1000000007;

    vector<long long> factorials = {1};
    for (long long i = 1; i <= LIM; ++i) {
        factorials.push_back((factorials.back() * i) % MODULUS);
    }
//    vector<long long> fact_run_sum;
    vector<long long> inv_fact;
//    int curr = 0;
    int curr_inv;
    for (auto x : factorials) {
//        curr += x;
//        fact_run_sum.push_back(curr);
        curr_inv += inverse(x, MODULUS);
        inv_fact.push_back(curr_inv);
    }


    for (int i = 0; i != N; ++i) {
        long long n, k;
        cin >> n >> k;
        cout << (factorials[n] * inverse(factorials[k], MODULUS) * inverse(factorials[n - k], MODULUS)) % MODULUS << "\n";
    }

}
