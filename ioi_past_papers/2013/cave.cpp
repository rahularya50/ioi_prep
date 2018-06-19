#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5001;
int doorsOpened[MAXN];
int placement[MAXN];
int state[MAXN];
int N;
int numTries = 0;

//void answer(int S[], int D[]) {
//        for (int a = 0; a < N; a++) {
//                if (S[a] != state[a] || D[a] != placement[a]) {
//                        printf("INCORRECT TRY USING %i TRIES\n", numTries);
//                        exit(0);
//                }
//        }
//        printf("ANSWER CORRECT USING %i TRIES\n", numTries);
//        exit(0);
//}
//
//
//int tryCombination(int S[]) {
//        std::fill(doorsOpened, doorsOpened + MAXN, 0);
//
//        for (int a = 0; a < N; a++) {
//                //printf("%i ", S[a]);
//                doorsOpened[placement[a]] = (S[a] == state[a]);
//        }
//        //printf("\n");
//        for (int a = 0; a < N; a++) {
//                //printf("%i ", doorsOpened[a]);
//        }
//        //printf("\n");
//
//        numTries++;
//        for (int a = 0; a < N; a++) {
//                if (!doorsOpened[a]) {
//                        //printf("ret @ %i\n", a);
//                        return a;
//                }
//        }
//        //printf("ret >%i\n", N);
//        return -1;
//}

void exploreCave(int n) {
    N = n;
    int S[N];
    for (int i = 0; i != N; ++i) {
        S[i] = 0;
    }
    vector<int> mapping(N, -1);
    for (int i = 0; i != N; ++i) {
        for (int i = 0; i != N; ++i) {
            if (mapping[i] == -1) {
                S[i] = 0;
            }
        }
        int openVal = 0;
        auto x = tryCombination(S);
//        cout << "got " << x << "\n";
        if (x == i) {
            openVal = 1;
        }
//        cout << "Switch should be set to " << openVal << " to open " << i << "\n";
        int low = 0;
        int high = N;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            for (int i = 0; i != N; ++i) {
                if (mapping[i] != -1) {
                    continue;
                }
                if (low <= i && i < mid) {
                    S[i] = openVal;
                } else {
                    S[i] = 1 - openVal;
                }
            }
            auto y = tryCombination(S);
            if (y == i) {
                // ith is not open
                low = mid;
            } else {
                // ith is open
                high = mid;
            }
        }
        mapping[low] = i;
//        cout << "Switch " << low << " opens " << i << "\n";
        S[low] = openVal;
    }
    answer(S, mapping.data());
}
//
//int main() {
//    // 4
//    // 2 1 3 0
//    // 1 1 1 0
//        scanf("%i", &N);
//        for (int a = 0; a < N; a++) {
//                scanf("%i", &placement[a]); //enter order of switches from 0...N - 1
//        }
//        for (int a = 0; a < N; a++) {
//                scanf("%i", &state[a]); //please only enter 1 or 0 here, otherwise you screw yourself up
//        }
//        exploreCave(N);
//        printf("Your program forgot to call answer(int S[], int D[])");
//}
