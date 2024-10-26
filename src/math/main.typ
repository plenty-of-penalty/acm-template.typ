#import "../template.typ": *
#show: styled

== 数论
#include "number-theory.typ"

== 数论筛法

=== 杜教筛

=== Powerful Number 筛

=== Min_25 筛

== 群论
#desc $X$ 为有限集 $A$ 到 $B$ 的映射；$X/G$ 表示作用在 $X$ 上产生的等价类集合。$c(g)$ 表示置换 $g$ 能拆分成的不相交的循环置换的数量。

==== Burnside 引理
#h(1fr) $display(abs(X"/"G) = 1 / abs(G) sum_(g in G) abs(X^g))$ #h(1fr)

==== Polya 定理
#h(1fr) $display(abs(X"/"G) = 1 / abs(G) sum_(g in G) abs(B)^(c(g)))$ #h(1fr)

== 线性代数

== 博弈论

== 概率论

== 组合数学

== 多项式与生成函数
#source("math/polynom/多项式.cpp", namespace: "ModulusOperations")

=== 多项式乘法
#source("math/polynom/多项式.cpp", namespace: "polynom_mul")

=== 多项式求逆
#source("math/polynom/多项式.cpp", namespace: "polynom_inv")

=== 多项式 $ln$
#source("math/polynom/多项式.cpp", namespace: "polynom_ln")

=== 多项式 $exp$
#source("math/polynom/多项式.cpp", namespace: "polynom_exp")

=== 多项式多点求值
#source("math/polynom/多点求值.cpp")

=== 多项式快速插值
#source("math/polynom/快速插值.cpp")

=== NTT（add10k）
#source("math/polynom/多项式-wh.cpp", namespace: "polynom")

=== 分治 NTT（add10k）
#source("math/polynom/多项式-wh.cpp", namespace: "DC_NTT")

== 杂项

=== 杨氏矩阵

=== 二次剩余
#source("math/cipolla.cpp")