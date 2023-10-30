#include <iostream>
#include <numeric>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

namespace unit {
    template<size_t N, typename T>
        requires is_arithmetic_v<T> or is_same_v<T, std::string>
    auto gev(std::vector<T> &v, std::array<T, N> i = {}) {
        assert(size(v) >= N);
        std::transform(begin(i), end(i), begin(v), begin(i), [](auto v1, auto v2) {
            return v1 + v2;
        });
        return i;
    }
}



int main()
{
    using namespace unit;
    vector<double> v {1., 2., 3.};
    vector<string> j{"e", "f", "n"};
    auto [a, b, c] = gev<3>(j);
    auto [a1, a2, a3] = gev<3>(v);
    cout << a << ' ' << b << ' ' << c;
    cout << a1 << ' ' << a2 << ' ' << a3;
}
