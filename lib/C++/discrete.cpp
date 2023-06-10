
// finished time: 2023.6.9
// author: pan__
template<typename T>
class discrete {
public:
    explicit discrete(const vector<T> &p) : arr(p) {
        sort(begin(arr), end(arr));
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
