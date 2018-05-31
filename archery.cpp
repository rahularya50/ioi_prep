#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, R;
    double R_raw;

    cin >> N;
    cin >> R_raw;
    R = static_cast<int>(round(R_raw * 10));

    int out = 0;

    for (int i = 0; i != N; ++i)
    {
        double X_raw, Y_raw;
        int X, Y;
        cin >> X_raw >> Y_raw;
        X = static_cast<int>(round(X_raw * 10));
        Y = static_cast<int>(round(Y_raw * 10));

        int r2 = X*X + Y*Y;
        for (int j = 1; j <= 10; ++j)
        {
            int k = 400*j;

            if (r2 <= k*k + R*R + 2*k*R)
            {
                out += (11 - j);
                break;
            }
        }
    }

    cout << out;
    return 0;
}
