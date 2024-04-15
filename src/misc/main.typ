#import "../template.typ": *

== 网络流

=== 最大流
#source("misc/flow/maxflow.cpp")

=== 费用流
#source("misc/flow/costflow.cpp")

== 状态压缩

=== 枚举子集 $O(3^n)$

#source("misc/bit/枚举子集.cpp")

=== 子集和 DP（SOS DP）

== 随机化

=== 模拟退火

#source("misc/模拟退火.cpp", namespace: "SimulateAnneal")

== 线性递推（BM 算法）$O(n^2)$

给定 ${a_i}_(i=1)^n$，求最短递推数列使得 $a_n = sum_(i=1)^k f_(n-i) c_i (n > k)$。模 $998244353$。

#source("misc/线性递推.cpp", namespace: "BerlekampMassey")

== 整式递推

== A$*$ 搜索

== 霍夫曼编码

== 浮点数求和

#source("misc/浮点数求和.cpp")