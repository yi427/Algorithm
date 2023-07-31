#include <bits/stdc++.h>

// started time: 2023.7.30
// author: pan__

template<size_t K> class Aho_Corasick {
public:
    explicit Aho_Corasick(): t(1) {}

    template<class Func>
    void insert(const std::string& str, Func op) {
        int pos = add(str);
        op(pos, str);
    }
    void insert(const std::string& str) {
        add(str);
    }
    template<class Func>
    void build(Func op) {
        std::queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int f = q.front(); q.pop();
            for (int j = 0; j < K; ++j) {
                int u = t[f].next[j];
                if (u != -1) {
                    op(u, get_link(u));
                    q.push(u);
                }
            }
        }
    }
    bool search(const std::string& str) {
        int v = 0;
        for (auto ch : str)
            v = go(v, ch);
        if (t[v].output) return true;
        while (v != 0 && !t[v].output)
            v = get_link(v);
        return v;
    }
    int next(int pos, char letter) {
        return go(pos, letter);
    }
private:
    struct vertex {
        /**
         * @param next[c] is the matched next state
         * @param go[i] is the All cases next state
         * @param p is the parent, pch is the p -> i, label
         * @param link is the suffix link
         * @param output is the last vertex
         */
        int next[K]{}, go[K]{}, p = -1, link = -1;
        char pch;
        bool output = false;
        explicit vertex(int p = - 1, char ch = '#'): p(p), pch(ch) {
            memset(next, -1, sizeof(next));
            memset(go, -1, sizeof(go));
        }
    };
    std::vector<vertex> t;
    int add(const std::string& str) {
        int v = 0;
        for (auto ch : str) {
            int c = ch - 'a';
            if (t[v].next[c] == -1) {
                t[v].next[c] = std::size(t);
                t.emplace_back(v, ch);
            }
            v = t[v].next[c];
        }
        t[v].output = true;
        return v;
    }
    int go(int, char);
    int get_link(int);
};

template<size_t K> int Aho_Corasick<K>::get_link(int v) {
    if (t[v].link == -1) {
        if (v == 0 || t[v].p == 0) t[v].link = 0;
        else t[v].link = go(get_link(t[v].p), t[v].pch);
    }
    return t[v].link;
}

template<size_t K> int Aho_Corasick<K>::go(int v, char ch) {
    int c = ch - 'a';
    if (t[v].go[c] == -1) {
        if (t[v].next[c] != -1) t[v].go[c] = t[v].next[c];
        else t[v].go[c] = ( v == 0) ? 0 : go(get_link(v), ch);
    }
    return t[v].go[c];
}
