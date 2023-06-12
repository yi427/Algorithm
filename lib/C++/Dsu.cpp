// This is the Disjoint Sets Union
// finished time: 2023.6.12
// author: pan__
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <cassert>
#include <numeric>

using namespace std;

class Dsu {
public:
    explicit Dsu(int _n) : parent_or_size(_n, -1), n(_n) { }
    int find_set(int a) {
        assert(a >= 0 && a < n);
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = find_set(parent_or_size[a]);
    }
    int union_sets(int x, int y) {
        assert(x >= 0 && x < n);
        assert(y >= 0 && y < n);
        x = find_set(x), y = find_set(y);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }
    bool isConnected(int x, int y) {
        return find_set(x) == find_set(y);
    }
    int size(int a) {
        return -parent_or_size[find_set(a)];
    }
private:
    int n;
    vector<int> parent_or_size;
};