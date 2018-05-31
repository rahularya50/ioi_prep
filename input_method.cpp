#include <bits/stdc++.h>

using namespace std;

int main()
{
//    while (true) {
    int N, L, W;
    cin >> N >> L;
    vector<string> dictionary;
    for (int i = 0; i != N; ++i)
    {
        string temp;
        cin >> temp;
        dictionary.push_back(temp);
    }
    cin >> W;
    vector<string> sentence;
    for (int i = 0; i != W; ++i)
    {
        string temp;
        cin >> temp;
        sentence.push_back(temp);
    }
    map<string, string> lookup;
    for (auto word: dictionary)
    {
        for (int i = 0; i != L; ++i)
        {
            lookup.insert({word.substr(0, i) + "_" + word.substr(i + 1), word});
//            cout << word.substr(0, i) + "_" + word.substr(i + 1) << "\n";
        }
    }
    for (auto word: sentence)
    {
        bool flag = true;

        for (int i = 0; i != L; ++i)
        {
            auto temp = word[i];
            word[i] = '_';

            cout << "Trial: " << word << "\n";

            if (lookup.find(word) != lookup.end() && temp != lookup[word][i])
            {
                cout << lookup[word] << "\n";
                flag = false;
                break;
            }

            word[i] = temp;
        }
        while (flag) {}
    }
//    }
}
