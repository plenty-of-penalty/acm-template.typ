#import "template.typ": *

#show: project.with(  
  title: "Plenty of Penalty",
  authors: (
    "xyrjr233",
    "add10k",
    "memset0",
  ),
  special_thanks: (
    "Sulfox",
  ),
)

= 基础模板
#importCode("template.cpp")

= 数据结构
#include "datastrure/main.typ"

= 树上问题
#include "tree/main.typ"

= 图论
#include "graph/main.typ"

= 数学
#include "math/main.typ"

= 字符串
#include "string/main.typ"

= 计算几何
#include "geometry/main.typ"

= 动态规划
#include "dp/main.typ"

= 杂项
#include "misc/main.typ"

= 思路
#include "thoughts/main.typ"

= 常见错误
#include "bugs/main.typ"

= 语言相关
#include "stl/main.typ"

= 附录
#include "appendix/main.typ"