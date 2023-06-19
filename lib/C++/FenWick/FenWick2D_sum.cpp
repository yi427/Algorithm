// started time: 2023.6.19
// author: pan__

template<typename T, typename H = int> class Fenwick2D {
public:
    using U = typename std::conditional_t<std::is_signed_v<T> && std::is_unsigned_v<H>,
            std::make_unsigned_t<T>,
            std::common_type_t<T>>;
    explicit Fenwick2D(size_t _m, size_t _n): m(_m), n(_n), bits(_m, vector<U>(_n)) {}
    explicit Fenwick2D(const vector<vector<T>>& a): Fenwick2D(size(a), size(a.front())) {
        for (size_t i = 0; i < m; ++i) for (size_t j = 0; j < n; ++j) {
                update(i, j, a[i][j]);
            }
    }
    U query(int x1, int y1, int x2, int y2) {
        return sum(x2, y2) - sum(x1-1, y2) - sum(x2, y1-1) + sum(x1-1, y1-1);
    }
    void update(int x, int y, U val) {
        for (int i = x; i < m; i |= i+1) for (int j = y; j < n; j |= j+1)
                bits[i][j] += val;
    }
private:
    vector<vector<U>> bits;
    size_t m, n;
    U sum(int x, int y) {
        U ret{};
        for (int i = x; i >= 0; i = (i & i+1) - 1) for (int j = y; j >= 0; j = (j & j+1) - 1)
                ret += bits[i][j];
        return ret;
    }
};