#import "../../template.typ": *
#show: styled

=== 最大流
#desc 先用 add($u$, $v$, $w$) 加边，再调用 solve($s$, $t$) 求解 $s$ 到 $t$ 的最大流。如果需要在同一张图上跑多次，需要手动回退流量。如果需要在不同图上做，可以调用 clear()。

#time $O(n^2 m)$。

#source("graph/flow/最大流.cpp", namespace: "maxflow")

=== 最小费用最大流

=== 有源汇上下界最大流

=== 最大流（add10k）
#source("graph/flow/最大流@wh.cpp")

=== 费用流（add10k）
#source("graph/flow/费用流@wh.cpp")