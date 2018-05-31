#include <bits/stdc++.h>

using namespace std;


double heartArea(double x)
{
//    cout << x << " " << 2.5*x*x << "\n";
    return 2.5*x*x;
}



double solve(double W, double H, int T)
{
//    cout << W << " " << H << " " << T << "\n";
    if (W < H)
        return solve(H, W, T);

    // W > H

    double best_heart = 0;
    pair<double, double> best_residue;


    if (W >= 4*H && heartArea(H) > best_heart)
    {
        best_heart = heartArea(H);
        best_residue = {W - 4*H, H};
    }

    if (W <= 4*H && heartArea(W / 4) > best_heart)
    {
        best_heart = heartArea(W / 4);
        best_residue = {H - W / 4, W};
    }

    if (best_heart < T)
        return 0;

    return best_heart + solve(best_residue.first, best_residue.second, T);
}


int main()
{
    int T, W, H;
    cin >> T;
    cin >> W >> H;

    cout << solve(W, H, T);

    return 0;
}

