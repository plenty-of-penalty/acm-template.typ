// https://www.luogu.com.cn/problem/P3803

#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 9, mod = 998244353;
int n, m, a[N << 2], b[N << 2];
inline int dec(int x, int y) { return (x -= y) < 0 ? x + mod : x; }
inline int inc(int x, int y) { return (x += y) >= mod ? x - mod : x; }
inline int fpow(int a, int b) {
  int s = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mod)
    if (b & 1) s = 1ll * s * a % mod;
  return s;
}
using namespace std;
namespace ntt {
const int mod = 998244353;
int lim = 1, k, rev[N << 2], w[N << 2];
void init(int len) {}
void dft(int *a, int lim) {
  for (int i = 0; i < lim; i++)
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int len = 1; len < lim; len <<= 1)
    for (int i = 0; i < lim; i += (len << 1))
      for (int j = 0; j < len; j++) {
        int x = a[i + j];
        int y = 1ll * a[i + j + len] * w[j + len] % mod;
        a[i + j] = inc(x, y);
        a[i + j + len] = dec(x, y);
      }
}
void idft(int *a, int lim) {
  reverse(a + 1, a + lim);
  dft(a, lim);
  int inv_lim = fpow(lim, mod - 2);
  for (int i = 0; i < lim; i++) {
    a[i] = 1ll * a[i] * inv_lim % mod;
  }
}
void polymul(int *a, int *b, int len) {
  while (lim <= n + m) lim <<= 1, ++k;
  for (int i = 0; i < lim; i++) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
  }
  for (int wn, len = 1; len < lim; len <<= 1) {
    wn = fpow(3, (mod - 1) / (len << 1));
    w[len] = 1;
    for (int i = 1; i < len; i++) {
      w[i + len] = 1ll * w[i + len - 1] * wn % mod;
    }
  }
  dft(a, lim), dft(b, lim);
  for (int i = 0; i < lim; i++) {
    a[i] = 1ll * a[i] * b[i] % mod;
  }
  idft(a, lim);
}
} // namespace ntt
using namespace ntt;
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i <= n; i++) cin >> a[i];
  for (int i = 0; i <= m; i++) cin >> b[i];
  polymul(a, b, n + m + 1);
  for (int i = 0; i <= n + m; i++) cout << a[i] << " \n"[i == n + m];
}
