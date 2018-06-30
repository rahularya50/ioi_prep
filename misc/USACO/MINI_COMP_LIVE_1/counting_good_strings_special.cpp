long long go(int x)
{

}

int main()
{
    int N, M, K;
    string S, T;
    cin >> N >> M >> K >> S >> T;
    vector<int> groups;
    int c = 0;
    for (auto x: S)
    {
        if (x == '?')
        {
            c += 1;
        }
        else if (c != 0)
        {
            groups.push_back(c);
            c = 0;
        }
    }
    groups.push_back(c);

    long long out = 1;
    for (auto x: groups)
    {
        out *= go(x);
        out %= (1e9 + 7);
    }
    cout << out;
}
