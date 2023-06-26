// started time: 2023.6.19
// author: pan__
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
// 参考地址
// https://stackoverflow.com/questions/31106459/how-to-adapt-fenwick-tree-to-answer-range-minimum-queries/34602284?newreg=b493f8052f4743f2a7ae1df3d5cc9f3b
// https://ioinformatics.org/journal/v9_2015_39_44.pdf
// 测试题目:
// https://www.acwing.com/problem/content/description/1272/
// https://leetcode.cn/problems/sliding-window-maximum/
template<typename T, class F, typename H = int> class FenWick {
public:
    using U = typename std::conditional_t<std::is_signed_v<T> && std::is_unsigned_v<H>,
            std::make_unsigned_t<T>,
            std::common_type_t<T>>;
    explicit FenWick(size_t _n, vector<T>& _a, U _val, F _op): n(_n), d_val(_val), b1(_n+2, _val), b2(_n+2, _val), op(_op), nums(_a) {}
    explicit FenWick(vector<T>& _a,  F _op,  U _val = U{}): FenWick(size(_a), _a, _val, _op) {
        for (int i = 1; i <= n; ++i) {
            b1[i] = op(nums[i-1], b1[i]);
            int r = i + (i&-i);
            if (r <= n+1) b1[r] = op(b1[r], b1[i]);
        }
        for (int i = n; i >= 1; --i) {
            b2[i] = op(nums[i-1], b2[i]);
            int l = i - (i&-i);
            b2[l] = op(b2[l], b2[i]);
        }
    }
    U query(int l, int r) {
        assert(0 <= l && l <= r && r < n);
        return query_helper(l+1, r+1);
    }
private:
    vector<U> b1, b2; vector<T>& nums;
    size_t n; U d_val; F op;
    U query_helper(int l, int r) {
        int val = d_val;
        int i = l;
        while (i + (i & -i) <= r) {
            val = op(val, b2[i]);
            i += i&-i;
        }
        i = r;
        while (i - (i & -i) >= l) {
            val = op(val, b1[i]);
            i -= i&-i;
        }
        val = op(val, nums[i-1]);
        return val;
    }
};
