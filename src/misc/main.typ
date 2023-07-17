#import "../template.typ": *

== A$*$ 搜索

== 随机化

=== 模拟退火

#importCode("misc/模拟退火.cpp", namespace: "SimulateAnneal")

== 线性递推（BM 算法）$O(n^2)$

给定 $a_1, a_2, dots, a_n$，求最短递推数列使得 $a_n = sum_(i=1)^k f_(n-i) c_i (n > k)$。运算模 $998244353$。

#importCode("misc/线性递推.cpp", namespace: "BerlekampMassey")

== 整式递推

