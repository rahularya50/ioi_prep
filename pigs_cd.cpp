#include <bits/stdc++.h>

using namespace std;

//long long log2(long long N) {
//    if (!N) {
//        return 0;
//    }
//    long long out = 0;
//    while (N >>= 1) {
//        ++out;
//    }
//    return out;
//}

long long gcd(long long a, long long b) {
//    cout << a << " " << b << "\n";
    if (b > a) {
        return gcd(b, a);
    }
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

long long lookup(long long a, long long b, const vector<vector<long long>>& table) {
//    cout << "Looking up " << a << " to " << b << endl;
    long long len = b - a;
    long long row = log2(len); // Check this
//    cout << "Row: " << row << endl;
    long long stride = 1 << row;
//    cout << "Ans = " << gcd(table[row][a], table[row][b - stride]) << endl;
    return gcd(table[row][a], table[row][b - stride]);
}

pair<long long, long long> raw_lookup(long long a, long long b, const vector<vector<long long>>& table) {
//    cout << "Looking up " << a << " to " << b << endl;
    long long len = b - a;
    long long row = log2(len); // Check this
//    cout << "Row: " << row << endl;
    long long stride = 1 << row;
//    cout << "Ans = " << gcd(table[row][a], table[row][b - stride]) << endl;)
    return {table[row][a], table[row][b - stride]};
}

bool is_valid(long long a, long long b, long long target, const vector<vector<long long>>& table) {
    auto x = raw_lookup(a, b, table);
    return x.first >= target && x.second >= target && (x.first % target == 0) && (x.second % target == 0);
}

void go(long long i, long long j, long long base_i, unordered_map<long long, long long>& out, const vector<vector<long long>>& table, const vector<long long>& A, const vector<long long>& B) {
    if (i == table.front().size()) {
        return;
    }

    long long low = i;
    long long high = j;

    auto target = lookup(base_i, low + 1, table);

    while (high - low > 1) {
//        cout << "Trying i = " << i << " and " << low << " <= j < " << high << "\n";
        long long mid = (low + high) / 2;
        if (is_valid(base_i, mid + 1, target, table)) {
            low = mid;
        } else {
            high = mid;
        }
    }

    long long seg_gcd = lookup(base_i, high, table);

    if (out.find(seg_gcd) != out.end()) {
        out[seg_gcd] += B[high + 1] - B[i + 1] - static_cast<long long>(high - i) * A[base_i];
    //    cout << "Adding all sums for i = " << base_i << " and " << i << " <= j < " << high << endl;
    //    cout << "Result = " << B[high + 1] - B[i + 1] - (high - i) * A[base_i] << endl;
    }

    go(high, j, base_i, out, table, A, B);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    long long N;
    cin >> N;

    vector<long long> S;
    S.reserve(N);
    for (long long i = 0; i != N; ++i) {
        long long temp;
        cin >> temp;
        S.push_back(temp);
    }

    vector<long long> T;
    T.reserve(N);
    for (long long i = 0; i != N; ++i) {
        long long temp;
        cin >> temp;
        T.push_back(temp);
    }

    vector<vector<long long>> table;
    table.reserve(log2(N) + 1);
    table.push_back(S);
    for (long long row = 1; (1 << row) <= N; ++row) {
        long long stride = 1 << row;
        table.push_back({});
//        cout << stride << endl;
        for (long long x = 0; x + stride <= N; ++x) {
            table[row].push_back(gcd(table[row - 1][x], table[row - 1][x + stride / 2]));
//            cout << table[row].back() << " ";
        }
//        cout << endl;
    }

//    cout << "table gen complete" << endl;

    vector<long long> A = {0};
    A.reserve(N + 2);
    long long x = 0;
    for (long long y : T) {
        x += y;
        A.push_back(x);
    }

    vector<long long> B = {0};
    x = 0;
    B.reserve(N + 2);
    for (long long y : A) {
        x += y;
        B.push_back(x);
    }

//
//    cout << "A = [";
//    for (auto x : A) {
//        cout << x << ", ";
//    }
//    cout << "]\n B = [";
//    for (auto x : B) {
//        cout << x << ", ";
//    }
//    cout << "]" << endl;
//
//    cout << "run sums complete" << endl;

    long long Q;
    cin >> Q;

    vector<long long> xs;
    xs.reserve(Q);

    unordered_map<long long, long long> out;

    for (long long i = 0; i != Q; ++i) {
        long long x;
        cin >> x;
        out[x] = 0;
        xs.push_back(x);
//        cout << out[x] << "\n";
    }


    for (long long i = 0; i != N; ++i) {
        go(i, N, i, out, table, A, B);
    }

    for (auto x : xs) {
        cout << out[x] << "\n";
    }

}
