#import "../template.typ": *
#show: styled

== 二维计算几何
#source("geometry/2d/geo.hpp", namespace: "geo")

=== 线段

- #[
    #desc 求点 $p$ 到线段 $(s,e)$ 的最短距离。

    #usage `Point<double> a, b(2,2), p(1,1); bool onSegment = segDist(a,b,p) < 1e-10;`
  ]

#source("geometry/2d/segment.hpp", namespace: "SegDist")

- #desc 求点 $p$ 是否在线段 $(s,e)$ 上（全整数写法）。

#source("geometry/2d/segment.hpp", namespace: "OnSegment")

- #desc TBD

#source("geometry/2d/segment.hpp", namespace: "SideOf")

- #desc 求两条线段 $(a,b)$ 和 $(c,d)$ 的交点，返回值为 `vector`。如果没有交点则 `vector` 为空，如果有无限个交点则返回所交线段的端点。

#source("geometry/2d/segment.hpp", namespace: "SegInter")

=== 直线

#source("geometry/2d/line.hpp", namespace: "LineDist")

#source("geometry/2d/line.hpp", namespace: "LineInter")

=== 凸包

#source("geometry/2d/polygon.hpp", namespace: "InPolygon")
#source("geometry/2d/polygon.hpp", namespace: "PolygonArea")
#source("geometry/2d/polygon.hpp", namespace: "PolygonCenter")
#source("geometry/2d/polygon.hpp", namespace: "PolygonCut")
#source("geometry/2d/polygon.hpp", namespace: "ConvexHull")
#source("geometry/2d/polygon.hpp", namespace: "HullDiameter")
#source("geometry/2d/polygon.hpp", namespace: "InHull")

=== 圆

TBD

== 三维计算几何

== 旋转卡壳

== 半平面交

== 最小圆覆盖

== 平面最近点对
#source("geometry/2d/misc.hpp", namespace: "ClosestPair")

== 反演变换