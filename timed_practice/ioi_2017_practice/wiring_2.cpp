#include <bits/stdc++.h>

using namespace std;

long long min_total_length(std::vector<int> r, std::vector<int> b) {
    long long out = 0;
    int r_pos = r.size() - 1;
    int b_pos = 0;
    while (r_pos >= 0 && b_pos < b.size()) {
        out += b[b_pos] - r[r_pos];
        ++b_pos;
        --r_pos;
    }
    while (r_pos >= 0) {
        out += b[0] - r[r_pos];
        --r_pos;
    }
    while (b_pos != b.size()) {
        out += b[b_pos] - r.back();
        ++b_pos;
    }
    return out;
}
