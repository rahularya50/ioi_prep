#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> rates(N);
    for (auto& x : rates) {
        cin >> x;
    }
    vector<int> weights(M);
    for (auto& x : weights) {
        cin >> x;
    }
    set<int> unoccupied;
    for (int i = 0; i != N; ++i) {
        unoccupied.insert(i);
    }
    vector<int> pos(M);
    deque<int> waiting;
    int out = 0;
    for (int i = 0; i != 2*M; ++i) {
        int x;
        cin >> x;
        if (x > 0) {
            // arrival
            if (unoccupied.size() > 0) {
                pos[x - 1] = *unoccupied.begin();
                unoccupied.erase(unoccupied.begin());
            } else {
                waiting.push_back(x - 1);
            }
        } else {
            // departure
            unoccupied.insert(pos[-1-x]);
            out += weights[-1-x] * rates[pos[-1-x]];
//            cout << out << "\n";
            if (waiting.size() > 0) {
                pos[waiting.front()] = *unoccupied.begin();
                waiting.pop_front();
                unoccupied.erase(unoccupied.begin());
            }
        }
    }
    cout << out;
}
