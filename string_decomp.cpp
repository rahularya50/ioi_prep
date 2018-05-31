#include <bits/stdc++.h>

using namespace std;

int main() {
    string S;
    dict D;
    cin >> S;
    vector<int>& cache(S.size(), -1);
    nextWordPos(0, S, D, cache);

}

int nextWordPos(int start_index, string S, dict D, vector<int>& cache) {
    if (start_index == S.size()) {
        return start_index;
    }
    if (cache[nextWordPos] != -1) {
        return cache[nextWordPos];
    }
    string curr;
    for (int i = start_index; i != S.size(); ++i) {
        curr += S[i];
        if (D.contains(curr)) {
            if (nextWordPos(i + 1, S, D) != 0) {
                cache[start_index] = i + 1;
                return i + 1;
            }
        }
    }
    cache[start_index] = 0;
    return 0;
}
