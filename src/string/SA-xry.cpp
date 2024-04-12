const int N = 1e5;
int n;
char S[N + 10];
int M = 26, sz, rk[N + 10], ar[N + 10], sa[N + 10], nw, ba[N + 10];
int he[N + 10];
void Getsa() {
  for (int i = 1; i <= M; ++i) ba[i] = 0;
  for (int i = 1; i <= n; ++i) ++ba[rk[i]];
  for (int i = 2; i <= M; ++i) ba[i] += ba[i - 1];
  for (int i = n; i >= 1; --i) sa[ba[rk[ar[i]]]--] = ar[i];
}
void SA() {
  M = 27;
  for (int i = 1; i <= n; ++i) rk[i] = S[i] - 'A' + 1, ar[i] = i;
  Getsa();
  for (int i = 1; i <= n; i <<= 1) {
    sz = 0;
    for (int j = n - i + 1; j <= n; ++j) ar[++sz] = j;
    for (int j = 1; j <= n; ++j)
      if (sa[j] > i) ar[++sz] = sa[j] - i;
    Getsa();
    for (int j = 1; j <= n; ++j) ar[j] = rk[j];
    rk[sa[1]] = nw = 1;
    for (int j = 2; j <= n; ++j) rk[sa[j]] = (sa[j] + i <= n && sa[j - 1] + i <= n && ar[sa[j]] == ar[sa[j - 1]] && ar[sa[j] + i] == ar[sa[j - 1] + i] ? nw : ++nw);
    M = nw;
  }
}
void Getheight() {
  int ls = 0;
  for (int i = 1; i <= n; ++i) {
    ls ? --ls : 0;
    if (rk[i] == 1) continue;
    while (i + ls <= n && sa[rk[i] - 1] + ls <= n && S[i + ls] == S[sa[rk[i] - 1] + ls]) ++ls;
    he[rk[i]] = ls;
  }
  return;
}