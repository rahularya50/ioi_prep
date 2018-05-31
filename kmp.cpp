#include <bits/stdc++.h>

using namespace std;

int main() {
    string source;
    string target;
    cin >> source >> target;
    vector<int> longest = {0}; // length of longest commonality between prefix + suffix *of* the prefix
    int prev = 0; // longest prefix of prefix that satisfies property
    for (int i = 1; i != target.size(); ++i) {
        while (prev && target[i] != target[prev]) {
            prev = longest[prev];
        }
        if (target[i] == target[prev]) {
            ++prev;
        }
        longest.push_back(prev);
    }
    int target_pos = 0;
    int out = 0;

    for (int i = 0; i != longest.size(); ++i) {
        cout << target.substr(0, i + 1) << ": " << longest[i] << "\n";
    }

    for (int i = 0; i != source.size(); ++i) {
        cout << "source: " << i << " and target: " << target_pos << "\n";
        char c = source[i];
        if (c == target[target_pos]) {
            ++target_pos;
            if (target_pos == target.size()) {
                ++out;
                target_pos = longest[target_pos];
            }
        } else {
            if (target_pos) {
                while (target_pos && c != target[target_pos]) {
                    target_pos = longest[target_pos];
                }
                if (c == target[target_pos]) {
                    ++target_pos;
                }
            }
        }
    }

    cout << out;
}
