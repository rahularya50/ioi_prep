#include <bits/stdc++.h>

using namespace std;

const int MAXLEN = 300000;

int main() {
    int a = 1;
    int b = 1;
    vector<char> F = {'0', '1'};
    F.reserve(MAXLEN * 2);

    while (a < MAXLEN) {
        for (int i = 0; i != a; ++i) {
            F.push_back(F[i]);
        }
        int c = a;
        a = a + b;
        b = c;
    }

//    for (auto x : F) {
//        cout << x;
//    }

    for (int t = 0; t != 5; ++t) {
        string inp;
        cin >> inp;
        int N = inp.size();
        vector<int> prefix_len(N, -1); // ending at char
        prefix_len[0] = 0;
        int curr = 0; // endpos of trial prefix
        for (int i = 1; i != N; ++i) {
            while (curr && inp[curr] != inp[i]) {
                curr = prefix_len[curr - 1];
            }
            if (inp[curr] == inp[i]) {
                ++curr;
            }
            prefix_len[i] = curr;
        }

//        for (int i = 0; i != N; ++i) {
//            for (int j = 0; j <= i; ++j) {
//                cout << inp[j];
//            }
//            cout << " " << prefix_len[i] << "\n";
//        }

        int pos = 0;
        bool found = false;
        for (int i = 0; i != F.size(); ++i) {
            if (F[i] == inp[pos]) {
                ++pos;
                if (pos == N) {
                    found = true;
                }
            } else {
                if (pos) {
                    pos = prefix_len[pos - 1];
                    --i;
                }
            }
        }

        cout << (found ? "YES" : "NO") << "\n";
    }

}
