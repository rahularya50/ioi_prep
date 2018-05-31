#include <bits/stdc++.h>

using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 0; t != T; ++t) {
        int N;
        cin >> N;
        vector<int> men;
        for (int i = 0; i != N; ++i) {
            int x;
            cin >> x;
            men.push_back(x);
        }
        vector<int> women;
        for (int i = 0; i != N; ++i) {
            int x;
            cin >> x;
            women.push_back(x);
        }
        sort(men.begin(), men.end());
        sort(women.begin(), women.end());
        long long out = 0;
        for (int i = 0; i != N; ++i) {
            out += men[i] * women[i];
        }
        cout << out << "\n";
    }
}
