/ start time: 2023.7.8
// author: pan__
class Priority_queue {
    constructor(...args) {
        for (let arg of args) {
            if (typeof arg === 'function') this.#op = arg;
            else this.#arr = [...arg];
        }
        for (let i = this.#parent(this.size()-1); i >= 0; i--)
            this.#sink(i);
    }
    empty() { return this.size() === 0; }
    size() { return this.#arr.length; }
    peek() { return this.#arr[0]; }
    push(...values) {
        for (let v of values) {
            this.#arr.push(v);
            this.#swim(this.size() - 1);
        }
    }
    pop() {
        if (!this.size()) throw new Error('Heap is empty!');
        this.#swap(0, this.size()-1);
        const v = this.#arr.pop();
        this.#sink(0);
        return v;
    }
    // The Swim and Sink method for Algorithm Fourth.
    // Swim Node
    #swim(k) {
        while (k > 0 && this.#com(this.#parent(k), k)) {
            this.#swap(this.#parent(k), k);
            k = this.#parent(k);
        }
    }
    // Sink Node
    #sink(k) {
        for (let N = this.size(); this.#left(k) < N;) {
            let j = this.#left(k);
            if (j < N-1 && this.#com(j, j+1)) j++;
            if (!this.#com(k, j)) break;
            this.#swap(k, j);
            k = j;
        }
    }
    // Notes: The first index is the Zero.
    #left(i) { return 2*i+1; }
    #parent(i) { return Math.floor((i-1)/2); }
    #com(x, y) { return this.#op(this.#arr[x], this.#arr[y]); }
    #swap(x, y) { [this.#arr[x], this.#arr[y]] = [this.#arr[y], this.#arr[x]]; }
    #op = (x, y) => x < y;
    #arr = [];
}

// The problem: https://leetcode.cn/problems/kth-largest-element-in-an-array/description/

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var findKthLargest = function(nums, k) {
    const p = new Priority_queue((x, y) => x > y);
    for (let i = 0; i < k; ++i) p.push(nums[i]);
    for (let i = k; i < nums.length; ++i) {
        if (nums[i] > p.peek()) {
            p.pop();
            p.push(nums[i]);
        }
    }
    return p.peek();
};

// The problem: https://leetcode.cn/problems/sort-an-array/description/

/**
 * @param {number[]} nums
 * @return {number[]}
 */
var sortArray = function(nums) {
    let p = new Priority_queue(nums, (x, y) => x > y);
    let res = [];
    while (p.size() !== 0) res.push(p.pop());
    return res;
};

// The problem: https://leetcode.cn/problems/ugly-number-ii/description/

/**
 * @param {number} n
 * @return {number}
 */
var nthUglyNumber = function(n) {
    const q = new Priority_queue((x, y) => x > y, [1]);
    const f = new Set();
    for (let i = 1; i <= n;) {
        let t = q.pop();
        if (f.has(t)) continue;
        if (i === n) return t;
        q.push(t*2, t*3, t*5);
        f.add(t);
        ++i;
    }
    return -1;
};
