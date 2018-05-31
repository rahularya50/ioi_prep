#include <bits/stdc++.h>

using namespace std;

int log2(int N) {
    int out = 1;
    while (N >>= 1) {
        ++out;
    }
    return out;
}

int go(int i, int depth, int maxdepth, int a, int b, const vector<int>& segment_tree) {
    int seg_size = 1 << (maxdepth - depth);
    int seg_start = seg_size * (i - (1 << depth) + 1);
    int seg_end = seg_start + seg_size;
    int mid = (seg_start + seg_end) / 2;

    if (a == seg_start && b == seg_end) {
        return segment_tree[i];
    }
    int out = -1;

    if (a < mid) {
        out = max(out, go(2 * i + 1, depth + 1, maxdepth, a, min(b, mid), segment_tree));
    }

    if (b > mid) {
        out = max(out, go(2 * i + 2, depth + 1, maxdepth, max(a, mid), b, segment_tree));
    }

    return out;
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> L;
    for (int i = 0; i != N; ++i) {
        int temp;
        cin >> temp;
        L.push_back(temp);
    }

    int logN = log2(N);
    N = 1 << logN;
    while (L.size() < N) {
        L.push_back(0);
    }


    vector<int> segment_tree(2*N - 1, -1);
    for (int i = N - 1; i != 2*N - 1; ++i) {
        segment_tree[i] = L[i + 1 - N];
    }

    for (int row = logN - 1; row >= 0; --row) {
        for (int i = ((1 << row) - 1); i != ((1 << (row + 1)) - 1); ++i) {
            segment_tree[i] = max(segment_tree[2*i + 1], segment_tree[2*i + 2]);
        }
    }

    for (int i = 0; i != M; ++i) {
        int a, b;
        cin >> a >> b;
        cout << go(0, 0, logN, min(a - 1, b), max(a - 1, b), segment_tree) << "\n";
    }

}
