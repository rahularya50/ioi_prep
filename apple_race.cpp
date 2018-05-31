#include <bits/stdc++.h>

using namespace std;

int main() {
    long long N, K;
    cin >> N >> K;
    vector<pair<long long, bool>> A;
    for (long long i = 0; i != N; ++i) {
        char t2;
        cin >> t2;
        long long temp;
        cin >> temp;
        A.push_back({temp, t2 == 'T'});
    }

    vector<long long> P;
    for (long long i = 0; i != K; ++i) {
        long long temp;
        cin >> temp;
        P.push_back(temp - 1);
    }

    map<long long, long long> first_S;
    for (long long i = 0; i != N; ++i) {
        if (!A[i].second && first_S.find(A[i].first) == first_S.end()) {
            first_S[A[i].first] = i;
//            cout << "Setting first_S of " << A[i].first << " to " << i << "\n";
        }
    }

    map<long long, long long> S;
    map<pair<long long, long long>, long long> T;

    long long P_index = 0;
    long long E = 0;
    set<long long> consumed;
    vector<long long> climbed;

    for (long long i = 0; i != N; ++i) {
        if (consumed.find(A[i].first) == consumed.end()) {
            if (A[i].second) {
                if (first_S.find(A[i].first) == first_S.end()) {
                    T[{-1, A[i].first}] = i;
                } else {
                    T[{N - first_S[A[i].first], A[i].first}] = i;
                }
            } else {
                S[A[i].first] = i;
            }
        }

        while (P_index != P.size() && i == P[P_index]) {
            while (consumed.size() < (P_index + 1) && S.size() > 0) {
                auto x = S.begin();
                if (consumed.find((*x).first) == consumed.end()) {
                    consumed.insert((*x).first);
//                    cout << "Consumed " << (*x).first << " at i = " << i << "\n";
                    E += 1;
                    climbed.push_back((*x).second);
                }
                S.erase(x);
            }

            while (consumed.size() < (P_index + 1) && T.size() > 0) {
                auto x = T.begin();
//                cout << "Considering: " << (*x).first.first << " " << (*x).first.second << " " << (*x).second << "\n";
                if (consumed.find((*x).first.second) == consumed.end()) {
                    consumed.insert((*x).first.second);
//                    cout << "Consumed " << (*x).first.second << " at i = " << i << "\n";
                    E += 2;
                    climbed.push_back((*x).second);
                }
                T.erase(x);
            }

            if (consumed.size() < (P_index + 1)) {
                cout << "Lose";
                return 0;
            }

            ++P_index;
        }
    }

    cout << E << " " << climbed.size() << "\n";
    sort(climbed.begin(), climbed.end());
    for (auto x : climbed) {
        cout << (x + 1) << " ";
    }
}
