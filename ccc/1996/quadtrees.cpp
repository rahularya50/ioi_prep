#include <bits/stdc++.h>

using namespace std;

int embed(int pos, int x, int y, int width, string& tree, vector<vector<bool>>& image) {
    if (tree[pos] == 'f') {
        for (int a = x; a != x + width; ++a) {
            for (int b = y; b != y + width; ++b) {
                image[a][b] = image[a][b] | 1;
            }
        }
    } else if (tree[pos] == 'e') {
    } else {
        pos = embed(pos + 1, x + width / 2, y, width / 2, tree, image);
        pos = embed(pos, x, y, width / 2, tree, image);
        pos = embed(pos, x, y + width / 2, width / 2, tree, image);
        pos = embed(pos, x + width / 2, y + width / 2, width / 2, tree, image);
        return pos;
    }
    return pos + 1;
}

int main() {
    int N;
    cin >> N;
    for (int t = 0; t != N; ++t) {
        vector<vector<bool>> image(32, vector<bool>(32, false));
        string tree1;
        cin >> tree1;
        embed(0, 0, 0, 32, tree1, image);
        string tree2;
        cin >> tree2;
        embed(0, 0, 0, 32, tree2, image);
        int out = 0;
        for (int i = 0; i != 32; ++i) {
            for (int j = 0; j != 32; ++j) {
                if (image[i][j]) {
                    ++out;
                }
            }
        }
        cout << "There are " << out << " black pixels." << "\n";
    }
}
