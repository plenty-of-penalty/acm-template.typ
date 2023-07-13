#import "template.typ": *

#show: project.with(  
  title: "ACM Template",
  authors: (
    "memset0",
    "Sulfox",
  ),
)

= 数据结构

= 数学

== 多项式

=== 快速数论变换（NTT）

=== 多项式乘法

= Introduction
#lorem(60)

== In this paper
#lorem(20)

=== Contributions
#lorem(40)

```cpp
const long long inf = 0x6363636363636363;
long long dis[N];
priority_queue<pair<long long, int>> q;
void dij(int s) {
  // 求 s 点到每个点的最短路
  fill(dis + 1, dis + n + 1, inf);
  dis[s] = 0, q.push({0, s});
  while (q.size()) {
    auto [d, u] = q.top();
    q.pop(); // 上一行不能用 auto&，因为这里释放了地址
    if (dis[u] + d) continue;
    for (const auto &[v, w] : G[u]) {
      if (dis[u] + w < dis[v]) {
        dis[v] = dis[u] + w;
        q.push(make_pair(-dis[v], v));
      }
    }
  }
}
```

= Related Work
#lorem(500)

= Related Work 2
#lorem(500)

= Related Work 3
#lorem(500)
