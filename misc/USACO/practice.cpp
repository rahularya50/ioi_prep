#include <bits/stdc++.h>

std::vector< std::vector<int> > permutations(std::set<int>&& elems)
{
    if (elems.size() == 0)
    {
        return {{}};
    }
    std::vector <std::vector<int> > out;
    for (auto iter = elems.begin(); iter != elems.end();)
    {
        auto temp_iter = std::next(iter);
        auto val = *iter;
        elems.erase(iter);
        for (auto x : permutations(elems))
        {
            x.push_back(val);
            out.push_back(x);
        }
        elems.insert(val);
        iter = temp_iter;
    }
    return out;
}

int main()
{
    permutations({1, 2, 3, 4});
}
