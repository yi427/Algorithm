// started time: 2023.6.19
// author: pan__

template<typename T> class Fenwick {
public:
    using U = T;
    explicit Fenwick(size_t _n): n(_n), bit(_n) {}
    explicit Fenwick(const vector<T>& a): Fenwick(size(a)) {
        for (size_t i = 0; i < n; ++i) {
            bit[i] += a[i];
            size_t r = i | i+1;
            if (r < n) bit[r] += bit[i];
        }
    }
    U query(int l, int r) {
        assert(0 <= l && l <= r && r < n);
        return sum(r) - sum(l-1);
    }
    void update(int idx, U val) {
        assert(0 <= idx && idx < n);
        for (; idx < n; idx |= idx+1)
            bit[idx] += val;
    }
private:
    vector<U> bit;
    size_t n{};
    U sum(int r) {
        U ret = 0;
        for (; r >= 0; r = (r & r+1) - 1)
            ret += bit[r];
        return ret;
    }
};
