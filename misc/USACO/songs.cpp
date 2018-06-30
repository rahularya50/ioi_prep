#include <bits/stdc++.h>

using namespace std;

int main()
{
    int A, B, N;
    cin >> A >> B >> N;
    set<int> song;
    for (int i = 0; i != A; ++i)
    {
        int temp;
        cin >> temp;
        song.insert(temp);
    }

    set<int> notes;
    for (int i = 0; i != B; ++i)
    {
        int temp;
        cin >> temp;
        notes.insert(temp);
    }

//    cout << *notes.lower_bound(N) << "\n";

    for (auto x = notes.lower_bound(N); x != notes.end(); ++x)
    {
        int delta = *x - N;
//        cout << "Delta: " << delta << "\n";
        for (auto y: song)
        {
            if (notes.find(y + delta) == notes.end())
            {
//                cout << y << "\n";
                goto fail;
            }
        }
        cout << delta;
        return 0;

        fail:
            continue;
    }
    cout << "Impossible";
    return 0;
}
