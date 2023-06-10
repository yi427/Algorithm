// finished time: 2023.6.10
// author: pan__

template<typename T>
class ChairTree {
public:
    explicit ChairTree(const vector<T> &arr) {
        end = *max_element(begin(arr), ::end(arr)) + 1;
        roots.push_back(build(start, end));
        for (auto &v: arr)
            roots.push_back(update(roots.back(), start, end, v));
    }

    int find_Kth(int l, int r, int k) {
        assert(k > 0 && k <= r-l+1);
        return find_Kth(roots[l], roots[r + 1], start, end, k);
    }

private:
    struct vertex {
        vertex *l;
        vertex *r;
        int sum = 0;

        explicit vertex(int val) : l(nullptr), r(nullptr), sum(val) {}

        vertex(vertex *l, vertex *r) : l(l), r(r) {
            if (l) sum += l->sum;
            if (r) sum += r->sum;
        }
    };

    using v_ptr = vertex *;
    vector<v_ptr> roots;
    int start = 0, end = 1;

    v_ptr build(int L, int R) {
        if (L == R) return new vertex(0);
        int m = (L + R) >> 1;
        return new vertex(build(L, m), build(m + 1, R));
    }

    v_ptr update(v_ptr v, int L, int R, int pos) {
        if (L == R) return new vertex(v->sum + 1);
        int m = (L + R) >> 1;
        if (pos <= m) return new vertex(update(v->l, L, m, pos), v->r);
        return new vertex(v->l, update(v->r, m + 1, R, pos));
    }

    int find_Kth(v_ptr vl, v_ptr vr, int L, int R, int k) {
        if (L == R) return L;
        int m = (L + R) >> 1, left_counter = vr->l->sum - vl->l->sum;
        if (left_counter >= k) return find_Kth(vl->l, vr->l, L, m, k);
        return find_Kth(vl->r, vr->r, m + 1, R, k - left_counter);
    }
};