#include <bits/stdc++.h>

using namespace std;

int get_index(char x) {
    if (x - 'A' < 26) {
        return x - 'A';
    } else {
        return x - 'a' + 26;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int G, N;
    cin >> G >> N;
    string W, S;
    cin >> W >> S;
    int out = 0;
    vector<int> w_counts(52);
    for (auto x : W) {
        ++w_counts[get_index(x)];
    }
    vector<int> curr_counts(52);
    for (int i = 0; i != G; ++i) {
        ++curr_counts[get_index(S[i])];
    }
    int diffs = 0;
    for (int i = 0; i != 52; ++i) {
        if (w_counts[i] != curr_counts[i]) {
            ++diffs;
        }
    }
    out += (diffs == 0);
    for (int i = G; i != N; ++i) {
        int prev = i - G;
        int prev_index = get_index(S[prev]);
        int next_index = get_index(S[i]);
        if (curr_counts[prev_index] == w_counts[prev_index]) {
            ++diffs;
        }
        --curr_counts[prev_index];
        if (curr_counts[prev_index] == w_counts[prev_index]) {
            --diffs;
        }
        if (curr_counts[next_index] == w_counts[next_index]) {
            ++diffs;
        }
        ++curr_counts[next_index];
        if (curr_counts[next_index] == w_counts[next_index]) {
            --diffs;
        }
        if (diffs == 0) {
            ++out;
        }
    }
    cout << out;
}
