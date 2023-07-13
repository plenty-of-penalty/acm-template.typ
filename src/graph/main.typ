#import "../template.typ": *

== 最短路

=== Dijkstra 算法 $O((V+E) log V)$

求点 $s$ 到每个点的最短路

#importCode("graph/dijkstra.cpp", namespace: "dijkstra")

=== Floyd $O(V^3)$

#importCode("graph/floyd.cpp")

== 最小生成树

=== Kruskal 算法
=== Prim 算法

=== Boruvka 算法

可用于求解边权互不相同的

== 连通性问题

=== 强联通分量

=== 点双联通分量

=== 边双联通分量