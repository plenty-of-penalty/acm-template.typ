// https://vjudge.net/problem/UVA-11526
#include <iostream>
using namespace std;
using ll = long long;
#define int long long

namespace stdlib {
ll sumF(int l, int r) { return r - l + 1; }
int G(int x) { return x; }
ll H(int n) { // $H(n) = sum_(i=1)^n floor(n/i)$
  ll res = 0;
  for (int l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    res += (ll)sumF(l, r) * G(n / l);
  }
  return res;
}
} // namespace stdlib
using namespace stdlib;

signed main() {
  // cin.tie(0)->sync_with_stdio(0);
  int t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    if (n <= 0) {
      cout << 0 << '\n';
      continue;
    }
    cout << H(n) << '\n';
  }
  return 0;
}