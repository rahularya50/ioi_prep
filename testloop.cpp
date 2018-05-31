#include <vector>
#include <iostream>

int main()
{
    std::vector<int> v = {1, 3, 5, 7, 9};

    for (auto x : v)
        std::cout << x << ' ';
}
