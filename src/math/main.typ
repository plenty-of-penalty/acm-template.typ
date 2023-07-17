#import "../template.typ": *

== 数论

== 线性代数

== 组合数学

== 多项式

=== 模域运算常用函数

#importCode("math/polynom/多项式.cpp", namespace: "modulus_op")

=== 多项式乘法

#importCode("math/polynom/多项式.cpp", namespace: "polynom_mul")

=== 多项式求逆

#importCode("math/polynom/多项式.cpp", namespace: "polynom_inv")

=== 多项式 $ln$

#importCode("math/polynom/多项式.cpp", namespace: "polynom_ln")

=== 多项式 $exp$

#importCode("math/polynom/多项式.cpp", namespace: "polynom_exp")
