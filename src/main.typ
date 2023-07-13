#import "template.typ": *

#show: project.with(  
  title: "ACM Template",
  authors: (
    "memset0",
    "Sulfox",
  ),
)




= 数据结构

== 线段树

=== zkw 线段树





= 图论

== 最短路

=== Dijkstra 算法 $O((V+E) log V)$

求点 $s$ 到每个点的最短路

#importCode("graph/dijkstra.cpp", namespace: "dijkstra")
#importCode("graph/dijkstra.cpp")

=== Floyd $O(V^3)$

== 最小生成树

=== Kruskal 算法
=== Prim 算法

=== Boruvka 算法

可用于求解边权互不相同的

== 连通性问题




= 数学

== 数论

== 多项式

=== 快速数论变换（NTT）

=== 多项式乘法





= 字符串





= 计算几何

== 计算几何基础





= 动态规划





= 杂项

== A$*$ 搜索

== 模拟退火





= 思路

== 离线算法

=== CDQ 分治

=== 整体二分

=== 莫队




= 附录

== 编辑指南

== 浏览计数

#image("https://count.getloli.com/get/@mem-acm-template?theme=rule34")