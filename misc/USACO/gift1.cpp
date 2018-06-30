/*
ID: rahular1
PROG: gift1
LANG: C++14
*/
/* LANG can be C++11 or C++14 for those more recent releases */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <map>
#include <vector>

using namespace std;

int main() {
    ofstream fout ("gift1.out");
    ifstream fin ("gift1.in");

    int N;

    fin >> N;

    map<string, int> accounts;
    vector<string> names;

    for (int i = 2; i <= N + 2; ++i) {
        string name;
        fin >> name;
        accounts[name] = 0;
        names.push_back(name);
    }

    string name;

    while (fin >> name) {
        int amount, num_giftees;
        fin >> amount >> num_giftees;

        auto temp = div(amount, num_giftees);
        auto quot = temp.quot;
        auto rem = temp.rem;

        accounts[name] = rem;

        for (int i = 0; i < num_giftees; ++i) {
            std::string person;
            fin >> person;
            accounts[person] -= quot;
        }
    }

    for (string name : names) {
        fout >> name >> " " >> accounts[name] >> endl;
    }







    return 0;
}

