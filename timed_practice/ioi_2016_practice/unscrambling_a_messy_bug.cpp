#include "bits/stdc++.h"

using namespace std;

vector<int> PERMUTATION;
set<string> dstruct;

void add_element(string x);
void compile_set();
bool check_element(string x);

vector<int> restore_permutation(int N, int W, int R) {
    string x;
    x.resize(N, '0');
    for (int i = 0; i != N; ++i) {
        x[i] = '1';
        add_element(x);
    }
    compile_set();
    string q;
    q.resize(N, '0');
    int chk_cnt = 0;
    vector<int> out(N, -1);
    for (int i = 0; i != N; ++i) {
        for (int j = 0; j != N; ++j) {
            if (q[j] == '1') {
                continue;
            }
            q[j] = '1';
            ++chk_cnt;
            if (chk_cnt > R) {
                exit(1);
            }
            if (check_element(q)) {
                out[j] = i;
                break;
            }
            q[j] = '0';
        }
    }
    return out;
}



//int add_cnt = 0;
//int chk_cnt = 0;
//
//void add_element(string x) {
//    ++add_cnt;
//    dstruct.insert(x);
//}
//
//string scramble(string x) {
//    vector<char> y(x.size());
//    for (int i = 0; i != x.size(); ++i) {
//        y[i] = x[PERMUTATION[i]];
//    }
//    return {y.begin(), y.end()};
//}
//
//void compile_set() {
//    set<string> newset;
//    for (auto x : dstruct) {
//        newset.insert(scramble(x));
//    }
//    swap(dstruct, newset);
//}
//bool check_element(string x) {
//    ++chk_cnt;
//    return dstruct.find(x) != dstruct.end();
//}
//
//int main() {
//    int n, w, r;
//    cin >> n >> w >> r;
//    PERMUTATION = vector<int>(n);
//    for (auto& x : PERMUTATION) {
//        cin >> x;
//    }
//    auto out = restore_permutation(n, w, r);
//    for (auto& x : out) {
//        cout << x << " ";
//    }
//    cout << "\n";
//    cout << add_cnt << ", " << chk_cnt << "\n";
//}
