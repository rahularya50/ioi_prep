#include <bits/stdc++.h>

using namespace std;


bool explore(int index, set<int>& outfits, vector<int>& seq, const vector< vector<int> >& vals)
{
    if (index == vals.size())
    {
        for (int i = 0; i != vals.size(); ++i)
        {
            cout << vals[i][seq[i]] << "\n";
        }
        return true;
    }
    std::vector<int> order;
    if (vals[index][0] > vals[index][1])
    {
        order = {1, 0};
    }
    else
    {
        order = {0, 1};
    }

    for (int x: order)
    {
        if (outfits.find(vals[index][x]) == outfits.end())
        {
            outfits.insert(vals[index][x]);
            seq.push_back(x);
            if (explore(index + 1, outfits, seq, vals))
            {
                return true;
            }
            outfits.erase(vals[index][x]);
            seq.pop_back();
        }
    }
    return false;
}


int main()
{
    int N;
    cin >> N;
    if (N > 31)
    {
        cout << "Impossible";
        return 0;
    }
    vector< vector<int> > vals;
    for (int i = 0; i != N; ++i)
    {
        int m_i, d_i;
        cin >> m_i >> d_i;
        vals.push_back({m_i, d_i});
    }

    int index = 0;
    set<int> outfits;

    std::vector<int> thing;

    if (!explore(index, outfits, thing, vals))
    {
        cout << "Impossible";
        return 0;
    }
}
