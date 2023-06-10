
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
    int pos(T val) { return lower_bound(begin(arr), end(arr), val) - begin(arr); }
    int greater(T val) { return lower_bound(begin(arr), end(arr), val+1) - begin(arr); }
    int greater_equal(T val) { return pos(val); }
    int less(T val) { return greater_equal(val) - 1;}
    int less_equal(T val) { return greater(val) - 1; }
    int len() { return length; }
private:
    vector<T> arr;
    int length;
};
