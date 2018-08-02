#include <bits/stdc++.h>

using namespace std;

struct y_segment {
    long long val;
    y_segment *left;
    y_segment *right;
    long long low;
    long long high;
};

struct x_segment {
    y_segment *val;
    x_segment *left;
    x_segment *right;
    long long low;
    long long high;
};

long long R, C, N;

long long SHIFT;

long long gcd(long long x, long long y) {
    if (y > x) {
        return gcd(y, x);
    }
    // x >= y
    if (y == 0) {
        return x;
    }
    return gcd(y, x % y);
}

void y_update(y_segment *segment, long long y, long long val) {
    auto mid = (segment->low + segment->high) / 2;

    if (segment->low + 1 >= segment->high) {
//        cout << "y_seg (" << segment->low << " <= y < " << segment->high << ") = " << val << "\n";
        segment->val = val;
        return;
    }

    if (y < mid) {
        if (segment->left == nullptr) {
            auto new_y = new y_segment({0, nullptr, nullptr, segment->low, mid});
            segment->left = new_y;
        }
        y_update(segment->left, y, val);
    } else {
        if (segment->right == nullptr) {
            auto new_y = new y_segment({0, nullptr, nullptr, mid, segment->high});
            segment->right = new_y;
        }
        y_update(segment->right, y, val);
    }

    long long out = 0;
    if (segment->left != nullptr) {
        out = gcd(out, segment->left->val);
    }

    if (segment->right != nullptr) {
        out = gcd(out, segment->right->val);
    }

//    cout << "y_seg (" << segment->low << " <= y < " << segment->high << ") = " << out << "\n";
    segment->val = out;
}

void x_update(x_segment *segment, long long x, long long y, long long val) {
//    cout << "Entering " << segment->low << " <= x < " << segment->high << "\n";
    y_update(segment->val, y, val);

    if (segment->low + 1 >= segment->high) {
        return;
    }

    auto mid = (segment->low + segment->high) / 2;

    if (x < mid) {
        if (segment->left == nullptr) {
            auto new_y = new y_segment({0, nullptr, nullptr, 0, R << SHIFT});
            auto new_x = new x_segment({new_y, nullptr, nullptr, segment->low, mid});
            segment->left = new_x;
        }
        x_update(segment->left, x, y, val);
    } else {
        if (segment->right == nullptr) {
            auto new_y = new y_segment({0, nullptr, nullptr, 0, R << SHIFT});
            auto new_x = new x_segment({new_y, nullptr, nullptr, mid, segment->high});
            segment->right = new_x;
        }
        x_update(segment->right, x, y, val);
    }

}

long long y_lookup(y_segment *segment, long long minY, long long maxY) {
//    cout << "y_seg (" << segment->low << " <= y < " << segment->high << ")" << "\n";
    if (minY <= segment->low && segment->high <= maxY) {
        return segment->val;
    }

    if (minY >= segment->high) {
        return 0;
    }

    if (maxY <= segment->low) {
        return 0;
    }

    auto mid = (segment->low + segment->high) / 2;

    long long out = 0;

    if (segment->left != nullptr && minY < mid) {
        out = gcd(out, y_lookup(segment->left, minY, min(mid, maxY)));
    }

    if (segment->right != nullptr && maxY > mid) {
        out = gcd(out, y_lookup(segment->right, max(minY, mid), maxY));
    }

    return out;
}


long long x_lookup(x_segment *segment, long long minX, long long maxX, long long minY, long long maxY) {
//    cout << "Entering " << segment->low << " <= x < " << segment->high << "\n";
    if (minX <= segment->low && segment->high <= maxX) {
        return y_lookup(segment->val, minY, maxY);
    }

    auto mid = (segment->low + segment->high) / 2;

    long long out = 0;

    if (segment->left != nullptr && minX < mid) {
        out = gcd(out, x_lookup(segment->left, minX, min(mid, maxX), minY, maxY));
    }

    if (segment->right != nullptr && maxX > mid) {
        out = gcd(out, x_lookup(segment->right, max(minX, mid), maxX, minY, maxY));
    }

    return out;
}

map<pair<long long, long long>, long long> offsets;
x_segment *x_root;

void init(int r, int c) {
    R = r;
    C = c;
    SHIFT = 18;

    auto y_def = new y_segment({0, nullptr, nullptr, 0, R << SHIFT});
    x_root = new x_segment({y_def, nullptr, nullptr, 0, C});
}

void update(long long y, long long x, long long val) {
    long long fuzz = offsets.size();
    if (offsets.find({x, y}) != offsets.end()) {
        fuzz = offsets[{x, y}];
    } else {
        offsets[{x, y}] = fuzz;
    }
    x_update(x_root, x, (y << SHIFT) + fuzz, val);
}

long long calculate(long long minY, long long minX, long long maxY, long long maxX) {
    ++maxX;
    ++maxY;
    return x_lookup(x_root, minX, maxX, minY << SHIFT, maxY << SHIFT);
}

int main() {
    cin >> R >> C >> N;
    init(R, C);

    for (long long i = 0; i != N; ++i) {
        long long a;
        cin >> a;
        if (a == 1) {
            long long x, y, val;
            cin >> y >> x >> val;
            update(y, x, val);
        } else {
            long long minX, maxX, minY, maxY;
            cin >> minY >> minX >> maxY >> maxX;
            cout << calculate(minY, minX, maxY, maxX) << "\n";
        }
    }
}

//long long main() {
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
