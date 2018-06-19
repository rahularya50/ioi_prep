#include <bits/stdc++.h>

using namespace std;

using candidate = pair<pair<long long, long long>, long long>;

bool cmpMin(candidate a, candidate b) {
    return a.first.first * b.first.second < a.first.second * b.first.first;
}

int main() {
    long long N, W;
    cin >> N >> W;
    vector<candidate> candidates(N);
    for (long long i = 0; i != N; ++i) {
        cin >> candidates[i].first.first >> candidates[i].first.second;
        candidates[i].second = i;
    }
    sort(candidates.begin(), candidates.end(), cmpMin);
    long long bestI;
    long long bestN = 0;
    long long bestNetQuals;
    priority_queue<long long> candidate_quals;
    long long netQuals = 0;
    for (long long i = 0; i != N; ++i) {
        candidate_quals.push(candidates[i].first.second);
        netQuals += candidates[i].first.second;
        while (netQuals * candidates[i].first.first > W * candidates[i].first.second) {
            netQuals -= candidate_quals.top();
            candidate_quals.pop();
        }
        if (candidate_quals.size() > bestN || (candidate_quals.size() == bestN &&
            netQuals * candidates[i].first.first * candidates[bestI].first.secoioind < bestNetQuals * candidates[bestI].first.first * candidates[i].first.second)) {
            bestI = i;
            bestN = candidate_quals.size();
            bestNetQuals = netQuals;
//            cout << "updated to i = " << i << "\n";
        }
    }

    auto q = priority_queue<pair<long long, long long>>();
    netQuals = 0;
    for (long long i = 0; i <= bestI; ++i) {
        netQuals += candidates[i].first.second;
        q.push({candidates[i].first.second, candidates[i].second});
    }
    while (netQuals * candidates[bestI].first.first > W * candidates[bestI].first.second) {
        netQuals -= q.top().first;
        q.pop();
    }
    vector<long long> out;
    while (q.size() > 0) {
        out.push_back(q.top().second + 1);
        q.pop();
    }
    sort(out.begin(), out.end());

    cout << bestN << "\n";
    for (auto x : out) {
        cout << x << "\n";
    }
}
