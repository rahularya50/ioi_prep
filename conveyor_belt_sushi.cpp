#include <bits/stdc++.h>

using namespace std;

bool contained(long long K, long long s, long long e) {
    if (e > s) {
        return (K >= s) && (K < e);
    }
    else {
        return (K >= s) || (K < e);
    }
}

int main() {
    ios::sync_with_stdio(false);

    long long N, K, Q;
    cin >> N >> K >> Q;
    --K;

    map<long long, long long> segments;
    list<long long> labels;
    for (long long i = 0; i != N; ++i) {
        labels.push_back(i + 1);
    }

    auto curr_label = labels.begin();
    for (long long i = 0; i != K; ++i) {
        ++curr_label;
    }
    bool full = true;
    bool empt = false;

    for (long long i = 0; i != Q; ++i, K = ((K + 1) % N))
    {
//        cout << "K = " << K << " ( ";
//        for (auto seg : segments) {
//            cout << "(" << seg.first << ", " << seg.second << "), ";
//        }
//        cout << ")\n";

        char c;
        cin >> c;

        if (c == 'T') {
            if (full) {
                segments = {{(K + 1) % N, K}};
                full = false;
                if (N == 1) {
                    empt = true;
                    cout << (*curr_label) << "\n";
                    continue;
                }
            } else if (empt) {
                cout << -1 << "\n";
                continue;
            }
            else {
                auto curr_segment = segments.upper_bound(K);
                if (curr_segment == segments.begin()) {
                    curr_segment = segments.end();
                }
                --curr_segment;

                long long start_index = (*curr_segment).first;
                long long end_index = (*curr_segment).second;

                if (!contained(K, start_index, end_index)) {
                    cout << -1 << "\n";
                    continue;
                }

                segments.erase(curr_segment);
                if (start_index != K) {
                    segments[start_index] = K;
                }
                if (end_index != ((K + 1) % N)) {
                    segments[(K + 1) % N] = end_index;
                }
            }

            cout << (*curr_label) << "\n";
            auto to_remove = curr_label;
            ++curr_label;
            labels.erase(to_remove);
            if (curr_label == labels.end()) {
                curr_label = labels.begin();
            }
            if (labels.size() == 0) {
                empt = true;
            }
        }
        else if (c == 'B') {
            if (empt) {
                continue;
            }
            if (full) {
                K = (K + N - 1) % N;
                continue;
            }
            auto curr_segment = segments.upper_bound(K);
            if (curr_segment == segments.begin()) {
                curr_segment = segments.end();
            }
            --curr_segment;
            long long start_index = (*curr_segment).first;
            long long end_index = (*curr_segment).second;

            if (!contained(K, start_index, end_index)) {
                continue;
            }

            segments.erase(curr_segment);
            if (start_index != K) {
                segments[start_index] = K;
            }

            long long new_end_index = (end_index + 1) % N;
            if (segments.find(new_end_index) != segments.end()) {
                segments[(K + 1) % N] = segments[new_end_index];
                segments.erase(new_end_index);
            }
            else {
                segments[(K + 1) % N] = new_end_index;
            }
        }
        else {
            if (empt) {
                continue;
            }
            if (!full) {
                auto curr_segment = segments.upper_bound(K);
                if (curr_segment == segments.begin()) {
                    curr_segment = segments.end();
                }
                --curr_segment;
                if (!contained(K, (*curr_segment).first, (*curr_segment).second)) {
                    continue;
                }
            }
            ++curr_label;
            if (curr_label == labels.end()) {
                curr_label = labels.begin();
            }
        }
    }
}
