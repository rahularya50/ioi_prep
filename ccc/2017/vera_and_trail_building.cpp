#include <bits/stdc++.h>

using namespace std;

int main() {
    int K;
    cin >> K;

    int V = 0;
    int E = 0;

    int val = sqrt(K) * 2;

    vector<int> squared;
    while (K > 0) {
        while (val * (val - 1) / 2 > K) {
            --val;
        }
        squared.push_back(val);
        K -= val * (val - 1) / 2;
        V += val;
        E += val;
        E += 1; // connector edge
    }

    --E;

    cout << V << " " << E << "\n";
    int curr = 1;
    for (auto x : squared) {
        if (curr != 1) {
            cout << (curr - 1) << " " << curr << "\n";
        }
        for (int i = 0; i != x - 1; ++i) {
            cout << (curr + i) << " " << (curr + i + 1) << "\n";
        }
        cout << (curr + x - 1) << " " << curr << "\n";
        curr += x;
    }


}
