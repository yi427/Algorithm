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
    explicit FenWick(size_t _n, vector<T>& _a, U _val, F _op): n(_n), d_val(_val), b1(_n+2, _val), b2(_n+1, _val), op(_op), nums(_a) {
        if (op(1, 2) == 2) com = std::less<U>();
        else com = std::greater<U>();
    }
    explicit FenWick(vector<T>& _a,  F _op,  U _val = U{}): FenWick(size(_a), _a, _val, _op) {
        for (int i = 0; i < n; ++i) {
            b1[i+1] = op(nums[i], b1[i+1]);
            for (int j = i+1; j <= n; j += j&-j)
                b1[j] = op(b1[i+1], b1[j]);
            b1.back() = op(b1.back(), nums[i]);
        }
        for (int i = n-1; i >= 0; --i) {
            b2[i+1] = op(nums[i], b2[i+1]);
            for (int j = i+1; j; j -= j&-j)
                b2[j] = op(b2[i+1], b2[j]);
            b2.front() = op(b2.front(), nums[i]);
        }
    }
    U query(int l, int r) {
        assert(0 <= l && l <= r && r < n);
        return query_helper(l+1, r+1);
    }
    void update(int idx, int val) {
        assert(0 <= idx && idx < n);
        int oldValue = nums[idx];
        nums[idx] = val;
        update_helper(idx+1, val, oldValue);
    }
private:
    vector<U> b1, b2; vector<T>& nums;
    size_t n; U d_val; F op;
    function<bool(U, U)> com;
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
    void update_helper(int idx, U val, U oldValue) {
        update_bit1(idx, val, oldValue);
        update_bit2(idx, val, oldValue);
    }
    void update_bit1(int node, U v, U oldValue) {
        while (node <= n+1) {
            if (com(v, b1[node])) {
                if (oldValue == b1[node]) {
                    if (node != n+1) v = op(v, nums[node-1]);
                    for (int j = 0; !(node & (1 << j)) && node - (1 << j) > 0; j++)
                        v = op(v, b1[node - (1 << j)]);
                } else break;
            }
            if (v == b1[node]) break;
            b1[node] = v;
            node += node & -node;
        }
    }
    void update_bit2(int node, U v, U oldValue) {
        while (node >= 0) {
            if (com(v, b2[node])) {
                if (oldValue == b2[node]) {
                    if (node != 0) v = op(v, nums[node-1]);
                    for (int j = 0; !(node & (1 << j)) && node + (1 << j) < n+1; j++)
                        v = op(v, b2[node + (1 << j)]);
                } else break;
            }
            if (v == b2[node]) break;
            b2[node] = v;
            node -= node & -node;
        }
    }
};

// 下面的版本是最开始的版本，可以对照着看

class FenWickMin {
public:
    FenWickMin(vector<int>& a): nums(a), n (size(a)) {
        b1.resize(n+2, 0xffff);
        b2.resize(n+1, 0xffff);
        for (int i = 0; i < n; ++i) {
            b1[i+1] = min(nums[i], b1[i+1]);
            for (int j = i+1; j <= n; j += j&-j)
                b1[j] = min(b1[i+1], b1[j]);
            b1.back() = min(b1.back(), nums[i]);
        }
        for (int i = n-1; i >= 0; --i) {
            b2[i+1] = min(nums[i], b2[i+1]);
            for (int j = i+1; j ; j -= j&-j)
                b2[j] = min(b2[i+1], b2[j]);
            b2[0] = min(b2[0], nums[i]);
        }
    }
    void print() {
        // copy(begin(b1), end(b1), ostream_iterator<int>(cout, " "));
        cout << endl;
        // copy(begin(b2), end(b2), ostream_iterator<int>(cout, " "));
    }
    int query(int l, int r) {
        int val = 0xffff;
        int i = l;
        while (i + (i & -i) <= r) {
            val = min(val, b2[i]);
            i += i&-i;
        }
        i = r;
        while (i - (i & -i) >= l) {
            val = min(val, b1[i]);
            i -= i&-i;
        }
        val = min(val, nums[i-1]);
        return val;
    }
    void update(int idx, int val) {
        int oldValue = nums[idx-1];
        nums[idx-1] = val;
        int node = idx, v = val;
        while (node <= n+1) {
            if (v > b1[node]) {
                if (oldValue == b1[node]) {
                    if (node != n+1) v = min(v, nums[node-1]);
                    for (int j = 0; !(node & (1 << j)) && node - (1 << j) > 0; j++)
                        v = min(v, b1[node - (1 << j)]);
                } else break;
            }
            if (v == b1[node]) break;
            b1[node] = v;
            node += node & -node;
        }
        node = idx, v = val;
        while (node >= 0) {
            if (v > b2[node]) {
                if (oldValue == b2[node]) {
                    if (node != 0) v = min(v, nums[node-1]);
                    for (int j = 0; !(node & (1 << j)) && node + (1 << j) < n+1; j++)
                        v = min(v, b2[node + (1 << j)]);
                } else break;
            }
            if (v == b2[node]) break;
            b2[node] = v;
            node -= node & -node;
        }
    }
private:
    vector<int> b1, b2;
    vector<int>& nums;
    int n;
};

// 以下是测试代码
int main()
{
    int M = 16, n = 15;
    constexpr auto low_bit = [](int v) {
        return v & -v;
    };
    for (int i = 1; i <= M; ++i) {
        int l = i - low_bit(i)+1, r = i;
        // cout << '[' << l << ',' << r << ']' << '\n';
    }
    vector v{1, 0, 2, 1, 1, 3, 0, 4, 2, 5, 2, 2, 3, 1, 0};
    vector t(M-1, 0xffff);
    FenWickMin f(v);
    f.print(); cout << endl;
    FenWickMin f2(t);
    f2.print(); cout << endl;
    for (int i = 0; i < size(v); ++i)
        f2.update(i+1, v[i]);
    f2.print();
    cout << endl;
    // int z = 4;
    // 找 节点的子节点
    //for (int j = 0; !(z & (1 << j)) && z - (1 << j) > 0; j++) cout << z - (1 << j) << ' ';
    //for (int j = 0; !(z & (1 << j)) && z + (1 << j) < M; j++) cout << z + (1 << j) << ' ';
    FenWick F(v, [](auto x, auto y){
      return min(x, y);
    }, 0xffff);
    // F.print();
    return 0;
}