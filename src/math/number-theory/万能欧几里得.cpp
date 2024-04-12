#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 I128;
const int MAXN = 20, mod = 998244353;
struct matrix {
  int a[MAXN][MAXN];
  matrix() { memset(a, 0, sizeof a); }
  matrix(int tp[MAXN][MAXN]) { memcpy(a, tp, sizeof a); }
  matrix operator*(const matrix &you) const {
    static int tp[MAXN][MAXN];
    memset(tp, 0, sizeof tp);
    for (int i = 0; i < MAXN; ++i)
      for (int k = 0; k < MAXN; ++k)
        for (int j = 0; j < MAXN; ++j) tp[i][j] = (tp[i][j] + ll(a[i][k]) * you.a[k][j]) % mod;
    return tp;
  }
  matrix operator+(const matrix &you) const {
    static int tp[MAXN][MAXN];
    for (int i = 0; i < MAXN; ++i)
      for (int j = 0; j < MAXN; ++j) tp[i][j] = (a[i][j] + you.a[i][j]) % mod;
    return tp;
  }
} I, A, B;
struct W {
  matrix A, B, res;
  W() { A = I, B = I, res = matrix(); }
  W(matrix _A, matrix _B, matrix _r) { A = _A, B = _B, res = _r; }
  W operator*(W you) { return W(A * you.A, B * you.B, res + A * you.res * B); }
};
matrix Pow(matrix a, ll p) {
  if (p == 1) return a;
  matrix res = I;
  while (p) {
    if (p & 1) res = res * a;
    a = a * a, p >>= 1;
  }
  return res;
}
W Pow(W a, ll p) {
  if (p == 1) return a;
  W res;
  while (p) {
    if (p & 1) res = res * a;
    a = a * a, p >>= 1;
  }
  return res;
}
W Wan(ll p, ll q, ll r, ll n, W A, W B) {
  if (p >= q) return Wan(p % q, q, r, n, A, Pow(A, p / q) * B);
  ll m = (I128(p) * n + r) / q;
  if (m == 0) return Pow(B, n);
  W res = Pow(B, (q - r - 1) / p) * A;
  res = res * Wan(q, p, (q - r - 1) % p, m - 1, B, A);
  return res * Pow(B, n - (I128(q) * m - r - 1) / p);
}
int main() {
  // freopen("wan.in","r",stdin);
  std::cin.tie(0)->sync_with_stdio(0);
  ll p, q, r, L, n;
  std::cin >> p >> q >> r >> L >> n;
  for (int i = 0; i < n; ++i) I.a[i][i] = 1;
  matrix A, B;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) std::cin >> A.a[i][j];
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) std::cin >> B.a[i][j];
  W U(I, B, matrix()), R(A, I, A);
  W res(I, Pow(B, r / q), matrix());
  res = res * Wan(p, q, r % q, L, U, R);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) printf("%d%c", res.res.a[i][j], j == n - 1 ? '\n' : ' ');
  return 0;
}
