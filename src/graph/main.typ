#import "../template.typ": *

== 最小生成树

=== Kruskal 算法

=== Prim 算法

=== Boruvka 算法 $O(m log n)$

要求给定图的边权两两不同。一般来说，我们可以给相同权值的边增加第二关键字使其满足条件。

1. 一开始每个点都算作一个连通块，对于每个连通块，找到往外连出的最小边。
2. 最小边一定在最小生成树上，我们可以选定最小边，并使这条边两端的连通块相连。
3. 如果剩余连通块个数 > 1，则回到步骤 1。注意到这样的迭代最多 $O(log n)$ 次。

== 最小树形图

== 最小直径生成树

== 连通性问题

=== 强联通分量

=== 点双联通分量

=== 边双联通分量

== 最短路

=== Dijkstra 算法 $O((n+m) log n)$

求点 $s$ 到每个点的最短路

#importCode("graph/最短路-dijkstra.cpp", namespace: "dijkstra")

=== Floyd 算法 $O(n^3)$

#importCode("graph/最短路-floyd.cpp")

== k 短路问题

== 同余最短路

== 最小环

== 差分约束系统

== 2-SAT

== 欧拉图

== 哈密顿图

== 弦图

== 网络流

#include "flow/main.typ"
