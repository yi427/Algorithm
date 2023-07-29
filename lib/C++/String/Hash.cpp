#include <bits/stdc++.h>

// started time: 2023.7.28
// author: pan__
template<class T> class String_hash {
public:
    using ui64 = unsigned long long;
    explicit String_hash(const std::vector<T> &s, char v = '1', size_t p = 13331)
        : n(size(s)), str(s), h(size(s) + 1), p_pow(size(s) + 1), v(v), P(p) {
        init();
    }
    /* [l, r) */
    [[nodiscard]] ui64 get(int l, int r) const {
        return (h[r] - h[l]) * p_pow[n-l-1];
    }
    ui64 tie(const String_hash& sh, int l, int r) {
        ui64 seed = 0, h1 = sh.get(l, r), h2 = this->get(l, r);
        seed ^= h1 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
private:
    const std::vector<T>& str;
    std::vector<ui64> h, p_pow;
    size_t n, v, P;
    void init() {
        p_pow[0] = 1;
        for (int i = 0; i < n; ++i) {
            p_pow[i+1] = p_pow[i] * P;
            h[i+1] = h[i] + (str[i] - v + 1) * p_pow[i];
        }
    }
};
