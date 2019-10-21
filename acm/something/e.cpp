#include "bits/stdc++.h"

using namespace std;

using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
	ll n, m, l;
  cin >> n >> m >> l;
  vector<pair<ll, ll>> fish(n);
  for (auto& x : fish) {
    cin >> x.first >> x.second;
  }

  vector<pair<ll, int>> order(m);
  for (int i = 0; i != m; ++i) {
    ll x;
    cin >> x;
    order[i] = {x, i};
  }

  sort(order.begin(), order.end());

  vector<ll> pts(m);
  for (int i = 0; i != m; ++i) {
    pts[i] = order[i].first;
  }

  vector<int> deltas(m);
  for (auto x : fish) {
    int xDelta = l - x.second;
    if (xDelta < 0) {
      continue;
    }
    int minX = x.first - xDelta;
    int maxX = x.first + xDelta;
    int minFm = distance(pts.begin(), lower_bound(pts.begin(), pts.end(), minX));
    int maxFm = distance(pts.begin(), upper_bound(pts.begin(), pts.end(), maxX));
    ++deltas[minFm];
    if (maxFm < m) {
      --deltas[maxFm];
    }
    // cout << minX << ", " << minFm << ", " << maxFm << ", " << maxX << "\n";
  }

  vector<int> out(m);

  int run = 0;
  for (int i = 0; i != m; ++i) {
    run += deltas[i];
    out[order[i].second] = run;
  }

  for (auto x : out) {
    cout << x << "\n";
  }
}
