#include <bits/stdc++.h>

using namespace std;

pair<long long, long long> go(long long pos, deque<long long>& blocked, const vector<long long>& pros, const vector<long long>& judges,
                  map<pair<long long, deque<long long>>, pair<long long, long long>>& cache) {
    if (cache.find({pos, blocked}) != cache.end()) {
        return cache[{pos, blocked}];
    }

    if (pos == judges.size()) {
        return {-1, 0}; // {pros_index, score}
    }

    long long best_move = -1;
    long long best_score = -1;

    for (long long i = 0; i != pros.size(); ++i) {
        if (find(blocked.begin(), blocked.end(), i) != blocked.end()) {
            continue;
        }
        long long f = blocked.front();
        blocked.pop_front();
        blocked.push_back(i);

        long long score = go(pos + 1, blocked, pros, judges, cache).second;

        if (pros[i] > judges[pos]) {
            score += (pros[i] - judges[pos]) * judges[pos];
        }

        if (score > best_score) {
            best_score = score;
            best_move = i;
        }

        blocked.pop_back();
        blocked.push_front(f);
    }

    cache[{pos, blocked}] = {best_move, best_score};
    return cache[{pos, blocked}];
}


int main() {
    long long N, M;
    cin >> N >> M;
    vector<long long> s;
    for (long long i = 0; i != N; ++i) {
        long long temp;
        cin >> temp;
        s.push_back(temp);
    }
    vector<long long> t;
    for (long long i = 0; i != M; ++i) {
        long long temp;
        cin >> temp;
        t.push_back(temp);
    }


    vector<pair<long long, long long>> bests;
    for (long long i = 0; i != N; ++i) {
        bests.push_back({s[i], i});
    }

    sort(bests.begin(), bests.end());

    vector<long long> best_indices;
    vector<long long> best_vals;

    for (long long i = 0; i != 7 && i != bests.size(); ++i) {
        best_indices.push_back(bests[bests.size() - 1 - i].second);
        best_vals.push_back(bests[bests.size() - 1 - i].first);
    }

    map<pair<long long, deque<long long>>, pair<long long, long long>> cache = {};
    deque<long long> blocked = {-1, -1, -1};

    auto res = go(0, blocked, best_vals, t, cache);

    auto curr_move = res.first;
    auto best_score = res.second;

    long long pos = 0;

    cout << best_score << "\n";

    while (pos != M) {
        auto res = cache[{pos, blocked}];
        curr_move = res.first;
        cout << best_indices[curr_move] + 1 << " ";
        blocked.pop_front();
        blocked.push_back(curr_move);
        ++pos;
    }
}
