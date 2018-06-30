#include <bits/stdc++>

using namespace std;

struct ninja
{
    int boss;
    int salary;
    int leadership;
};

int main()
{
    int N, M;
    cin >> N >> M;

    vector<ninja> ninjas;
    for (int i = 0; i != N; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        ninjas.push_back({a, b, c});
    }


}
