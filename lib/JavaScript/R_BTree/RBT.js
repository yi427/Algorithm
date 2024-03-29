// @start 2023.7.15
// @author pan__

class TreeMap {
    constructor(com = null) {
        this.#t = new RedBlackTree(com);
    }
    get(key) {
        let res = this.#t.get(key);
        if (!res) return null;
        return res.val;
    }
    getOrDefault(key, v) {
        let ans = this.get(key);
        if (!ans) return v;
        return ans;
    }
    put(key, val) {
        this.#t.put(key, val);
    }
    delete(key) {
        let res = this.#t.delete(key);
        if (!res) return this.#makeNode();
        return this.#makeNode(res.key, res.val);
    }
    ceiling(key) {
        let res = this.#t.ceiling(key);
        if (!res) return this.#makeNode();
        return this.#makeNode(res.key, res.val);
    }
    floor(key) {
        let res = this.#t.floor(key);
        if (!res) return this.#makeNode();
        return this.#makeNode(res.key, res.val);
    }
    next(key) {
        let h = this.#t.successor(this.#t.get(key));
        if (!h) return this.#makeNode();
        return this.#makeNode(h.key, h.val);
    }
    [Symbol.iterator]() {
        let i = this.#t.min(), f = this.#t.successor;
        return {
          next() {
              if (i) {
                  let res = [i.key, i.val];
                  i = f(i);
                  return { done: false, value: res };
              } else {
                  return { done: true, value: undefined };
              }
          },
          return() {
              return { done: true };
          }
        };
    }
    #makeNode = function (key = null, val = null) {
        return {key, val};
    }
    #t;
}

