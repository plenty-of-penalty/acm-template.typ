#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; ++i)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; --i)
#ifdef memset0
#define log(...) fprintf(stderr, __VA_ARGS__)
#else
#define log(...) (void(0))
#define endl '\n'
#endif
using namespace std;
using ll = long long;
using lf = long double;
using ull = unsigned long long;

namespace maxflow {
int s, t;
vector<int> hed, cur, dep;
struct edge {
  int to, val, nxt;
};
vector<edge> e;
void _add(int u, int v, int w) {
  while (u >= hed.size() || v >= hed.size()) hed.push_back(-1);
  e.push_back({v, w, hed[u]});
  hed[u] = e.size() - 1;
}
bool bfs() {
  fill(all(dep), 0);
  queue<int> q;
  q.push(s);
  dep[s] = 1;
  while (q.size()) {
    int u = q.front();
    q.pop();
    for (int i = hed[u]; ~i; i = e[i].nxt)
      if (e[i].val && !dep[e[i].to]) {
        dep[e[i].to] = dep[u] + 1;
        q.push(e[i].to);
      }
  }
  return dep[t];
}
int dfs(int u, int d) {
  if (u == t) return d;
  int s = 0;
  for (int &i = cur[u]; ~i; i = e[i].nxt)
    if (e[i].val && dep[e[i].to] == dep[u] + 1)
      if (int x = dfs(e[i].to, min(d - s, e[i].val))) {
        s += x;
        e[i].val -= x;
        e[i ^ 1].val += x;
        if (s == d) return s;
      }
  return s ? s : dep[u] = 0;
}
void add(int u, int v, int w) {
  _add(u, v, w);
  _add(v, u, 0);
}
ll solve(int _s, int _t) {
  s = _s, t = _t;
  dep.resize(hed.size()); // !
  ll ans = 0;
  while (bfs()) {
    cur = hed;
    ans += dfs(s, INT_MAX);
  }
  return ans;
}
void clear() {
  e.clear();
  hed.clear();
}
} // namespace maxflow

int main() {
#ifdef memset0
  freopen("maxflow.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  vector<tuple<int, int, int>> e(m);
  for (auto &[u, v, w] : e) {
    cin >> u >> v >> w;
    maxflow::add(u, v, w);
  }
  cout << maxflow::solve(s, t) << endl;
}