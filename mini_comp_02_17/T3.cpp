#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;

    vector<long long> A;
    vector<long long> B;

    for (int i = 0; i != N; ++i)
    {
        long long temp1, temp2;
        cin >> temp1 >> temp2;
        A.push_back(temp1);
        B.push_back(temp2);
    }

    vector<long long> f_A;
    for (int i = 0; i != N; ++i)
    {
        long long temp;
        cin >> temp;
        f_A.push_back(temp);
    }

    vector<long long> f_B;
    for (int i = 0; i != N; ++i)
    {
        long long temp;
        cin >> temp;
        f_B.push_back(temp);
    }

    vector<long long> f_delta;  // Gain for each debug rather than rewrite
    for (int i = 0; i != N; ++i)
    {
        f_delta.push_back(f_B[N - 1 - i] - f_A[i]);
    }

    vector<long long> A_minus_B;
    for (int i = 0; i != N; ++i)
    {
        A_minus_B.push_back(A[i] - B[i]);
    }

    sort(A_minus_B.begin(), A_minus_B.end());

    vector<long long> cost_deltas = {0};
    long long sum = 0;

    for (int i = 0; i != N; ++i)
    {
        sum += A_minus_B[i] + f_delta[i];
        cost_deltas.push_back(sum);
    }

    long long out = accumulate(B.begin(), B.end(), static_cast<long long>(0))
               + *min_element(cost_deltas.begin(), cost_deltas.end())
               - accumulate(f_B.begin(), f_B.end(), static_cast<long long>(0));

    cout << out;

    return 0;
}
