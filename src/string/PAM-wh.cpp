namespace PAM {
int t[MAXN][26], fail[MAXN], len[MAXN], size[MAXN];
int last, tot, now;
void init() {
  len[0] = -1;
  last = tot = 1;
}
void extend(int w) {
  int pos = last;
  while (pos && s[now - len[pos]] - 'a' != w) pos = fail[pos];
  if (!t[pos][w]) {
    int cur = ++tot;
    t[pos][w] = cur, len[cur] = len[pos] + 2;
    if (!pos) fail[cur] = 1;
    else {
      pos = fail[pos];
      while (pos && s[now - len[pos]] - 'a' != w) pos = fail[pos];
      fail[cur] = t[pos][w];
    }
    last = tot;
  } else
    last = t[pos][w];
  ++now, ++size[last];
}
void solve() {
  ll ans = 0;
  for (int i = tot; i; --i) size[fail[i]] += size[i], ans = std::max(ans, ll(size[i]) * len[i]);
  printf("%lld\n", ans);
}
} // namespace PAM