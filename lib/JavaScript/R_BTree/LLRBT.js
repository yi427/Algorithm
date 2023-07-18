class RedBlackTree {
    /**
     * Get the compare rule
     * @param {function} com
     */
    constructor(com = null) {
        if (com) this.#op = com;
    }
    size() { return this.#size_helper(this.#root); }
    empty() { return this.#root === null; }
    get(key) { return this.#get_helper(this.#root, key); }
    put(key, val) {
        this.#root = this.#put_helper(this.#root, key, val);
        this.#root.color = RedBlackTree.#BLACK;
    }
    floor(key) {
        return this.#floor_helper(this.#root, key);
    }
    ceiling(key) {
        return this.#ceiling_helper(this.#root, key);
    }
    deleteMin() {
        if (!this.#isRed(this.#root.left) && !this.#isRed(this.#root.right))
            this.#root.color = RedBlackTree.#RED;
        this.#root = this.#deleteMin_helper(this.#root);
        if (!this.empty()) this.#root.color = RedBlackTree.#BLACK;
    }
    delete(key) {
        if (!this.contains(key)) return;
        if (!this.#isRed(this.#root.left) && !this.#isRed(this.#root.right))
            this.#root.color = RedBlackTree.#RED;
        this.#root = this.#delete_helper(this.#root, key);
        if (!this.empty()) this.#root.color = RedBlackTree.#BLACK;
    }
    contains(key) {
        return this.get(key) !== null;
    }
    min() {
        return this.#min_helper(this.#root);
    }

    #root = null;
    /**
     * The function to creat thw Node Object
     * @param {any} key
     * @param {any} val
     * @param {boolean} color
     * @param {number} size
     * @return {{val, color, size, left: null, right: null, key}}
     */
    #makeNode = function (key, val, color, size) {
        return { key, val, color, size, left: null, right: null };
    };
    #op = (x, y) => {
        return x - y;
    }
    /* help methods */
    #isRed(x) {
        if (!x) return false;
        return x.color === RedBlackTree.#RED;
    }

    /**
     * Get the Node number
     * @param x
     * @return {number}
     */
    #size_helper(x) {
        if (!x) return 0;
        return x.size;
    }
    #get_helper(x, key) {
        while (x) {
            let cmp = this.#op(key, x.key);
            if (cmp < 0) x = x.left;
            else if (cmp > 0) x = x.right;
            else return x.val;
        }
        return null;
    }
    #put_helper(h, key, val) {
        if (!h) return this.#makeNode(key, val, RedBlackTree.#RED, 1);

        let cmp = this.#op(key, h.key);
        if (cmp < 0) h.left = this.#put_helper(h.left, key, val);
        else if (cmp > 0) h.right = this.#put_helper(h.right, key, val);
        else h.val = val;

        if (this.#isRed(h.right) && !this.#isRed(h.left)) h = this.#rotateLeft(h);
        if (this.#isRed(h.left) && this.#isRed(h.left.left)) h = this.#rotateRight(h);
        if (this.#isRed(h.left) && this.#isRed(h.right)) this.#flipColors(h);

        return h;
    }
    #floor_helper(x, key) {
        if (!x) return null;
        let cmp = this.#op(key, x.key);
        if (cmp === 0) return x;
        if (cmp < 0) return this.#floor_helper(x.left, key);
        let t = this.#floor_helper(x.right, key);
        if (t) return t;
        return x;
    }
    #ceiling_helper(x, key) {
        if (!x) return null;
        let cmp = this.#op(key, x.key);
        if (cmp === 0) return x;
        if (cmp > 0) return this.#ceiling_helper(x.right, key);
        let t = this.#ceiling_helper(x.left, key);
        if (t) return t;
        return x;
    }
    #deleteMin_helper(h) {
        if (!h.left) return null;
        if (!this.#isRed(h.left) && !this.#isRed(h.left.left))
            h = this.#moveRedLeft(h);
        h.left = this.#deleteMin_helper(h.left);
        return this.#balance(h);
    }
    #delete_helper(h, key) {
        if (this.#op(key, h.key) < 0) {
            if (!this.#isRed(h.left) && !this.#isRed(h.left.left))
                h = this.#moveRedLeft(h);
            h.left = this.#delete_helper(h.left, key);
        } else {
            if (this.#isRed(h.left))
                h = this.#rotateRight(h);
            if (!this.#op(key, h.key) && !h.right)
                return null;
            if (!this.#isRed(h.right) && !this.#isRed(h.right.left))
                h = this.#moveRedRight(h);
            if (!this.#op(key, h.key)) {
                let x = this.#min_helper(h.right);
                [h.key, h.val] = [x.key, x.val];
                h.right = this.#deleteMin_helper(h.right);
            } else
                h.right = this.#delete_helper(h.right, key);
        }
        return this.#balance(h);
    }
    #min_helper(h) {
        if (!h.left) return h;
        return this.#min_helper(h.left);
    }
    #rotateLeft(h) {
        console.assert(h && this.#isRed(h.right))
        let x = h.right;
        h.right = x.left;
        x.left = h;
        x.color = h.color;
        h.color = RedBlackTree.#RED;
        x.size = h.size;
        h.size = this.#size_helper(h.left) + this.#size_helper(h.right) + 1;
        return x;
    }
    #rotateRight(h) {
        console.assert(h && this.#isRed(h.left));
        let x = h.left;
        h.left = x.right;
        x.right = h;
        x.color = h.color;
        h.color = RedBlackTree.#RED;
        x.size = h.size;
        h.size = this.#size_helper(h.left) + this.#size_helper(h.right) + 1;
        return x;
    }
    #flipColors(h) {
        h.color = !h.color;
        h.left.color = !h.left.color;
        h.right.color = !h.right.color;
    }
    #moveRedLeft(h) {
        this.#flipColors(h);
        if (this.#isRed(h.right.left)) {
            h.right = this.#rotateRight(h.right);
            h = this.#rotateLeft(h);
            this.#flipColors(h);
        }
        return h;
    }
    #moveRedRight(h) {
        this.#flipColors(h);
        if (this.#isRed(h.left.left)) {
            h = this.#rotateRight(h);
            this.#flipColors(h);
        }
        return h;
    }
    #balance(h) {
        if (this.#isRed(h.right) && !this.#isRed(h.left)) h = this.#rotateLeft(h);
        if (this.#isRed(h.left) && this.#isRed(h.left.left)) h = this.#rotateRight(h);
        if (this.#isRed(h.left) && this.#isRed(h.right)) this.#flipColors(h);

        h.size = this.#size_helper(h.left) + this.#size_helper(h.right) + 1;
        return h;
    }
    static #RED = true;
    static #BLACK = false;
}
