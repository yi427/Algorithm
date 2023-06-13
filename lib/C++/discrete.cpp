#include <vector>
#include <iostream>
#include <functional>

// start time: 2023.6.9
// author: pan__
using namespace std;

template<typename T>
class discrete {
public:
    template<class _f = function<bool(T, T)>>
    explicit discrete(const vector<T> &p, _f com = std::less<T>()) : arr(p) {
        sort(begin(arr), end(arr), com);
        arr.resize(unique(begin(arr), end(arr)) - begin(arr));
        this->length = size(arr);
    }

    [[nodiscard]] int pos(T val) const { return lower_bound(begin(arr), end(arr), val) - begin(arr); }

    [[nodiscard]] int greater(T val) const { return lower_bound(begin(arr), end(arr), val + 1) - begin(arr); }

    [[nodiscard]] int greater_equal(T val) const { return pos(val); }

    [[nodiscard]] int less(T val) const { return greater_equal(val) - 1; }

    [[nodiscard]] int less_equal(T val) const { return greater(val) - 1; }

    [[nodiscard]] int len() const { return length; }

    [[nodiscard]] T get(int p) const { return arr[p]; }

private:
    vector<T> arr;
    int length;
};

int main()
{
    // [[nodiscard]] 的意思是这个值不允许被丢弃，换句话说，当你调用这个函数的时候，你肯定需要用到返回值，如果你没有用到，肯定是哪里写错了。
    vector v{100, 900, 1000, 10};
    // default compare is the std::less<T>()
    discrete d(v, [](auto x, auto y) { return x > y; });
    for (int i = 0; i < d.len(); ++i)
        cout << d.get(i) << ' ';
    return 0;
}
