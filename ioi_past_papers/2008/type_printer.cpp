#include <bits/stdc++.h>

using namespace std;

using node = array<int, 26>;

deque<node> tree;
deque<int> cnt;

deque<int> fullDists;
deque<int> partDists;
deque<int> lastIndices;

deque<char> ops;

int getFullDist(int i) {
//    cout << i << "\n";
    if (fullDists[i] != -1) {
        return fullDists[i];
    }
    int out = 0;
    for (auto x : tree[i]) {
        if (x == -1) {
            continue;
        }
        out += getFullDist(x) + 2;
    }
//    cout << "fullDists[" << i << "] = " << out << "\n";
    fullDists[i] = out;
    return out;
}

int getPartDist(int i) {
//    cout << i << "\n";
    if (partDists[i] != -1) {
        return partDists[i];
    }
    int minDelta = 0;
    int lastIndex = -1;
    for (int j = 0; j != 26; ++j) {
//        cout << j << "\n";
        if (tree[i][j] == -1) {
            continue;
        }
        auto x = getFullDist(tree[i][j]);
        auto y = getPartDist(tree[i][j]);
        if (y - x <= minDelta) {
            lastIndex = j;
            minDelta = y - x;
        }
    }
    int out = 0;
    for (int j = 0; j != 26; ++j) {
        if (tree[i][j] == -1 || j == lastIndex) {
            continue;
        }
        out += getFullDist(tree[i][j]) + 2;
    }
    if (lastIndex != -1) {
        out += getPartDist(tree[i][lastIndex]) + 1;
    }
//    cout << "lastNode = " << tree[i][lastIndex] << "\n";
//    cout << "partDists[" << i << "] = " << out << "\n";
    lastIndices[i] = lastIndex;
    partDists[i] = out;
    return out;
}

void fullDisplay(int i) {
    for (int j = 0; j != 26; ++j) {
        if (tree[i][j] == -1) {
            continue;
        }
        cout << char('a' + j) << "\n";
        fullDisplay(tree[i][j]);
        cout << "-\n";
    }
    for (int j = 0; j != cnt[i]; ++j) {
        cout << "P\n";
    }
}

void display(int i) {
    for (int j = 0; j != 26; ++j) {
        if (tree[i][j] == -1 || j == lastIndices[i]) {
            continue;
        }
        cout << char('a' + j) << "\n";
        fullDisplay(tree[i][j]);
        cout << "-\n";
    }
    for (int j = 0; j != cnt[i]; ++j) {
        cout << "P\n";
    }
    if (lastIndices[i] != -1) {
        cout << char('a' + lastIndices[i]) << "\n";
        display(tree[i][lastIndices[i]]);
    }
}

int main() {
    int N;
    cin >> N;

    vector<string> words(N);
    for (auto& x : words) {
        cin >> x;
    }

    node blank;
    for (int i = 0; i != 26; ++i) {
        blank[i] = -1;
    }
    tree.push_back(blank);
    cnt.push_back(0);

    for (auto x : words) {
        int pos = 0;
//        cout << "newWord\n";
        for (auto y : x) {
            if (tree[pos][y - 'a'] == -1) {
                tree[pos][y - 'a'] = tree.size();
                tree.push_back(blank);
                cnt.push_back(0);
            }
            pos = tree[pos][y - 'a'];
//            cout << pos << "\n";
        }
        ++cnt[pos];
    }

    fullDists = deque<int>(tree.size(), -1);
    partDists = deque<int>(tree.size(), -1);
    lastIndices = deque<int>(tree.size(), -1);
    cout << getPartDist(0) + N << "\n";
    for (auto x : ops) {
        cout << x << "\n";
    }
    display(0);
}
