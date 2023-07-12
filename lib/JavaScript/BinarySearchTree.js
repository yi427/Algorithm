// @start time: 2023.7.10
// @author pan__
// @name Binary search tree

class BST {
    /**
     * @param {function} com
     */
    constructor(com = null) {
        if (com) this.#cmp = com;
    }
    size() { return this.#size_helper(this.#root); }
    put(key, val) {
        this.#root = this.#put_helper(this.#root, key, val);
    }
    get(key) {
        return this.#get_helper(this.#root, key);
    }
    lower_bound(key) {
        return this.#lower_helper(this.#root, key);
    }
    delete(key) {
        this.#root = this.#delete_helper(this.#root, key);
    }
    back() {
        return this.#min(this.#root);
    }
    #root = null;
    #cmp = (x, y) => {
        return x - y;
    }
    #size_helper(x) {
        if (x === null) return 0;
        return x.N;
    }
    /**
     * @param {Node} x
     * @param key
     * @param val
     * @return {Node}
     */
    #put_helper(x, key, val) {
        if (!x) return new Node(key, val, 1);
        let cmp = this.#cmp(key, x.key);
        if (cmp < 0) x.left = this.#put_helper(x.left, key, val);
        else if (cmp > 0) x.right = this.#put_helper(x.right, key, val);
        else x.val = val;
        x.N = this.#size_helper(x.left) + this.#size_helper(x.right) + 1;
        return x;
    }

    /**
     * @param {Node} x
     * @param key
     * @return {Node|null}
     */
    #get_helper(x, key) {
        if (!x) return null;
        let cmp = this.#cmp(key, x.key);
        if (cmp < 0) return this.#get_helper(x.left, key);
        else if (cmp > 0) return this.#get_helper(x.right, key);
        return x;
    }

    /**
     * @param {Node} x
     * @return {Node}
     */
    #min(x) {
        if (!x.left) return x;
        return this.#min(x.left);
    }

    /**
     * @param {Node} x
     * @param key
     * @return {Node|null}
     */
    #lower_helper(x, key) {
        if (!x) return null;
        let cmp = this.#cmp(key, x.key);
        if (cmp === 0) return x;
        if (cmp > 0) return this.#lower_helper(x.right, key);
        let t = this.#lower_helper(x.left, key);
        if (t) return t;
        return x;
    }

    /**
     * @param {Node} x
     * @return {Node|null}
     */
    #deleteMin(x) {
        if (!x.left) return x.right;
        x.left = this.#deleteMin(x.left);
        x.N = this.#size_helper(x.left) + this.#size_helper(x.right) + 1;
        return x;
    }

    /**
     * @param {Node} x
     * @param key
     * @return {Node|null}
     */
    #delete_helper(x, key) {
        if (!x) return null;
        let cmp = this.#cmp(key, x.key);
        if (cmp < 0) x.left = this.#delete_helper(x.left, key);
        else if (cmp > 0) x.right = this.#delete_helper(x.right, key);
        else {
            if (!x.right) return x.left;
            if (!x.left) return x.right;
            let t = x;
            x = this.#min(t.right);
            x.right = this.#deleteMin(t.right);
            x.left = t.left;
        }
        x.N = this.#size_helper(x.left) + this.#size_helper(x.right) + 1;
        return x;
    }
}
class Node {
    key = null;
    val = null;
    left = null;
    right = null;
    N = 0;
    constructor(key, val, N) {
        this.key = key;
        this.val = val;
        this.N = N;
    }
}
