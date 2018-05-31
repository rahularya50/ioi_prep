#include <bits/stdc++.h>

using namespace std;


void dump(vector<vector<string>>& buffer, string& out)
{
    for (auto& x: buffer)
    {
        for (auto& y: x)
        {
            if (out != "" && out.back() != ' ')
                out.push_back(' ');
            out.insert(out.end(), y.begin(), y.end());
        }
    }
    buffer = {};
}

string needed(vector<vector<string>>& buffer)
{
    if (buffer.size() == 0)
        return "";

    string last = buffer.back().back();

    if (last == "I")
        return "love";
    if (last == "love")
        return "you";
}

void clean(vector<vector<string>>& buffer)
{
    while (buffer.size() > 0 && buffer.back().size() == 3)
    {
        buffer.pop_back();
    }
}

int main()
{
    string text;
    getline(cin, text);

    vector<vector<string>> sentences;
    vector<string> temp;
    string curr_word;

    for (auto x: text)
    {
        if ((x == '.' || x == ' ') && curr_word != "")
        {
            temp.push_back(curr_word);
            curr_word = "";
        }
        if (x == '.' && temp.size() > 0)
        {
            sentences.push_back(temp);
            temp = {};
        }
        if (x != '.' && x != ' ')
        {
            curr_word.push_back(x);
        }
    }

    string out = "";

    for (auto& sentence: sentences)
    {
        vector<vector<string>> buffer;
        bool nonempty = false;

        for (auto& word: sentence)
        {
//            cout << "Reading: \"" << word << "\"\n";
            if (word != "I" && word != needed(buffer))
            {
                nonempty = true;
                dump(buffer, out);
                if (out != "" && out.back() != ' ')
                    out.push_back(' ');
                out.insert(out.end(), word.begin(), word.end());
            }
            else if (word == "I")
            {
                buffer.push_back({"I"});
            }
            else if (word == needed(buffer))
            {
                buffer.back().push_back(word);
                clean(buffer);
            }
        }

        if (buffer.size() > 0)
            nonempty = true;

        if (nonempty)
        {
            dump(buffer, out);
            out.push_back('.');
            out.push_back(' ');
        }
    }

    cout << out;

    return 0;
}
