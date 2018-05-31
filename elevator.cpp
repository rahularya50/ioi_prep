#include <bits/stdc++.h>

using namespace std;

long long log2(long long N) {
    long long out = 1;
    while (N >>= 1) {
        ++out;
    }
    return out;
}

long long amount(long long row, long long col, long long minPos, long long maxPos, const vector<vector<long long>>& segment_tree) {
    long long step_pos = 1 << (segment_tree.size() - row - 1);
    long long start_pos = col * step_pos;
    long long end_pos = (col + 1) * step_pos;
    long long mid_pos = (start_pos + end_pos) / 2;

    if (minPos == start_pos && maxPos == end_pos) {
        return segment_tree[row][col];
    }

    long long out = 0;
    if (minPos < mid_pos) {
        out += amount(row + 1, col * 2, minPos, min(mid_pos, maxPos), segment_tree);
    }
    if (maxPos > mid_pos) {
        out += amount(row + 1, col * 2 + 1, max(mid_pos, minPos), maxPos, segment_tree);
    }
    return out;
}

void add(long long row, long long col, long long pos, vector<vector<long long>>& segment_tree) {
    long long step_pos = 1 << (segment_tree.size() - row - 1);
    long long start_pos = col * step_pos;
    long long end_pos = (col + 1) * step_pos;
    long long mid_pos = (start_pos + end_pos) / 2;

    if (start_pos <= pos && end_pos > pos) {
        ++segment_tree[row][col];
    }

    if (step_pos > 1) {
        if (pos < mid_pos) {
            add(row + 1, col * 2, pos, segment_tree);
        }
        else {
            add(row + 1, col * 2 + 1, pos, segment_tree);
        }
    }
}

void subtract(long long row, long long col, long long pos, vector<vector<long long>>& segment_tree) {
    long long step_pos = 1 << (segment_tree.size() - row - 1);
    long long start_pos = col * step_pos;
    long long end_pos = (col + 1) * step_pos;
    long long mid_pos = (start_pos + end_pos) / 2;

    if (start_pos <= pos && end_pos > pos) {
        --segment_tree[row][col];
    }

    if (step_pos > 1) {
        if (pos < mid_pos) {
            subtract(row + 1, col * 2, pos, segment_tree);
        }
        else {
            subtract(row + 1, col * 2 + 1, pos, segment_tree);
        }
    }
}

void print_tree(const vector<vector<long long>>& segment_tree) {
    cout << "Tree: \n";
    for (auto x : segment_tree) {
        for (auto y : x) {
            cout << y << " ";
        }
        cout << "\n";
    }
}

int main() {
    long long N, H;
    cin >> N >> H;

    long long M = 0;
    vector<pair<long long, vector<long long>>> waits;
    waits.reserve(N);
    for (long long i = 0; i != N; ++i) {
        long long f, c;
        cin >> f >> c;
        M += c;
        vector<long long> people;
        people.reserve(c);
        for (long long i = 0; i != c; ++i) {
            long long temp;
            cin >> temp;
            people.push_back(temp);
        }
        waits.push_back({f, people});
    }

    M = 1 << log2(M);
//    cout << M << "\n";
    vector<vector<long long>> segment_tree;
    for (long long s = M; s >= 1; s >>= 1) {
        segment_tree.push_back(vector<long long>(M / s));
    }
//    prlong long_tree(segment_tree);

    long long out = 0;
    priority_queue<pair<long long, long long>,
                   vector<pair<long long, long long>>,
                   greater<pair<long long, long long>>> onboard_back_pos;
                   // {dest_floor, pos from back}

    long long waits_index = 0;
    long long onboard = 0;

    while (onboard_back_pos.size() > 0 || waits_index < waits.size()) {
        long long next_onboard = numeric_limits<long long>::max();
        long long next_offboard = numeric_limits<long long>::max();

        if (!onboard_back_pos.empty()) {
            next_offboard = onboard_back_pos.top().first;
        }
        if (waits_index != waits.size()) {
            next_onboard = waits[waits_index].first;
        }

//        cout << min(next_offboard, next_onboard) << "\n";

        if (next_offboard <= next_onboard) {
//            cout << "offboarding" << "\n";
//            prlong long_tree(segment_tree);
            long long max_back = onboard_back_pos.top().second;
            long long num_getting_off = 0;
            out += amount(0, 0, max_back, onboard, segment_tree);
            while (onboard_back_pos.size() > 0 && onboard_back_pos.top().first == next_offboard) {
                long long pos = onboard_back_pos.top().second;
                subtract(0, 0, pos, segment_tree);
                onboard_back_pos.pop();
                ++num_getting_off;
            }
            out += amount(0, 0, max_back, onboard, segment_tree);
        }
        else {
//            cout << "onboarding" << "\n";
            for (auto x : waits[waits_index].second) {
                add(0, 0, onboard, segment_tree);
                onboard_back_pos.push({x, onboard});
                ++onboard;
                ++out;
            }
            ++waits_index;
        }
    }

    cout << out;
}
