#include <bits/stdc++.h>

using namespace std;

const int NONE = 2000000000;

int go(int pos, int Mval, int Nval, vector<int>& M, vector<int>&N, unordered_map<int, unordered_set<pair<int, int>>>& sets,
       unordered_map<pair<int, pair<int, int>>, int>& cache) {

//    cout << "Considering seq starting at " << pos << " with M = " << Mval << " and N = " << Nval << ".\n";

    if (cache.find({pos, {Mval, Nval}}) != cache.end()) {
        return cache[{pos, {Mval, Nval}}];
    }

    if (pos == M.size()) {
        return 0;
    }

    if (Mval != NONE && Nval != NONE) {
        if (M[pos] != Mval && N[pos] != Nval) {
            cache[{pos, {Mval, Nval}}] = 0;
//            cout << "Fail at pos = " << pos << " with M = " << M[pos] << " != " << Mval << " OR N = " << N[pos] << " != " << Nval << ".\n";
            return 0;
        }
        else {
            int temp = go(pos + 1, Mval, Nval, M, N, sets, cache) + 1;
            cache[{pos, {Mval, Nval}}] = temp;
            sets[temp].insert({pos, pos + temp});
            return temp;
        }
    }

    if (Mval == NONE && Nval != NONE) {
        if (N[pos] == Nval) {
            int temp = go(pos + 1, Mval, Nval, M, N, sets, cache) + 1;
            cache[{pos, {Mval, Nval}}] = temp;
            sets[temp].insert({pos, pos + temp});
            return temp;
        }
        else {
            int temp = go(pos + 1, M[pos], Nval, M, N, sets, cache) + 1;
            cache[{pos, {Mval, Nval}}] = temp;
            sets[temp].insert({pos, pos + temp});
//            cout << pos << " " << temp << "\n";
            return temp;
        }
    }

    if (Nval == NONE && Mval != NONE) {
        if (M[pos] == Mval) {
            int temp = go(pos + 1, Mval, Nval, M, N, sets, cache) + 1;
            cache[{pos, {Mval, Nval}}] = temp;
            sets[temp].insert({pos, pos + temp});
            return temp;
        }
        else {
            int temp = go(pos + 1, Mval, N[pos], M, N, sets, cache) + 1;
            cache[{pos, {Mval, Nval}}] = temp;
            sets[temp].insert({pos, pos + temp});
            return temp;
        }
    }

    // ELSE

    int temp1 = go(pos + 1, M[pos], Nval, M, N, sets, cache) + 1;
    sets[temp1].insert({pos, pos + temp1});

    int temp2 = go(pos + 1, Mval, N[pos], M, N, sets, cache) + 1;
    sets[temp2].insert({pos, pos + temp2});

    int temp3 = go(pos + 1, Mval, Nval, M, N, sets, cache);

    cache[{pos, {Mval, Nval}}] = max({temp1, temp2, temp3});

//    cout << "Seq identified from " << pos << " to " << pos + max({temp1, temp2, temp3}) << "\n";

    return max({temp1, temp2, temp3});
}




int main() {
    int T;
    cin >> T;
    for (int i = 0; i != T; ++i) {
        int S;
        cin >> S;
        vector<int> M;
        vector<int> N;
        for (int j = 0; j != S; ++j)
        {
            int D, A, B;
            cin >> D >> A >> B;
            M.push_back(D + A);
            N.push_back(D - B);
        }

        unordered_map<int, set<pair<int, int>>> sets;
        unordered_map<pair<int, pair<int, int>>, int> cache;
        int out = go(0, NONE, NONE, M, N, sets, cache);
        cout << "Case #" << (i + 1) << ": " << out << " " << sets[out].size() << "\n";
    }
}
