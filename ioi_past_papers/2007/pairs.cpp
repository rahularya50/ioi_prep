#include <bits/stdc++.h>

using namespace std;

struct y_tree {
    int s;
    int e;
    y_tree *l;
    y_tree *r;
    int val;
};

struct y_tree {
    int s;
    int e;
    y_tree *l;
    y_tree *r;
    b_tree *val;
};

struct y_tree {
    int s;
    int e;
    y_tree *l;
    y_tree *r;
    a_tree *val;
};

struct x_tree {
    int s;
    int e;
    x_tree *l;
    x_tree *r;
    y_tree *val;
};

int B, N, D, M;

int lim;

void update(int y, y_tree *tree) {
    ++(tree->val);
    if (tree->e - tree->s == 1) {
        return;
    }
    int mid_pos = (tree->s + tree->e) / 2;
    if (y < mid_pos) {
        if (tree->l == nullptr) {
            tree->l = new y_tree({tree->s, mid_pos, nullptr, nullptr, 0});
        }
        update(y, tree->l);
    } else {
        if (tree->r == nullptr) {
            tree->r = new y_tree({mid_pos, tree->e, nullptr, nullptr, 0});
        }
        update(y, tree->r);
    }

}

void update(int x, int y, x_tree *tree) {
    update(y, tree->val);
    if (tree->e - tree->s == 1) {
        return;
    }
    int mid_pos = (tree->s + tree->e) / 2;
    if (x < mid_pos) {
        if (tree->l == nullptr) {
            tree->l = new x_tree({tree->s, mid_pos, nullptr, nullptr, nullptr});
            tree->l->val = new y_tree({-lim, lim, nullptr, nullptr, 0});
        }
        update(x, y, tree->l);
    } else {
        if (tree->r == nullptr) {
            tree->r = new x_tree({mid_pos, tree->e, nullptr, nullptr, nullptr});
            tree->r->val = new y_tree({-lim, lim, nullptr, nullptr, 0});
        }
        update(x, y, tree->r);
    }
}

int query(int minY, int maxY, y_tree *tree) {
    if (minY <= tree->s && maxY >= tree->e) {
        return tree->val;
    }
    int out = 0;
    int mid_pos = (tree->s + tree->e) / 2;
    if (minY < mid_pos && tree->l != nullptr) {
        out += query(minY, min(mid_pos, maxY), tree->l);
    }
    if (maxY > mid_pos && tree->r != nullptr) {
        out += query(max(mid_pos, minY), maxY, tree->r);
    }
    return out;
}

int query(int minX, int maxX, int minY, int maxY, x_tree *tree) {
    if (minX <= tree->s && maxX >= tree->e) {
        return query(minY, maxY, tree->val);
    }
    int out = 0;
    int mid_pos = (tree->s + tree->e) / 2;
    if (minX < mid_pos && tree->l != nullptr) {
        out += query(minX, min(mid_pos, maxX), minY, maxY, tree->l);
    }
    if (maxX > mid_pos && tree->r != nullptr) {
        out += query(max(mid_pos, minX), maxX, minY, maxY, tree->r);
    }
    return out;
}

int query(int minX, int maxX, int minY, int maxY, int minA, int maxA, int minB, int maxB, x_tree *tree) {
    if (minY <= tree->s && maxY >= tree->e) {
        return query(minY, maxY, tree->val);
    }
    int out = 0;
    int mid_pos = (tree->s + tree->e) / 2;
    if (minX < mid_pos && tree->l != nullptr) {
        out += query(minX, min(mid_pos, maxX), minY, maxY, tree->l);
    }
    if (maxX > mid_pos && tree->r != nullptr) {
        out += query(max(mid_pos, minX), maxX, minY, maxY, tree->r);
    }
    return out;
}

int query(int minX, int maxX, int minY, int maxY, int minA, int maxA, int minB, int maxB, x_tree *tree) {
    if (minX <= tree->s && maxX >= tree->e) {
        return query(minY, maxY, minA, maxA, minB, maxB, tree->val);
    }
    int out = 0;
    int mid_pos = (tree->s + tree->e) / 2;
    if (minX < mid_pos && tree->l != nullptr) {
        out += query(minX, min(mid_pos, maxX), minY, maxY, minA, maxA, minB, maxB, tree->l);
    }
    if (maxX > mid_pos && tree->r != nullptr) {
        out += query(max(mid_pos, minX), maxX, minY, maxY, minA, maxA, minB, maxB, tree->r);
    }
    return out;
}

int main() {
    cin >> B >> N >> D >> M;
    if (B == 1) {
        vector<int> animals(N);
        for (auto& x : animals) {
            cin >> x;
        }
        sort(animals.begin(), animals.end());
        long long p1 = 0;
        long long p2 = 0;
        long long out = 0;
        while (p1 != animals.size()) {
            while (p2 != animals.size() && animals[p1] + D >= animals[p2]) {
                ++p2;
            }
            out += (p2 - p1 - 1LL);
            ++p1;
        }
        cout << out;
        return 0;
    } else if (B == 2) {
        vector<pair<int, int>> animals(N);
        for (auto& x : animals) {
            cin >> x.first >> x.second;
            --x.first;
            --x.second;
        }
        lim = 1LL << ((int)log2(M) + 2);
        auto y = new y_tree({-lim, lim, nullptr, nullptr, 0});
        auto x = new x_tree({-lim, lim, nullptr, nullptr, y});
        for (auto a : animals) {
            update(a.first + a.second, a.first - a.second, x);
        }
        long long out = 0;
        for (auto a : animals) {
            long long q = query(a.first + a.second - D, a.first + a.second + D + 1, a.first - a.second - D, a.first - a.second + D + 1, x);
//            cout << q << "\n";
            out += q - 1LL;
        }
        cout << out / 2;
        return 0;
    }
}
