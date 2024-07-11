// https://vjudge.net/problem/UVA-11526
#include <iostream>
using namespace std;
using ll = long long;
#define int long long

namespace sqrt_decomposition {
ll H(int n) { // $H(n) = sum_(i=1)^n floor(n/i)$
  ll res = 0;
  for (int l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    res += (ll)(r - l + 1) * (n / l);
  }
  return res;
}
} // namespace sqrt_decomposition
using namespace sqrt_decomposition;

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