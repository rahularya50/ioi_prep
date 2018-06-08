#include <bits/stdc++.h>

using namespace std;

struct y_segment {
    long long start_y;
    long long end_y;
    y_segment *left_index;
    y_segment *right_index;
    long long val;
};

struct x_segment {
    int start_x;
    int end_x;
    x_segment *left_index;
    x_segment *right_index;
    y_segment *val;
};

y_segment empty_y_seg;

int cnt;

long long gcd(long long X, long long Y) {
    long long tmp;
//    cout << "gcd of " << X << " and " << Y << "is = ";
    while (X != Y && Y != 0) {
        tmp = X;
        X = Y;
        Y = tmp % Y;
    }
//    cout << X << "\n";
    return X;
}

void y_update(y_segment *y_i, long long y_target, long long val) {
//    cout << "Considering subsegment between " << y_i->start_y << " <= y < " << y_i->end_y << "\n";
    if (y_i->start_y + 1 == y_i->end_y) {
        y_i->val = val;
//            cout << "Settingx subsegment between " << y_i->start_y << " <= y < " << y_i->end_y << " to " << val << "\n";
        return;
    }
    auto mid_pos = (y_i->start_y + y_i->end_y) / 2;
    if (y_target < mid_pos) {
        if (y_i->left_index == nullptr) {
            auto new_left = new y_segment({y_i->start_y, mid_pos, nullptr, nullptr, 0});
            y_i->left_index = new_left;
        }
        y_update(y_i->left_index, y_target, val);
    } else {
        if (y_i->right_index == nullptr) {
            auto new_right = new y_segment({mid_pos, y_i->end_y, nullptr, nullptr, 0});
            y_i->right_index = new_right;
        }
        y_update(y_i->right_index, y_target, val);
    }
    auto lval = (y_i->left_index) == nullptr ? 0 : y_i->left_index->val;
    auto rval = (y_i->right_index) == nullptr ? 0 : y_i->right_index->val;

    y_i->val = gcd(lval, rval);

//    cout << "considering = " << y_i->left_index << " and " << y_i->right_index << "\n";
//    cout << "Setting subsegment (i = " << y_i << ") between " << y_i->start_y << " <= y < " << y_i->end_y << " to " << y_i->val << "\n";
}

void x_update(x_segment *x_i, int x_target, long long y_target, long long val) {
//    cout << "Considering segment between " << x_i->start_x << " <= x < " << x_i->end_x << "\n";
    y_update(x_i->val, y_target, val);
    if (x_i->left_index == nullptr) {
        if (x_i->start_x + 1 == x_i->end_x) {
            return;
        }
        auto mid_pos = (x_i->start_x + x_i->end_x) / 2;
        auto left_empty = new y_segment(empty_y_seg);
        auto right_empty = new y_segment(empty_y_seg);
        auto new_left = new x_segment({x_i->start_x, mid_pos, nullptr, nullptr, left_empty});
        auto new_right = new x_segment({mid_pos, x_i->end_x, nullptr, nullptr, right_empty});
        x_i->left_index = new_left;
        x_i->right_index = new_right;
    }
    auto& left_seg = x_i->left_index;
    auto& right_seg = x_i->right_index;
    if (x_target < left_seg->end_x) {
        x_update(x_i->left_index, x_target, y_target, val);
    } else {
        x_update(x_i->right_index, x_target, y_target, val);
    }
}

long long y_lookup(y_segment *y_i, long long minY, long long maxY) {
    auto& curr_seg = *y_i;
    if (minY <= curr_seg.start_y && curr_seg.end_y <= maxY) {
//        cout << "Including subsegment between " << (curr_seg.start_y) << " <= y < " << (curr_seg.end_y) << "\n";
        return curr_seg.val;
    }
    long long out = 0;
    if (curr_seg.left_index != nullptr) {
        if (minY < curr_seg.left_index->end_y) {
            out = gcd(out, y_lookup(curr_seg.left_index, minY, min(maxY, curr_seg.left_index->end_y)));
        }
    }
    if (curr_seg.right_index != nullptr) {
        if (maxY > curr_seg.right_index->start_y) {
            out = gcd(out, y_lookup(curr_seg.right_index, max(minY, curr_seg.right_index->start_y), maxY));
        }
    }
    return out;

}

long long x_lookup(x_segment *x_i, int minX, int maxX, long long minY, long long maxY) {
    auto& curr_seg = *x_i;
    if (minX <= curr_seg.start_x && curr_seg.end_x <= maxX) {
//        cout << "Including segment between " << curr_seg.start_x << " <= x < " << curr_seg.end_x << "\n";
        return y_lookup(curr_seg.val, minY, maxY);
    }
    long long out = 0;
    if (curr_seg.left_index != nullptr) {
        auto& left_seg = curr_seg.left_index;
        auto& right_seg = curr_seg.right_index;
        if (minX < left_seg->end_x) {
            out = gcd(out, x_lookup(curr_seg.left_index, minX, min(maxX, left_seg->end_x), minY, maxY));
        }
        if (maxX > right_seg->start_x) {
            out = gcd(out, x_lookup(curr_seg.right_index, max(minX, right_seg->start_x), maxX, minY, maxY));
        }
    }
    return out;
}

int updates;
map<pair<int, int>, int> index_lookup;
x_segment *root;

void init(int X, int Y) {
    cnt = static_cast<int>(log2(5000)) + 1;
    empty_y_seg = {0, static_cast<long long>(Y) << cnt, nullptr, nullptr, 0};
//    cout << "0 <= y < " << empty_y_seg.end_y << "\n";
    auto first_empty = new y_segment(empty_y_seg);
    root = new x_segment({0, X, nullptr, nullptr, first_empty});

    updates = 0;
}

void update(int p, int q, long long k) {
    if (index_lookup.find({p, q}) == index_lookup.end()) {
        index_lookup[{p, q}] = updates;
    }
    ++updates;
    x_update(root, p, (static_cast<long long>(q) << cnt) + index_lookup[{p, q}], k);
}

long long calculate(int p, int q, int u, int v) {
    return x_lookup(root, p, u + 1, static_cast<long long>(q) << cnt, (static_cast<long long>(v) + 1LL) << cnt);
}
//
//int main() {
//    init(2, 3);
//    update(0, 0, 20);
//    update(0, 2, 15);
//    update(1, 1, 12);
//    cout << calculate(0, 0, 0, 2) << "\n";
//    cout << calculate(0, 0, 1, 1) << "\n";
//    update(0, 1, 6);
//    update(1, 1, 14);
//    cout << calculate(0, 0, 0, 2) << "\n";
//    cout << calculate(0, 0, 1, 1) << "\n";
//}

int main() {
    int X, Y, N;
    cin >> X >> Y >> N;
    init(X, Y);
    for (int i = 0; i != N; ++i) {
        int op;
        cin >> op;
        if (op == 1) {
            int p, q;
            long long k;
            cin >> p >> q >> k;
            update(p, q, k);
        } else {
            int p, q, u, v;
            cin >> p >> q >> u >> v;
            cout << calculate(p, q, u, v) << "\n";
        }
    }
}
