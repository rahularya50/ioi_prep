#include <bits/stdc++.h>

using namespace std;

int go(vector<int> amounts, const vector<pair<int, int>>& needed) {
    vector<int> need_now = {0};
    map<int, int> waitingon = {};

    while (true) {
        int i = need_now.back();

        if (waitingon[i] > 8) {
            break;
        }

        auto source = needed[i];
        int a = source.first;
        int b = source.second;
        if (a && b && amounts[a] && amounts[b]) {
            --amounts[a];
            --amounts[b];
            ++amounts[i];
            need_now.pop_back();
            if (i == 0) {
                need_now.push_back(0);
            } else {
                --waitingon[i];
            }
        }
        else {
            if (!a || !b)
                break;
            if (!amounts[a]) {
                need_now.push_back(a);
                ++waitingon[a];
            }
            if (!amounts[b]) {
                need_now.push_back(b);
                ++waitingon[b];
            }
        }
    }

    return amounts[0];
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i != T; ++i) {
        int M;
        cin >> M;
        vector<pair<int, int>> needed;
        for (int j = 0; j != M; ++j) {
            int x, y;
            cin >> x >> y;
            needed.push_back({x - 1, y - 1});
        }

        vector<int> A;
        for (int j = 0; j != M; ++j) {
            int temp;
            cin >> temp;
            A.push_back(temp);
        }

        cout << "Case #" << (i + 1) << ": " << go(A, needed) << "\n";
    }
}
