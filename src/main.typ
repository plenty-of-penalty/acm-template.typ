#import "template.typ": *

#show: project.with(  
  title: "ACM Template",
  authors: (
    "memset0",
    "Sulfox",
  ),
)

#outline()



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
#include "thinking/main.typ"

= 常见错误
#include "bugs/main.typ"

= 附录
#include "appendix/main.typ"