#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;
    vector<long long> A;
    for (int i = 0; i != N; ++i)
    {
        long long temp;
        cin >> temp;
        A.push_back(temp);
    }

    int first = 0;
    int last = 0;

    map<long long, int> counts;
    vector<int> leaps;
    int distincts = 0;

    while (true)
    {
//        cout << "First: " << first << " Last: " << last << " Distincts: " << distincts << "\n";
        if (distincts < M && last < N)
        {
            if (counts.find(A[last]) == counts.end())
            {
                counts[A[last]] = 0;
                distincts += 1;
            }
            counts[A[last]] += 1;
            last += 1;
        }
        else if (first < N && distincts >= M)
        {
            leaps.push_back(last);
            counts[A[first]] -= 1;
            if (counts[A[first]] == 0)
            {
                distincts -= 1;
                counts.erase(counts.find(A[first]));
            }
            first += 1;
        }
        else
        {
            for (int i = first; i != N; ++i)
            {
                leaps.push_back(N + 1);
            }
            break;
        }
    }

    vector<long long> cumulatives = {0};
    long long test = 0;

    for (auto x: leaps)
    {
        test += x;
        cumulatives.push_back(test);
//        cout << test << " ";
    }

//    cout << "\n";

    int K;
    cin >> K;

    for (int i = 0; i != K; ++i)
    {
        int L, R;
        cin >> L >> R;

        L -= 1;
        R -= 1;

        if (leaps[L] > R + 1)
        {
            cout << 0 << "\n";
            continue;
        }

        int min_pos = L;
        int max_pos = R;

        while (min_pos < max_pos)
        {
            auto mean = (min_pos + max_pos + 1) / 2;
            if (leaps[mean] > R + 1)
            {
                max_pos = mean - 1;
            }
            else
            {
                min_pos = mean;
            }
        }

        long long num = min_pos - L + 1;

        long long out = num * (R + 2) + cumulatives[L] - cumulatives[min_pos + 1];
//        cout << "Out " << out << " L: " << L << " R: " << R << " Mean: " << min_pos << " Num: " << num << "\n";


//        for (int j = L; j <= R; ++j)
//        {
//            if (leaps[j] == -1 || j + leaps[j] > R + 1)
//            {
//                continue;
//            }
//
//            out += R - (j + leaps[j] - 1) + 1;
//        }
        cout << out << "\n";
    }

    return 0;
}
