// finished time: 2023.6.10
// author: pan__

constexpr int LEN = 1e5 * 18;
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

struct vertex {
    int l{}, r{}, sum{};
};

vertex seg[LEN];

// 主席树
template<typename T>
class ChairTree {
public:
    explicit ChairTree(const vector<T>& arr): d(arr) {
        end = d.len();
        roots.push_back(build(start, end));
        for (int i = 0; i < size(arr); ++i) 
            roots.push_back(update(roots.back(), start, end, d.pos(arr[i]))); 
    }
    int find_Kth(int l, int r, int k)
    {
        assert(k > 0 && k <= r-l+1);
        return d.get(find_Kth(roots[l], roots[r+1], start, end, k));
    }
private:
    int cnt = 0, start = 0, end = 1;
    vector<int> roots;
    const discrete<T> d;
    int build(int l, int r)
    {
        int root = ++cnt;
        seg[root].sum = 0;
        if (l == r) return root;
        int m = (l+r) >> 1;
        seg[root].l = build(l, m);
        seg[root].r = build(m+1, r);
        return root;
    }
    int update(int last, int l, int r, int pos)
    {
        int dir = ++cnt;
        seg[dir] = seg[last];
        seg[dir].sum++;
        if (l == r) return dir;
        int m = (l + r) >> 1;
        if (pos <= m) seg[dir].l = update(seg[last].l, l, m, pos);
        else seg[dir].r = update( seg[last].r, m+1, r, pos);
        return dir;
    }
    int find_Kth(int v1, int v2, int l, int r, int k)
    {
        if (l == r) return l;
        int m = (l+r) >> 1, left_counter = seg[seg[v2].l].sum - seg[seg[v1].l].sum;
        if (left_counter >= k) return find_Kth(seg[v1].l, seg[v2].l, l, m, k);
        return find_Kth(seg[v1].r, seg[v2].r, m+1, r, k-left_counter);
    }
};