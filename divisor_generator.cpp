#ifdef __cplusplus
extern "C" {
#endif
int isDivisibleBy(int M);
int play(int N);
#ifdef __cplusplus
}
#endif

#include <bits/stdc++.h>

using namespace std;

// TODO: global variables can be declared here

//////
//int isDivisibleBy(int M) {
//    cout << "Is it divisible by " << M << "?\n";
//    string x;
//    cin >> x;
//    return (x == "Y");
//}

long long playHelper(long long N, long long currPrimeIndex, long long known, vector<long long>& primes) {
    for (long long i = currPrimeIndex; i < primes.size() && primes[i] * known <= N; ++i) {
        if (isDivisibleBy(known * primes[i])) {
            return playHelper(N, i, known * primes[i], primes);
        }
    }
    return known;
}


int play(int N) {
  if (N == 1) {
    return 1;
  }
  vector<bool> isPrime (N + 1, true);
  for (long long i = 2; i * i <= N; ++i) {
    if (!isPrime[i]) {
        continue;
    }
    for (long long j = i * 2; j <= N; j += i) {
        isPrime[j] = false;
    }
  }

  vector<long long> primes;
  for (long long i = 2; i <= N; ++i) {
    if (isPrime[i]) {
        primes.push_back(i);
    }
  }

  return playHelper(N, 0, 1, primes);
}
////
//int main() {
//    cout << play(2);
//}
