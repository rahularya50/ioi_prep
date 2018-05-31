#include <vector>
#include <functional>

class Operarray
{
public:
    static long long gcdi(long long x, long long y) {
        if (x > y) {
            return gcdi(y, x);
        }
        // x is less than y
        if (x == 0) { return y; }
        return gcdi(y % x, x);
    }
    static long long lcmu(long long a, long long b) {
        return a * b / gcdi(a, b);
    }
    static long long som(long long x, long long y) { return x + y; }
    static long long maxi(long long x, long long y) { return x > y ? x : y; }
    static long long mini(long long x, long long y) { return x > y ? y : x; }
    // your high order function operArray
    static std::vector<long long> operArray(std::function<long long (long long, long long)> func,
                       std::vector<long long> &arr, long long init) {
          std::vector<long long> out;
          for (int i = 0; i < arr.size(); i++) {
              out.push_back(func(i == 0 ? init : arr[i - 1], arr[i]));
          }
          return out;
    }
};

void testequal(std::vector<long long> ans, std::vector<long long> sol)
{
    std::cout << ans == sol;
}

template<typename Func>
static void dotest(Func func, std::vector<long long> &arr, long long init, std::vector<long long> expected)
{
    testequal(Operarray::operArray(func, arr, init), expected);
}

int main() {
    std::vector<long long> dta = { 18, 69, -90, -78, 65, 40 };
    std::vector<long long> sol = { 18, 3, 3, 3, 1, 1 };
    dotest(Operarray::gcdi, dta, dta[0], sol);
    sol = { 18, 414, 2070, 26910, 26910, 107640 };
    dotest(Operarray::lcmu, dta, dta[0], sol);
    sol = { 18, 69, 69, 69, 69, 69 };
    dotest(Operarray::maxi, dta, dta[0], sol);
    sol = { 18, 18, -90, -90, -90, -90 };
    dotest(Operarray::mini, dta, dta[0], sol);
    sol = { 18, 87, -3, -81, -16, 24 };
    dotest(Operarray::som, dta, 0, sol);

    return 0;
}
