struct Edge {
  ll v, w, cost, nxt;
} e[MAXM << 1 | 1];
ll cnt = 1, last[MAXN];
void adde(ll u, ll v, ll w, ll c) {
  ++cnt;
  e[cnt].v = v, e[cnt].w = w, e[cnt].cost = c;
  e[cnt].nxt = last[u], last[u] = cnt;
}
void insert(ll u, ll v, ll w, ll c) { adde(u, v, w, c), adde(v, u, 0, -c); }
ll dis[MAXN], cur[MAXN];
bool vis[MAXN], inqueue[MAXN];
queue<ll> q;
bool spfa(ll s, ll t, ll n) {
  for (ll i = 1; i <= n; ++i) dis[i] = -INF, cur[i] = last[i];
  dis[s] = 0;
  q.push(s);
  while (!q.empty()) {
    ll u = q.front();
    q.pop();
    inqueue[u] = 0;
    for (ll i = last[u]; i; i = e[i].nxt) {
      ll v = e[i].v;
      if (e[i].w > 0 && umax(dis[v], dis[u] + e[i].cost)) {
        if (!inqueue[v]) inqueue[v] = 1, q.push(v);
      }
    }
  }
  return dis[t] != -INF;
}
ll sumc = 0;
ll ex_flow(ll u, ll t, ll flow = INF) {
  if (u == t) return flow;
  vis[u] = 1;
  ll f = 0;
  for (ll &i = cur[u]; i; i = e[i].nxt) {
    ll v = e[i].v;
    if (!vis[v] && dis[v] == dis[u] + e[i].cost) {
      ll tmp = ex_flow(v, t, min(e[i].w, flow - f));
      e[i].w -= tmp, e[i ^ 1].w += tmp;
      sumc += e[i].cost * tmp;
      f += tmp;
      if (f == flow) return f;
    }
  }
  return f;
}
ll zkw(ll s, ll t, ll n) {
  sumc = 0;
  while (memset(vis, 0, sizeof vis), spfa(s, t, n)) ex_flow(s, t);
  return sumc;
}
