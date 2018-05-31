#include <bits/stdc++.h>

using namespace std;

int log2(int N) {
    int out = 0;
    while (N >>= 1) {
        ++out;
    }
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    int N;
    cin >> N;
    vector<int> A;
    A.reserve(N);
    for (int i = 0; i != N; ++i) {
        int temp;
        cin >> temp;
        A.push_back(temp);
    }

    vector<vector<int>> table;
    table.push_back(A);
    for (int i = 1; (1 << i) <= N; ++i) {
        int stride = 1 << i;
//        cout << "Stride: " << stride << "\n";
        table.push_back({});
        for (int x = 0; x + stride <= N; ++x) {
            table[i].push_back(min(table[i - 1][x], table[i - 1][x + stride / 2]));
        }
    }

//    for (auto x : table) {
//        for (auto y : x) {
//            cout << y << " ";
//        }
//        cout << "\n";
//    }

    int Q;
    cin >> Q;
    for (int i = 0; i != Q; ++i) {
        int a, b;
        cin >> a >> b; // 1 indexed, inclusive
        int gap = b - a + 1;
        int row = log2(gap);
        int stride = 1 << row;
//        cout << "Gap = " << gap << " and stride = " << stride << "\n";
        cout << min(table[row][a], table[row][b + 1 - stride]) << "\n";
    }
}
