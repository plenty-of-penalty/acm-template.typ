#import "../template.typ": *

== 数论

=== 根号分治

#usage 可以 $O(1)$ 计算 $f(r)-f(l)$，则可以 $O(sqrt(n))$ 计算 $sum_(i=1)^n f(i) g(floor(n/i))$。

#caution 注意一些 $i=0$ 的 Case

#source("math/number-theory/数论分块.cpp", namespace: "sqrt_decomposition")

=== $n$ 维根号分治

=== 万能欧几里得

#source("math/number-theory/万能欧几里得.cpp")

== 线性代数

== 组合数学

== 多项式

=== 模意义下常用运算

#source("math/polynom/多项式.cpp", namespace: "ModulusOperations")

=== 多项式乘法

#source("math/polynom/多项式.cpp", namespace: "polynom_mul")

=== 多项式求逆

#source("math/polynom/多项式.cpp", namespace: "polynom_inv")

=== 多项式 $ln$

#source("math/polynom/多项式.cpp", namespace: "polynom_ln")

=== 多项式 $exp$

#source("math/polynom/多项式.cpp", namespace: "polynom_exp")

== 多项式（add10k）

=== NTT

#source("math/polynom/多项式-wh.cpp", namespace: "polynom")

=== 分治 NTT

#source("math/polynom/多项式-wh.cpp", namespace: "DC_NTT")
