/*
ID: rahular1
PROG: ride
LANG: C++14
*/
/* LANG can be C++11 or C++14 for those more recent releases */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int product(const std::string x) {
    int out = 1;
    for (char i : x) {
        out *= (i - 'A' + 1);
    }
    return out % 47;
}

int main() {
    ofstream fout ("ride.out");
    ifstream fin ("ride.in");
    string a, b;
    fin >> a >> b;

    int prod_1, prod_2;
    prod_1 = product(a);
    prod_2 = product(b);

    fout << (prod_1 == prod_2 ? "GO" : "STAY") << endl;
    return 0;
}
