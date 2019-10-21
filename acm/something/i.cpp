#include "bits/stdc++.h"

using namespace std;

long long dp[150];

using ll = long long;

long long go(long long i, vector<long long>& seq) {
  if (dp[i] != -1) {
    return dp[i];
  }
  long long N = seq.size();
  long long cnt = 0;
  long long min_found = 1000;
  for (long long j = i + 1; j != N; ++j) {
    if (seq[j] < seq[i]) {
      continue;
    }
    if (seq[j] < min_found) {
      cnt += go(j, seq);
      min_found = seq[j];
    }
  }
  if (cnt == 0) {
    cnt = 1;
  }
  dp[i] = cnt;
  return cnt;
}

int main() {
  memset(dp, -1, 150);

	long long N, M;
  cin >> N >> M;
  vector<long long> offsets(N);
  for (long long i = 0; i != M; ++i) {
    long long a, b;
    cin >> a >> b;
    --a;
    --b;
    if (a < b) {
      --offsets[b];
      ++offsets[a];
    } else {
      ++offsets[b];
      --offsets[a];
    }
  }

  vector<long long> seq(N);
  for (long long i = 0; i != N; ++i) {
    seq[i] = i + offsets[i];
  }
  //
  // for (auto x : seq) {
  //   cout << x << ", ";
  // }
  // cout << endl;

  // num of maximal longest increasung subsequences
  long long run_min = N + 5;
  vector<long long> starts;
  for (long long i = 0; i != N; ++i) {
    if (seq[i] < run_min) {
      starts.push_back(i);
    }
    run_min = min(run_min, seq[i]);
  }

  long long out = 0;
  for (auto x : starts) {
    out += go(x, seq);
  }
  //
  // for (long long i = 0; i != N; ++i) {
  //   cout << "dp[" << i << "] = " << dp[i] << endl;
  // }

  cout << out << endl;
}
