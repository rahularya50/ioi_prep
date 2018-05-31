#include <bits/stdc++.h>

using namespace std;

int main() {
   long long A, B, C, D;
   cin >> A >> B >> C >> D;

   long long out = 0;
   out += B; // Making small hearts
   out += C; // Making large hearts
   out += D*2 + max((long long)0, (long long)ceil((A - D*2) / 2.0));

   cout << out;

   return 0;
}
