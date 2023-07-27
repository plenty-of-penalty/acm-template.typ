#import "../template.typ": *

== 状态压缩

=== 枚举子集 $O(3^n)$

```cpp
for (int x = 0; x < (1 << n); x++) {
  for (int y = x & (x - 1); y != x; (y -= 1) &= x) {
    // 枚举 y 是 x 的所有子集
  }
}
```

=== 子集和 DP（SOS DP）

== 随机化

=== 模拟退火

#importCode("misc/模拟退火.cpp", namespace: "SimulateAnneal")

== 线性递推（BM 算法）$O(n^2)$

给定 $a_1, a_2, dots, a_n$，求最短递推数列使得 $a_n = sum_(i=1)^k f_(n-i) c_i (n > k)$。运算模 $998244353$。

#importCode("misc/线性递推.cpp", namespace: "BerlekampMassey")

== 整式递推


== A$*$ 搜索

== 霍夫曼编码