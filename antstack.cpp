#include <bits/stdc++.h>

using namespace std;

int go(int index, int target_net_weight, const vector<int>& W, vector<vector<int>>& cache) {
   if (index >= 0 && target_net_weight >= 0 && cache[index][target_net_weight] != -1) {
       return cache[index][target_net_weight];
   }

   if (target_net_weight < 0) {
       return -10000000;
   }

   if (index == -1) {
       return 0;
   }

   auto answer = max(1 + go(index - 1, min(target_net_weight - W[index], W[index] * 6), W, cache), go(index - 1, target_net_weight, W, cache));
   cache[index][target_net_weight] = answer;
   return answer;
}

int main() {
//    ios::sync_with_stdio(false);
   int T;
   cin >> T;
   for (int i = 0; i != T; ++i) {
       int N;
       cin >> N;
       vector<int> W;
//       W.reserve(N);
       for (int j = 0; j != N; ++j) {
           int temp;
           cin >> temp;
           W.push_back(temp);
       }

       vector<vector<int>> cache(N, vector<int>(*max_element(W.begin(), W.end())*7 + 3, -1));
       cout << "Case #" << (i + 1) << ": " << go(N - 1, *max_element(W.begin(), W.end())*7, W, cache) << "\n";
   }
}
