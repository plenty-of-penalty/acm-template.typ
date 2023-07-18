#import "../template.typ": *

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

== 最小生成树

=== Kruskal 算法

=== Prim 算法

=== Boruvka 算法

可用于求解边权互不相同的无向联通图的最小生成树。一般来说，我们可以通过给相同权值的边增加第二关键词使其满足这一条件。

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