class RedBlackTree {
    constructor(com = null) {
        if (com) this.#com = com;
    }
    get(key) {
        let ans = this.#get_helper(this.#root, key);
        if (!ans) return null;
        return ans;
    }
    put(key, val) {
        this.#put_helper(this.#root, key, val);
        if (!this.empty()) this.#root.color = RedBlackTree.#BLACK;
    }
    delete(key) {
        let x = this.#get_helper(this.#root, key);
        if (!x) return null;
        return this.#delete_helper(x);
    }
    min() {
        return this.#min_helper(this.#root);
    }
    contains(key) { return this.get(key) !== null; }
    empty() { return this.#root === null; }
    floor(key) {
        return this.#floor_helper(this.#root, key);
    }
    ceiling(key) {
        return this.#ceiling_helper(this.#root, key);
    }
    successor(h) {
        if (!h) return null;
        if (h.right) return this.#min_helper(h.right);
        let y = h.parent;
        while (y&& y.right === h)
            [y, h] = [y.parent, y]
        return y;
    }
    #com = (x, y) => { return x - y; }
    #root = null;
    /**
     * Creat a new Node
     * @param key
     * @param val
     * @param color
     * @param parent
     * @return {{val, parent: null, color, left: null, right: null, key}}
     */
    #makeNode = function (key, val, color, parent) {
        return {key, val, color, left: null, right: null, parent};
    }
    static #RED = true;
    static #BLACK = false;
    #get_helper(h, key) {
        while (h) {
            let com = this.#com(key, h.key);
            if (com < 0) h = h.left;
            else if (com > 0) h = h.right;
            else return h;
        }
        return null;
    }
    #put_helper(h, key, val) {
        let cur = h, p = null;
        while (cur) {
            p = cur;
            let com = this.#com(key, cur.key);
            if (com < 0) cur = cur.left;
            else if (com > 0) cur = cur.right;
            else {
                cur.val = val;
                return;
            }
        }
        let newNode = this.#makeNode(key, val, RedBlackTree.#RED, p);
        if (p) {
            let com = this.#com(key, p.key);
            if (com < 0) p.left = newNode;
            else p.right = newNode;
        } else {
            this.#root = newNode;
        }
        this.#fixAfterInsertion(newNode);
    }
    #delete_helper(h) {
        let res = this.successor(h);
        if (h.left && h.right) {
            let s = this.successor(h);
            [h.key, h.val] = [s.key, s.val];
            [h, res] = [s, h];
        }
        let r = null;
        if (h.left) r = h.left;
        else if (h.right) r = h.right;
        if (r) {
            r.parent = h.parent;
            if (!h.parent) this.#root = r;
            else if (h === h.parent.left) h.parent.left = r;
            else h.parent.right = r;
            this.#remove(h);
            r.color = RedBlackTree.#BLACK;
        } else if (!h.parent) {
            this.#root = null;
        } else {
            if (h.color === RedBlackTree.#BLACK) this.#fixAfterDeletion(h);
            if (h.parent) {
                if (h === h.parent.left) h.parent.left = null;
                else h.parent.right = null;
                this.#remove(h);
            }
        }
        return res;
    }
    /** Helper Function **/
    #fixAfterInsertion(h) {
        let p = null, g = null;
        while ((p = h.parent) && this.#isRed(p) && (g = p.parent)) {
            if (p === g.left) {
                let u = g.right;
                if (this.#isRed(u)) {
                    this.#flipColors(g);
                    h = p;
                } else {
                    if (h === p.right) {
                        h = p;
                        p = this.#rotateLeft(p);
                    }
                    this.#flipColor(p);
                    this.#flipColor(g);
                    this.#rotateRight(g);
                }
            } else {
                let u = g.left;
                if (this.#isRed(u)) {
                    this.#flipColors(g);
                    h = p;
                } else {
                    if (h === p.left) {
                        h = p;
                        p = this.#rotateRight(p);
                    }
                    this.#flipColor(p);
                    this.#flipColor(g);
                    this.#rotateLeft(g);
                }
            }
        }
    }
    #fixAfterDeletion(h) {
        let parent = h.parent;
        while (!this.#isRed(h) && h !== this.#root) {
            if (h === parent.left) {
                let sid = parent.right;
                if (this.#isRed(sid)) {
                    this.#setColor(parent, RedBlackTree.#RED);
                    this.#setColor(sid, RedBlackTree.#BLACK);
                    this.#rotateLeft(parent);
                    sid = parent.right;
                }
                if (!this.#isRed(this.#leftOf(sid)) && !this.#isRed(this.#rightOf(sid))) {
                    this.#setColor(sid, RedBlackTree.#RED);
                    [parent, h] = [h.parent, parent];
                } else {
                    if (!this.#isRed(this.#rightOf(sid))) {
                        this.#setColor(this.#leftOf(sid), RedBlackTree.#BLACK);
                        this.#setColor(sid, RedBlackTree.#RED);
                        this.#rotateRight(sid);
                        sid = parent.right;
                    }
                    this.#setColor(sid, parent.color);
                    this.#setColor(parent, RedBlackTree.#BLACK);
                    this.#setColor(this.#rightOf(sid), RedBlackTree.#BLACK);
                    this.#rotateLeft(parent);
                    h = this.#root;
                }
            } else {
                let sid = parent.left;
                if (this.#isRed(sid)) {
                    this.#setColor(parent, RedBlackTree.#RED);
                    this.#setColor(sid, RedBlackTree.#BLACK);
                    this.#rotateRight(parent);
                    sid = parent.left;
                }
                if (!this.#isRed(this.#leftOf(sid)) && !this.#isRed(this.#rightOf(sid))) {
                    this.#setColor(sid, RedBlackTree.#RED);
                    [parent, h] = [h.parent, parent];
                } else {
                    if (!this.#isRed(this.#leftOf(sid))) {
                        this.#setColor(this.#rightOf(sid), RedBlackTree.#BLACK);
                        this.#setColor(sid, RedBlackTree.#RED);
                        this.#rotateLeft(sid);
                        sid = parent.left;
                    }
                    this.#setColor(sid, parent.color);
                    this.#setColor(parent, RedBlackTree.#BLACK);
                    this.#setColor(this.#leftOf(sid), RedBlackTree.#BLACK);
                    this.#rotateRight(parent);
                    h = this.#root;
                }
            }
        }
        h.color = RedBlackTree.#BLACK;
    }
    #min_helper(h) {
        if (!h.left) return h;
        return this.#min_helper(h.left);
    }
    #rotateLeft(h) {
        let x = h.right;
        h.right = x.left;
        if (x.left) x.left.parent = h;
        x.parent = h.parent;
        if (!h.parent) this.#root = x;
        else {
            if (h.parent.left === h) h.parent.left = x;
            else h.parent.right = x;
        }
        x.left = h;
        h.parent = x;
        return x;
    }
    #rotateRight(h) {
        let x = h.left;
        h.left = x.right;
        if (x.right) x.right.parent = h;
        x.parent = h.parent;
        if (!h.parent) this.#root = x;
        else {
            if (h.parent.left === h) h.parent.left = x;
            else h.parent.right = x;
        }
        x.right = h;
        h.parent = x;
        return x;
    }
    #flipColor(h) {
        h.color = !h.color;
    }
    #flipColors(h) {
        h.color = !h.color;
        h.left.color = !h.left.color;
        h.right.color = !h.right.color;
    }
    #floor_helper(x, key) {
        if (!x) return null;
        let cmp = this.#com(key, x.key);
        if (cmp === 0) return x;
        if (cmp < 0) return this.#floor_helper(x.left, key);
        let t = this.#floor_helper(x.right, key);
        if (t) return t;
        return x;
    }
    #ceiling_helper(x, key) {
        if (!x) return null;
        let cmp = this.#com(key, x.key);
        if (cmp === 0) return x;
        if (cmp > 0) return this.#ceiling_helper(x.right, key);
        let t = this.#ceiling_helper(x.left, key);
        if (t) return t;
        return x;
    }
    #isRed(h) {
        if (!h) return RedBlackTree.#BLACK;
        return h.color === RedBlackTree.#RED;
    }
    #remove(h) {
        h.left = h.right = h.parent = h.key = h.val = h.color = null;
    }
    #leftOf(h) {
        if (!h) return null;
        return h.left;
    }
    #rightOf(h) {
        if (!h) return null;
        return h.right;
    }
    #setColor(h, c) {
        if (!h) return;
        h.color = c;
    }
}
