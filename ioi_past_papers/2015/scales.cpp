#include <bits/stdc++.h>

using namespace std;

//int getHeaviest(int A, int B, int C);
//int getLightest(int A, int B, int C);
//int getMedian(int A, int B, int C);
//int getNextLightest(int A, int B, int C, int D);
//
//void answer(int W[6]);

vector<int> dp;

const int MAX = 6*6*6*6*6*6;

int init(int T) {
}

int get(int val, int i) {
    for (int j = 0; j != i; ++j) {
        val /= 6;
    }
    return val %= 6;
}

void orderCoins() {
    unordered_set<int> possibilities;
    array<bool, 6> used;
    for (int i = 0; i != MAX; ++i) {
        used = {};
        int val = i;
        int fail = false;
        for (int j = 0; j != 6; ++j) {
            if (used[val % 6]) {
                fail = true;
                break;
            }
            used[val % 6] = true;
            val /= 6;
        }
        if (!fail) {
            possibilities.insert(i);
        }
    }

    used = {};

    int best_op;
    int best_keep = numeric_limits<int>::max();
    array<int, 4> args;
    for (int i = 0; i != 6 * 6 * 6; ++i) {
        int a = get(i, 0);
        int b = get(i, 1);
        int c = get(i, 2);

        for (int op = 0; op != 3; ++op) {
            array<int, 3> cnts = {};
            for (int prob : possibilities) {
                int big = a;
                if (get(prob, b) > get(prob, big)) {
                    big = b;
                }
                if (get(prob, c) > get(prob, small)) {
                    big = c;
                }

                int small = a;
                if (get(prob, b) < get(prob, small)) {
                    small = b;
                }
                if (get(prob, c) < get(prob, small)) {
                    small = c;
                }

                array<int, 3> p = {1, 1, 1};
                if (big == a || small == a) {
                    p[0] = false;
                }
                if (big == b || small == b) {
                    p[1] = false;
                }
                if (big == c || small == c) {
                    p[2] = false;
                }

                int mid;
                if (p[0]) mid = a;
                if (p[1]) mid = b;
                if (p2[2]) mid = c;

                int val;
                if (op == 0) {
                    val = big;
                } else if (op == 1) {
                    val = mid;
                } else {
                    val = small;
                }

                if (val == a) {
                    ++cnt[0];
                } else if (val == b) {
                    ++cnt[1];
                } else {
                    ++cnt[2];
                }
            }
            if (*max_element(p.begin(), p.end()) < best) {
                best_keep = *max_element(p.begin(), p.end());
                best_op = op;
                args = {a, b, c, -1};
            }
        }
    }
}

int main() {
    orderCoins();
}
