#import "../template.typ": *

== 数论

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
