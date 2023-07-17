#include <bits/stdc++.h>
#define ll long long
using namespace std;

namespace modulus_op {
const int mod = 998244353;
inline int sub(int x, int y) {
  x -= y;
  return x < 0 ? x + mod : x;
}
inline int add(int x, int y) {
  x += y;
  return x >= mod ? x - mod : x;
}
inline int power(int a, int b) {
  int s = 1;
  for (; b; b >>= 1, a = (ll)a * a % mod)
    if (b & 1) s = (ll)s * a % mod;
  return s;
}
} // namespace modulus_op
using namespace modulus_op;

namespace polynom_mul {
vector<int> rev, rt;
void getRevRoot(int n) {
  int m = log(n) / log(2) + 1e-8;
  rev.resize(n);
  for (int i = 1; i < n; i++) {
    rev[i] = rev[i >> 1] >> 1 | (i & 1) << (m - 1);
  }
  static int len = 1;
  if (len < n) {
    rt.resize(n);
    for (; len < n; len <<= 1) {
      int uni = power(3, (mod - 1) / (len << 1));
      rt[len] = 1;
      for (int i = 1; i < len; i++) {
        rt[i + len] = (ll)rt[i + len - 1] * uni % mod;
      }
    }
  }
}
void ntt(vector<int> &f, int n) {
  f.resize(n);
  for (int i = 0; i < n; i++) {
    if (i < rev[i]) swap(f[i], f[rev[i]]);
  }
  for (int len = 1; len < n; len *= 2) {
    for (int i = 0; i < n; i += len * 2) {
      for (int j = 0; j < len; j++) {
        int x = f[i + j];
        int y = (ll)f[i + j + len] * rt[j + len] % mod;
        f[i + j] = add(x, y);
        f[i + j + len] = sub(x, y);
      }
    }
  }
}
vector<int> operator*(vector<int> f, vector<int> g) {
  int n = 1, m = (int)(f.size() + g.size()) - 1;
  while (n < m) n <<= 1;
  int invn = power(n, mod - 2);
  getRevRoot(n), ntt(f, n), ntt(g, n);
  for (int i = 0; i < n; i++) f[i] = (ll)f[i] * g[i] % mod;
  reverse(f.begin() + 1, f.end()), ntt(f, n);
  f.resize(m);
  for (int i = 0; i < m; i++) f[i] = (ll)f[i] * invn % mod;
  return f;
}
} // namespace polynom_mul
using namespace polynom_mul;

namespace polynom_inv {
vector<int> polyInv(vector<int> f, int n) {
  if (n == 1) return {power(f[0], mod - 2)};
  f.resize(n);
  vector<int> g = polyInv(f, n / 2), h(n);
  g.resize(n);
  for (int i = 0; i < n / 2; i++) h[i] = g[i];
  int invn = power(n, mod - 2);
  getRevRoot(n), ntt(f, n), ntt(g, n);
  for (int i = 0; i < n; i++) f[i] = (ll)f[i] * g[i] % mod;
  reverse(f.begin() + 1, f.end());
  ntt(f, n);
  for (int i = 1; i < n / 2; i++) f[i] = 0;
  for (int i = n / 2; i < n; i++) {
    f[i] = (ll)f[i] * invn % mod;
  }
  f[0] = 1, ntt(f, n);
  for (int i = 0; i < n; i++) f[i] = (ll)f[i] * g[i] % mod;
  reverse(f.begin() + 1, f.end()), ntt(f, n);
  for (int i = n / 2; i < n; i++) {
    h[i] = sub(0, (ll)f[i] * invn % mod);
  }
  return h;
}
vector<int> operator~(vector<int> f) {
  if (f.empty()) return f;
  int n = 1, m = f.size();
  while (n < m) n <<= 1;
  f = polyInv(f, n);
  f.resize(m);
  return f;
}
} // namespace polynom_inv
using namespace polynom_inv;

vector<int> inv = {1, 1};
void initInv(int m) {
  static int n = 2;
  if (n < m) {
    n = m;
    inv.resize(m);
    for (int i = n; i < m; i++) {
      inv[i] = (ll)(mod - mod / i) * inv[mod % i] % mod;
    }
  }
}

namespace polynom_ln {
vector<int> polyDeri(vector<int> f) {
  if (f.empty()) return f;
  int m = f.size();
  for (int i = 1; i < m; i++) {
    f[i - 1] = (ll)f[i] * i % mod;
  }
  f.pop_back();
  return f;
}
vector<int> polyInte(vector<int> f) {
  f.push_back(0);
  int m = f.size();
  initInv(m); // 需要自备线性求逆元
  for (int i = m - 1; i >= 1; i--) {
    f[i] = (ll)f[i - 1] * inv[i] % mod;
  }
  f[0] = 0;
  return f;
}
vector<int> polyLn(vector<int> f) {
  if (f.empty()) return f;
  int m = f.size();
  f = (~f) * polyDeri(f);
  f.resize(m);
  f = polyInte(f);
  f.pop_back();
  return f;
}
} // namespace polynom_ln
using namespace polynom_ln;

namespace polynom_exp {
vector<int> polyExp(vector<int> f, int n) {
  if (n == 1) return {1};
  f.resize(n);
  vector<int> g = polyExp(f, n / 2), h(n), g0;
  g.resize(n);
  g0 = polyLn(g);
  for (int i = 0; i < n / 2; i++) h[i] = g[i];
  for (int i = 0; i < n; i++) f[i] = sub(g0[i], f[i]);
  int invn = power(n, mod - 2);
  getRevRoot(n), ntt(f, n), ntt(g, n);
  for (int i = 0; i < n; i++) f[i] = (ll)f[i] * g[i] % mod;
  reverse(f.begin() + 1, f.end()), ntt(f, n);
  for (int i = n / 2; i < n; i++) {
    h[i] = sub(0, (ll)f[i] * invn % mod);
  }
  return h;
}
vector<int> polyExp(vector<int> f) {
  if (f.empty()) return f;
  int n = 1, m = f.size();
  while (n < m) n <<= 1;
  f = polyExp(f, n);
  f.resize(m);
  return f;
}
} // namespace polynom_exp
using namespace polynom_exp;

int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  int n, m;
  vector<int> f, g;
  cin >> n >> m, ++n, ++m;
  f.resize(n);
  for (int i = 0; i < n; i++) cin >> f[i];
  g.resize(m);
  for (int i = 0; i < m; i++) cin >> g[i];
  vector<int> h = f * g;
  for (int i = 0; i < h.size(); i++) cout << h[i] << " \n"[i + 1 == h.size()];
}