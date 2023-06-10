// finished time: 2023.6.10
// author: pan__

constexpr int LEN = 1e5 * 18;
// 主席树
struct vertex {
    int l{}, r{}, sum{};
};

vertex seg[LEN];

template<typename T>
class ChairTree {
public:
    explicit ChairTree(vector<T>& arr) {
        end = *max_element(begin(arr), ::end(arr)) + 1;
        roots.push_back(build(start, end));
        for (int i = 0; i < size(arr); ++i) 
            roots.push_back(update(roots.back(), start, end, arr[i])); 
    }
    int find_Kth(int l, int r, int k)
    {
        assert(k > 0 && k <= r-l+1);
        return find_Kth(roots[l], roots[r+1], start, end, k);
    }
private:
    int cnt = 0, start = 0, end = 1;
    vector<int> roots;
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