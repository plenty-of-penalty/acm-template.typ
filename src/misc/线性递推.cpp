// https://qoj.ac/problem/547

#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int mod = 998244353;
inline int sub(int x, int y) { return x -= y, x < 0 ? x + mod : x; }
inline int add(int x, int y) { return x += y, x >= mod ? x - mod : x; }
inline int inv(int x) {
  if (x < 2) return 1;
  return (ll)(mod - mod / x) * inv(mod % x) % mod;
}
inline int power(int a, int b) {
  int s = 1;
  for (; b; b >>= 1, a = (ll)a * a % mod)
    if (b & 1) s = (ll)s * a % mod;
  return s;
}
namespace BerlekampMassey {
vector<int> BM(const vector<int> &a) {
  int fail = -1, delta = 0;
  vector<int> res, lst;
  for (int i = 0; i < a.size(); i++) {
    int tmp = 0;
    for (int j = 0; j < res.size(); j++) {
      tmp = (tmp + (ll)a[i - j - 1] * res[j]) % mod;
    }
    if (a[i] == tmp) continue;
    if (fail == -1) {
      res.resize(i + 1);
      fail = i, delta = sub(a[i], tmp);
      for (int j = 0; j <= i; j++) res[j] = 0;
      continue;
    }
    vector<int> now = res;
    int len = lst.size() + i - fail;
    int mul = (ll)sub(a[i], tmp) * inv(delta) % mod;
    if (res.size() < len) res.resize(len);
    res[i - fail - 1] = add(res[i - fail - 1], mul);
    for (int j = 0; j < lst.size(); j++) {
      res[i - fail + j] = sub(res[i - fail + j], (ll)mul * lst[j] % mod);
    }
    if (now.size() < len) {
      lst = now, fail = i, delta = sub(a[i], tmp);
    }
  }
  return res;
}
} // namespace BerlekampMassey
using namespace BerlekampMassey;
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<int> res = BM(a);
  cout << res.size() << endl;
  for (int i = 0; i < res.size(); i++) cout << res[i] << " \n"[i + 1 == res.size()];
}