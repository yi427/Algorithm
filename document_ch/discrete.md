# 离散化模板

1. 构造函数:
   * 参数:  
      1. 原始数组  
      2. 比较函数，默认比较函数是 std::less\<T\>()  
2. 接口：  

`pos(val)`: 获取 `val` 对应的映射  

---

`greater(val)`: 获取 $>$ `val` 对应的映射

---

`greater_equal(val)`: 获取 $\ge$ `val` 对应的映射  

---

`less(val)`: 获取 $<$ `val` 对应的映射

---

`less_equal(val)`: 获取 $\le$ `val` 对应的映射

---

`get(pos)`: 获取 `pos` 映射对应的数组值

---

`len()`: 获取数组长度  
