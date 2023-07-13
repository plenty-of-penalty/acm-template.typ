// https://uoj.ac/problem/622

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;
int n, m, s;
vector<pair<int, int>> G[N];

namespace dijkstra {
const long long inf = 4e14;
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
} // namespace dijkstra
using namespace dijkstra;

int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> s;
  for (int u, v, w, i = 1; i <= m; i++) {
    cin >> u >> v >> w;
    G[u].emplace_back(v, w);
  }
  dij(s);
  for (int i = 1; i <= n; i++) cout << (dis[i] == inf ? -1 : dis[i]) << " \n"[i == n];
}