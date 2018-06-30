#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

int main(){
    int N, score = 0;
    double x, y, R;
    cin >> N;
    cin >> R;
    for(int i = 0; i < N; ++i){
        cin >> x;
        cin >> y;

        cout << "Received: " << x << " " << y << "\n";
        double hi = sqrt(x * x + y * y) - R;
        const double dist = sqrt(hi * hi);

        if(dist <= 400){
            int ring = ceil(dist / 40.0);
            int n = 11 - ring;
            score += n;
        }
//        cout << "Hey lilian: " << dist << endl;
    }
    cout << score;
}
