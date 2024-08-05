/**
 * @description: 给定一棵有 $n$ 个点的树，询问树上距离为 $k$ 的点对是否存在。
 * @problem: https://www.luogu.com.cn/problem/P3806
 */
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 9, K = 1e7 + 9;
int n, q, rt, tot, fa[N], siz[N], mxp[N];
bool vis[N], bkt[K];
vector<int> k, ans;
vector<pair<int, int>> G[N];
void findroot(int u) {
  siz[u] = 1, mxp[u] = 0;
  for (auto [v, w] : G[u])
    if (!vis[v] && v != fa[u]) {
      fa[v] = u;
      findroot(v);
      siz[u] += siz[v];
      mxp[u] = max(mxp[u], siz[v]);
    }
  mxp[u] = max(mxp[u], tot - siz[u]); // 这里不能用 n
  if (rt == 0 || mxp[u] < mxp[rt]) rt = u;
}
vector<int> cur;
vector<vector<int>> all;
void collect(int u, int d) {
  cur.push_back(d);
  for (auto [v, w] : G[u])
    if (!vis[v] && v != fa[u]) {
      fa[v] = u;
      collect(v, d + w);
    }
}
void solve(int u) {
  vis[u] = 1;
  all.clear();
  all.push_back({0});
  for (auto [v, w] : G[u])
    if (!vis[v]) {
      cur.clear();
      fa[v] = u, collect(v, w);
      all.push_back(cur);
    }
  for (int i = 0; i < q; i++)
    if (!ans[i]) {
      for (auto &vec : all) {
        for (int dis : vec) {
          if (0 <= dis && dis < K && bkt[dis]) ans[i] = true;
        }
        for (int dis : vec) {
          int tmp = k[i] - dis;
          if (tmp >= 0 && tmp < K) bkt[tmp] = true;
        } // 一定要分成两个for
      }
      for (auto &vec : all) {
        for (int dis : vec) {
          int tmp = k[i] - dis;
          if (tmp >= 0 && tmp < K) bkt[tmp] = false;
        }
      }
    }
  for (auto [v, w] : G[u])
    if (!vis[v]) {
      rt = 0, tot = siz[v];
      findroot(v);
      solve(rt);
    }
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> q;
  for (int u, v, w, i = 1; i < n; i++) {
    cin >> u >> v >> w;
    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
  }
  k.resize(q), ans.resize(q);
  for (int &x : k) cin >> x;
  tot = n;
  findroot(1);
  solve(rt);
  for (int x : ans) {
    cout << (x ? "AYE" : "NAY") << endl;
  }
}