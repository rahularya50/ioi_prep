#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int N;
    while (cin >> N) {
        string source;
        string target;

        cin >> target;

        vector<int> longest_suffix(target.size());

        int pos = 0; // Represents current trial *pointer*
        for (int i = 1; i != target.size(); ++i) {
            while (pos && target[i] != target[pos]) {
                pos = longest_suffix[pos - 1]; // Reverting pointer to previous possibility, one past the last known longest prefix of suffix
            }
            if (target[i] == target[pos]) {
                ++pos; // If it matches, we can move the pointer forward
            }
            longest_suffix[i] = pos; // Currently, everything behind the pointer matches the suffix.
        }

//        for (int i = 0; i != target.size(); ++i) {
//            cout << longest_suffix[i] << " ";
//            for (int j = 0; j <= i; ++j) {
//                cout << target[j];
//            }
//            cout << "\n";
//        }

        cin >> source;

        pos = 0;
        for (int x = 0; x != source.size(); ++x) {
            if (source[x] == target[pos]) {
                ++pos;
                if (pos == target.size()) {
                    cout << (x - target.size() + 1) << "\n";
                    pos = longest_suffix[pos - 1];
                }
            } else {
                if (pos) {
                    pos = longest_suffix[pos - 1];
                    --x;
                }
            }
        }

        cout << "\n";
    }
}
