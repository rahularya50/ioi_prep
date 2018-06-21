#include <bits/stdc++.h>

static int moves, TT, NN, prev = -1;

int HC(int N);

int Guess(int x){
   int r;
   if (prev == -1 || abs(x-TT) == abs(prev-TT)) r = 0;
   else if (abs(x-TT) > abs(prev-TT)) r = -1;
   else r = 1;
   prev = x;
   if (x < 1 || x > NN) exit(92);
   moves++;
   return r;
}

int main(){
   int n=0,i,t,OK=0,sub1=0,sub2=0,sub3=0;
   double worst = 999999;
   while (2 == scanf("%d%d",&NN,&TT)) {
      if (NN > n) n = NN;
      prev = -1;
      moves = 0;
      int h = HC(NN);
      std::cout << "Returned: " << h << "\n";
      if (h != TT) {
         exit(91);
      }
      int W = floor(0.00001+log(3*NN)/log(2));
      double alpha = 2 - (double)moves/W;
      if (alpha < worst) worst = alpha;
       // 1 means failure
      if ( NN <= 500 && moves > 500 ) exit(93);
      if ( NN <= 500 && moves > 18 ) sub2=1;
      if ( NN <= 500 && moves > 16 ) sub3=1;
      OK++;
     std::cout << "done!";
   }
   if (!sub1) printf("OK 1\n");
   if (!sub2) printf("OK 2\n");
   if (!sub3) printf("OK 3\n");
   if (worst > 0) printf("OK 4 alpha %0.2lf\n",worst);
   return 0;
}

using namespace std;

int HC(int N) {
    if (N == 1) {
        return 1;
    }
    int low = 1;
    int high = N;
    int prev = max(1, N / 2 - 1);
    int target = min(N, prev + 2);
    Guess(prev);
    int x = Guess(target);
    prev = target;
    if (x == 0 && prev != target) {
        return (prev + target) / 2;
    } else if (x == 1) {
        low = (prev + target) / 2;
    } else {
        high = (prev + target) / 2;
    }
    while (low != high) {
//        cout << low << " <= x <= " << high << "\n";
        int target = (low + high) - prev;
        if (target < 1) {
            target = 1;
        }
        if (target > N) {
            target = N;
        }
        int realMid = (prev + target) / 2;
//        cout << prev << ", " << target << "\n";
        auto x = Guess(target);
//        cout << "Received " << x << "\n";
        if (x == 0) {
            return realMid;
        } else if ((x == 1) != (target > prev)) {
            high = (prev + target - 1) / 2;
        } else {
            low = (prev + target + 2) / 2;
        }
        prev = target;
    }
    return low;
}
