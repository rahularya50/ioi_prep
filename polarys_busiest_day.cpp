#include <bits/stdc++.h>

using namespace std;

const long long CAN = 1;
const long long MUST = 2;
const long long END = 3;

int main() {
    long long N;
    cin >> N;

    priority_queue<pair<long long, long long>> todo;
    vector<long long> lengths(N);
    vector<long long> starts(N);
    for (long long i = 0; i != N; ++i) {
        long long s, e;
        cin >> s >> e;

        todo.push({-s - e, i});
        starts[i] = s * 2;
        lengths[i] = (e - s) * 2;
    }

    long long time = 0;

    while (todo.size() > 0) {
        auto next = todo.top();
        todo.pop();
        if (time > -next.first) {
            cout << "NO";
            return 0;
        }
        time = max(time, starts[next.second]);
        time += lengths[next.second] / 2;
    }
    cout << "YES";

}
