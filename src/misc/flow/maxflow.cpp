struct Edge {
  ll v, w, nxt;
} e[MAXN << 3 | 1];
ll cnt = 1, last[MAXN];
void adde(ll u, ll v, ll w) {
  ++cnt;
  e[cnt].v = v, e[cnt].w = w;
  e[cnt].nxt = last[u], last[u] = cnt;
}
void insert(ll u, ll v, ll w) { adde(u, v, w), adde(v, u, 0); }
ll dep[MAXN], cur[MAXN];
queue<ll> q;
bool bfs(ll s, ll t, ll n) {
  for (ll i = 1; i <= n; ++i) cur[i] = last[i], dep[i] = 0;
  dep[s] = 1;
  q.push(s);
  while (!q.empty()) {
    ll u = q.front();
    q.pop();

    for (ll i = last[u]; i; i = e[i].nxt) {
      ll v = e[i].v;

      if (e[i].w > 0 && !dep[v]) {
        dep[v] = dep[u] + 1;
        q.push(v);
      }
    }
  }
  return dep[t] != 0;
}
ll ex_flow(ll u, ll t, ll flow = INF) {
  if (u == t) return flow;
  ll f = 0;
  for (ll &i = cur[u]; i; i = e[i].nxt) {
    ll v = e[i].v;
    if (dep[v] == dep[u] + 1 && e[i].w > 0) {
      ll tmp = ex_flow(v, t, min(e[i].w, flow - f));
      e[i].w -= tmp, e[i ^ 1].w += tmp;
      f += tmp;
      if (f == flow) return f;
    }
  }
  return f;
}
ll Dinic(ll s, ll t, ll n) {
  ll res = 0;
  while (bfs(s, t, n)) res += ex_flow(s, t);
  return res;
}