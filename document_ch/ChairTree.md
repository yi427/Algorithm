# 主席树

* 离散化版本

1. 构造函数:
    只需要传入数组就可以了，对于离散化排序部分，部分数据结构若是不支持排序则需要在离散化中写`lambda`函数  
    时间复杂度: O(N)
2. 接口:
    * find_Kth(l, r, k):
        返回区间$[l, r]$ 内第**K**小的元素。  
        时间复杂度$O(log n)$  
3. 关于数组大小的设置:
    * 1e5大小的话，18 倍就可以了，对于更大的题目，可以开到 32 倍左右。  
