// https://www.luogu.com.cn/problem/P3809
// https://uoj.ac/problem/35

#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 9;
namespace SuffixSort {
int n, m, sa[N], rnk[N], cnt[N], old[N], height[N];
void radixSort() {
  for (int i = 1; i <= m; i++) cnt[i] = 0;
  for (int i = 1; i <= n; i++) cnt[rnk[i]]++;
  for (int i = 2; i <= m; i++) cnt[i] += cnt[i - 1];
  for (int i = n; i >= 1; i--) {
    sa[cnt[rnk[old[i]]]--] = old[i];
  }
}
void suffixSort(const string &s) {
  n = s.length();
  for (int i = 1; i <= n; i++) {
    m = max(m, rnk[i] = s[i - 1]);
    old[i] = i;
  }
  radixSort();
  for (int len = 1, num = 0; true; len <<= 1, num = 0) {
    for (int i = n - len + 1; i <= n; i++) {
      old[++num] = i;
    }
    for (int i = 1; i <= n; i++) {
      if (sa[i] > len) old[++num] = sa[i] - len;
    }
    radixSort();
    memcpy(old, rnk, sizeof(old));
    rnk[sa[1]] = m = 1;
    for (int i = 2; i <= n; i++) {
      rnk[sa[i]] = old[sa[i - 1]] == old[sa[i]] && old[sa[i - 1] + len] == old[sa[i] + len] ? m : ++m;
    }
    if (m >= n) break;
  }
  for (int i = 1, j, num = 0; i <= n; i++) {
    if (rnk[i] == 1) height[1] = num = 0;
    j = sa[rnk[i] - 1];
    num = num ? num - 1 : 0;
    while (i + num <= n && j + num <= n && s[i + num - 1] == s[j + num - 1]) {
      num++;
    }
    height[rnk[i]] = num;
  }
}
} // namespace SuffixSort
using namespace SuffixSort;
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  string s;
  cin >> s;
  suffixSort(s);
  for (int i = 1; i <= n; i++) cout << sa[i] << " \n"[i == n];
  for (int i = 2; i <= n; i++) cout << height[i] << " \n"[i == n];
}