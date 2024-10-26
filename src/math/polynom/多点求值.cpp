#include <bits/stdc++.h>
#define vec std::vector<z>
template <class T> inline void read(T &x) {
  x = 0;
  register char c = getchar();
  register bool f = 0;
  while (!isdigit(c)) f ^= c == '-', c = getchar();
  while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
  if (f) x = -x;
}
template <class T> inline void print(T x) {
  if (x < 0) putchar('-'), x = -x;
  if (x > 9) print(x / 10);
  putchar(x % 10 + '0');
}
template <class T> inline void print(T x, char c) { print(x), putchar(c); }
const int N = 1e5 + 10, mod = 998244353;
int rev[N << 2];
struct z {
  int x;
  z(int x = 0) : x(x) {}
  friend inline z operator*(z a, z b) { return (long long)a.x * b.x % mod; }
  friend inline z operator-(z a, z b) { return (a.x -= b.x) < 0 ? a.x + mod : a.x; }
  friend inline z operator+(z a, z b) { return (a.x += b.x) >= mod ? a.x - mod : a.x; }
} w[N << 2];
inline z fpow(z a, int b) {
  z s = 1;
  for (; b; b >>= 1, a = a * a)
    if (b & 1) s = s * a;
  return s;
}
int init(int n) {
  int lim = 1, k = 0;
  while (lim < n) lim <<= 1, ++k;
  for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
  for (int len = 1; len < lim; len <<= 1) {
    z wn = fpow(3, (mod - 1) / (len << 1));
    w[len] = 1;
    for (int i = 1; i < len; i++) w[i + len] = w[i + len - 1] * wn;
  }
  return lim;
}
void dft(vec &a, int lim) {
  a.resize(lim);
  for (int i = 0; i < lim; i++)
    if (i < rev[i]) std::swap(a[i], a[rev[i]]);
  for (int len = 1; len < lim; len <<= 1)
    for (int i = 0; i < lim; i += (len << 1))
      for (int j = 0; j < len; j++) {
        z x = a[i + j], y = a[i + j + len] * w[j + len];
        a[i + j] = x + y, a[i + j + len] = x - y;
      }
}
void idft(vec &a, int lim) {
  dft(a, lim), std::reverse(&a[1], &a[lim]);
  z inv = fpow(lim, mod - 2);
  for (int i = 0; i < lim; i++) a[i] = a[i] * inv;
}
vec mul(vec a, vec b) {
  int len = a.size() + b.size() - 1, lim = init(len);
  dft(a, lim), dft(b, lim);
  for (int i = 0; i < lim; i++) a[i] = a[i] * b[i];
  return idft(a, lim), a.resize(len), a;
}
vec mulT(vec a, vec b, int l = -1) {
  int len = ~l ? l : a.size() - b.size() + 1;
  std::reverse(b.begin(), b.end());
  vec c = mul(a, b);
  c = vec(&c[b.size() - 1], &c[b.size() + len - 1]);
  return c;
}
vec inv(const vec &f, int len = -1) {
  if ((len = ~len ? len : f.size()) == 1) return {fpow(f[0], mod - 2)};
  vec a(&f[0], &f[len]), b = inv(f, (len + 1) >> 1);
  int lim = init((len << 1) - 1);
  dft(a, lim), dft(b, lim);
  for (int i = 0; i < lim; i++) a[i] = b[i] * (2 - a[i] * b[i]);
  return idft(a, lim), a.resize(len), a;
}
vec multiPointEvalution(vec f, vec a) {
  static vec F[N << 2], G[N << 2];
  vec b(f.size());
  std::function<void(int, int, int)> dfs1 = [&](int u, int l, int r) {
    if (l == r) {
      F[u] = {1, 0 - a[l]};
      return;
    }
    dfs1(u << 1, l, (l + r) >> 1);
    dfs1(u << 1 | 1, ((l + r) >> 1) + 1, r);
    F[u] = mul(F[u << 1], F[u << 1 | 1]);
  };
  std::function<void(int, int, int)> dfs2 = [&](int u, int l, int r) {
    if (l == r) {
      b[l] = G[u][0];
      return;
    }
    G[u << 1] = mulT(G[u], F[u << 1 | 1]);
    G[u << 1 | 1] = mulT(G[u], F[u << 1]);
    dfs2(u << 1, l, (l + r) >> 1);
    dfs2(u << 1 | 1, ((l + r) >> 1) + 1, r);
  };
  return dfs1(1, 0, f.size() - 1), G[1] = mulT(f, inv(F[1]), a.size()), dfs2(1, 0, f.size() - 1), b;
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  int n, m, l;
  read(n), read(m), ++n, l = std::max(n, m);
  vec f(l), a(l), b;
  for (int i = 0; i < n; i++) read((int &)f[i]);
  for (int i = 0; i < m; i++) read((int &)a[i]);
  b = multiPointEvalution(f, a);
  for (int i = 0; i < m; i++) print((int &)b[i], '\n');
}
// 5:00