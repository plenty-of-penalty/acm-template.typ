#import "../template.typ": *

#theorem([欧拉定理])[
  若 $gcd(a, m) = 1$，则 $a^(phi(m)) equiv 1 (mod m)$。
]

#theorem([拓展欧拉定理])[
  $
    a^b = cases(
      a^(b mod phi(m))\, &gcd(a, m) = 1\,,
      a^b\, &gcd(a, m) != 1\, b < phi(m)\,,
      a^(b mod phi(m) + phi(m))\, space &gcd(a, m) != -1\, b >= phi(m) \.,
    )
    space (mod m)
  $
]

=== 中国剩余定理

=== 二次剩余

=== 原根

=== 离散对数

=== 连分数

=== 数论分块

#usage 可以 $O(1)$ 计算 $f(r)-f(l)$，则可以 $O(sqrt(n))$ 计算 $sum_(i=1)^n f(i) g(floor(n/i))$。

#caution 注意一些 $i=0$ 的情况。

#source("math/number-theory/数论分块.cpp", namespace: "sqrt_decomposition")

=== $n$ 维数论分块

=== 类欧几里得

=== 万能欧几里得

#source("math/number-theory/万能欧几里得.cpp")