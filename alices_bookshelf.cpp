#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> lhs;
    priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>> rhs;
    set<int> removed;
    int i = 0;

    for (int j = 0; j != N; ++j) {
        int type;
        cin >> type;
        if (type == 1) {
            int X;
            cin >> X;
            lhs.push({X, i});
            rhs.push({X, i});
            ++i;
        }
        else if (type == 2) {
            while (lhs.size() > 0 && removed.find(lhs.top().second) != removed.end()) {
                lhs.pop();
            }
            if (lhs.size() == 0) {
                cout << "-1\n";
            }
            else {
                cout << lhs.top().first << "\n";
            }
        }
        else if (type == 3) {
            while (rhs.size() > 0 && removed.find(rhs.top().second) != removed.end()) {
                rhs.pop();
            }
            if (rhs.size() == 0) {
                cout << "-1\n";
            }
            else {
                cout << rhs.top().first << "\n";
            }
        }
        else if (type == 4) {
            while (lhs.size() > 0 && removed.find(lhs.top().second) != removed.end()) {
                lhs.pop();
            }
            removed.insert(lhs.top().second);
            lhs.pop();
        }
        else if (type == 5) {
            while (rhs.size() > 0 && removed.find(rhs.top().second) != removed.end()) {
                rhs.pop();
            }
            removed.insert(rhs.top().second);
            rhs.pop();
        }
    }
}
