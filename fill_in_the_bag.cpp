#include <bits/stdc++.h>

using namespace std;

const long long MODULUS = 1000000007LL;
const long long MAXSIZE = 101;

using matrix = vector<vector<long long>>;

matrix multiply (const matrix& A, const matrix& B) {
    auto N = A.size();
    matrix out(N, vector<long long>(N));
    for (long long i = 0; i != N ; ++i) {
        for (long long j = 0; j != N; ++j) {
            for (long long k = 0; k != N; ++k) {
                out[i][j] = (((A[i][k] % MODULUS) * (B[k][j] % MODULUS) % MODULUS) + out[i][j]) % MODULUS;
//                out[i][j] %= MODULUS;
            }
        }
    }
    return out;
}

void print(matrix X) {
    cout << "[\n";
    for (auto a : X) {
        cout << "   ";
        for (auto b : a) {
            cout << b << " ";
        }
        cout << "\n";
    }
    cout << "]\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long N, K;
    cin >> N >> K;
    vector<long long> C(MAXSIZE);
    for (long long i = 0; i != N; ++i) {
        long long x;
        cin >> x;
        ++C[x - 1];
    }

    matrix A(MAXSIZE + 1, vector<long long>(MAXSIZE + 1));
    A[0][0] = C[0] + 1;
    for (long long i = 1; i != MAXSIZE; ++i) {
        A[0][i] = C[i] - C[i - 1];
    }
    A[0][MAXSIZE] = -1 * C[MAXSIZE - 1];
    for (long long i = 0; i != MAXSIZE; ++i) {
        A[i + 1][i] = 1;
    }

    matrix I(MAXSIZE + 1, vector<long long>(MAXSIZE + 1));
    for (long long i = 0; i != MAXSIZE + 1; ++i) {
        I[i][i] = 1;
    }

    vector<matrix> Apowers = {A};
//    print(Apowers.back());
    for (long long k = 2; k <= K; k <<= 1LL) {
        Apowers.push_back(multiply(Apowers.back(), Apowers.back()));
//        print(Apowers.back());
    }

    matrix curr = I;
    for (long long i = 0; i != Apowers.size(); ++i) {
        if (K & (1LL << i)) {
            curr = multiply(curr, Apowers[i]);
        }
    }

//    print(curr);
//    while (curr[0][0] < 0) { }

    cout << ((curr[0][0] + MODULUS) % MODULUS);

}
