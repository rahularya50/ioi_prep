#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;
    map<int, vector<int>> edges;
    for (int i = 0; i != M; ++I)
    {
        int A, B;
        cin >> A >> B;
        edges[A].push_back(B);
        edges[B].push_back(A);
    }
}
