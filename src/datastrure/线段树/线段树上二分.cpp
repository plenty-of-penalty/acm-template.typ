#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
#ifdef memset0
#define log(...) fprintf(stderr, __VA_ARGS__)
#else
#define log(...) (void(0))
#define endl '\n'
#endif
using namespace std;
using ll = long long;

const int N = 1e5 + 9;
int n, m, k, a[N], f[N];
vector<int> same[N];

struct segment {
  int l, r, mid, len;
  int max, lazy;
  ll sum;
} p[N << 2];

void pushup(int u, int x) {
  p[u].sum += (ll)x * p[u].len;
  p[u].lazy += x;
}
void pushdown(int u) {
  if (p[u].lazy) {
    pushup(u << 1, p[u].lazy);
    pushup(u << 1 | 1, p[u].lazy);
    p[u].lazy = 0;
  }
}

void build(int u, int l, int r) {
  p[u].l = l, p[u].r = r;
  p[u].mid = (l + r) >> 1;
  p[u].len = r - l + 1;
  if (l == r) {
    p[u].max = a[l];
    return;
  }
  build(u << 1, l, p[u].mid);
  build(u << 1 | 1, p[u].mid + 1, r);
  p[u].max = max(p[u << 1].max, p[u << 1 | 1].max);
}

void build_sum(int u) {
  if (p[u].l == p[u].r) {
    p[u].sum = f[p[u].l];
    return;
  }
  build_sum(u << 1);
  build_sum(u << 1 | 1);
  p[u].sum = p[u << 1].sum + p[u << 1 | 1].sum;
}

void modify_max(int u, int k, int x) {
  if (p[u].l == p[u].r) {
    p[u].max = x;
    return;
  }
  if (k <= p[u].mid) {
    modify_max(u << 1, k, x);
  } else {
    modify_max(u << 1 | 1, k, x);
  }
  p[u].max = max(p[u << 1].max, p[u << 1 | 1].max);
}

void modify_sum(int u, int k, int x) {
  if (p[u].l == p[u].r) {
    p[u].sum = x;
    return;
  }
  pushdown(u);
  if (k <= p[u].mid) {
    modify_sum(u << 1, k, x);
  } else {
    modify_sum(u << 1 | 1, k, x);
  }
  p[u].sum = p[u << 1].sum + p[u << 1 | 1].sum;
}

void modify_sum(int u, int l, int r, int x) {
  if (p[u].l == l && p[u].r == r) return pushup(u, x);
  pushdown(u);
  if (r <= p[u].mid) {
    modify_sum(u << 1, l, r, x);
  } else if (l > p[u].mid) {
    modify_sum(u << 1 | 1, l, r, x);
  } else {
    modify_sum(u << 1, l, p[u].mid, x);
    modify_sum(u << 1 | 1, p[u].mid + 1, r, x);
  }
  p[u].sum = p[u << 1].sum + p[u << 1 | 1].sum;
}

int query_max(int u, int l, int r) {
  if (p[u].l == l && p[u].r == r) return p[u].max;
  if (r <= p[u].mid) return query_max(u << 1, l, r);
  if (l > p[u].mid) return query_max(u << 1 | 1, l, r);
  return max(query_max(u << 1, l, p[u].mid), //
             query_max(u << 1 | 1, p[u].mid + 1, r));
}

namespace BinarySearchOnSegTree {
int count_prefix(int u, int l, int r, int x) {
  if (p[u].l == p[u].r) return p[u].max <= x;
  if (p[u].l == l && p[u].r == r) {
    if (p[u << 1].max > x) return count_prefix(u << 1, l, p[u].mid, x);
    return p[u << 1].len + count_prefix(u << 1 | 1, p[u].mid + 1, r, x);
  }
  if (r <= p[u].mid) return count_prefix(u << 1, l, r, x);
  if (l > p[u].mid) return count_prefix(u << 1 | 1, l, r, x);
  int res = count_prefix(u << 1, l, p[u].mid, x);
  if (res == p[u].mid - l + 1 /* !!! */) res += count_prefix(u << 1 | 1, p[u].mid + 1, r, x);
  return res;
}
int count_suffix(int u, int l, int r, int x) {
  if (p[u].l == p[u].r) return p[u].max <= x;
  if (p[u].l == l && p[u].r == r) {
    if (p[u << 1 | 1].max > x) return count_suffix(u << 1 | 1, p[u].mid + 1, r, x);
    return p[u << 1 | 1].len + count_suffix(u << 1, l, p[u].mid, x);
  }
  if (r <= p[u].mid) return count_suffix(u << 1, l, r, x);
  if (l > p[u].mid) return count_suffix(u << 1 | 1, l, r, x);
  int res = count_suffix(u << 1 | 1, p[u].mid + 1, r, x);
  if (res == r - p[u].mid /* !!! */) res += count_suffix(u << 1, l, p[u].mid, x);
  return res;
}
} // namespace BinarySearchOnSegTree
using namespace BinarySearchOnSegTree;

ll query_sum(int u, int k) {
  if (p[u].l == p[u].r) {
    return p[u].sum;
  }
  pushdown(u);
  if (k <= p[u].mid) return query_sum(u << 1, k);
  return query_sum(u << 1 | 1, k);
}

ll query_sum(int u, int l, int r) {
  if (p[u].l == l && p[u].r == r) {
    return p[u].sum;
  }
  pushdown(u);
  if (r <= p[u].mid) return query_sum(u << 1, l, r);
  if (l > p[u].mid) return query_sum(u << 1 | 1, l, r);
  return query_sum(u << 1, l, p[u].mid) + //
         query_sum(u << 1 | 1, p[u].mid + 1, r);
}

int query_left(int k, int x) { return k - count_suffix(1, 0, k - 1, x) - 1; }
int query_right(int k, int x) { return k + count_prefix(1, k + 1, n + 1, x) + 1; }

long long query(int l, int r) { return query_sum(1, l, r) * k + (ll)(r - l + 1) * (n - 1); }

void update_same(int l, int r, int x) {
  // a[l]==a[r] 考虑他们对于l<i<r满足a[l]和a[r]都在i左右单调栈的贡献
  if (l + 1 >= r) return;
  if (a[l] <= query_max(1, l + 1, r - 1)) return;
  modify_sum(1, l + 1, r - 1, -x);
}

void update_same_pos(int k, int x, int y = -1) {
  int p = lower_bound(all(same[a[k]]), k) - same[a[k]].begin();
  if (p > 0) {
    update_same(same[a[k]][p - 1], k, x);
  }
  if (p + 1 < (int)same[a[k]].size()) {
    update_same(k, same[a[k]][p + 1], x);
  }
  if (y != -1) {
    same[a[k]][p] = y;
  }
}

void resolve(int k) {
  int l = query_left(k, a[k]);
  int r = query_right(k, a[k]);
  log("resolve %d >> l=%d r=%d >> f=%lld\n", k, l, r, query_sum(1, a[l] < a[r] ? l : r));
  modify_sum(1, k, query_sum(1, a[l] < a[r] ? l : r) + 1);
}

void exchange(int x) {
  if (a[x] == a[x + 1]) return;
  log("exchange a[%d]=%d with a[%d]=%d\n", x, a[x], x + 1, a[x + 1]);
  update_same_pos(x, -1, x + 1);
  update_same_pos(x + 1, -1, x);
  for (int i = 1; i <= n; i++) log("%lld%c", query_sum(1, i, i), " \n"[i == n]);
  if (a[x] < a[x + 1]) {
    int l = query_left(x, a[x] - 1) + 1;
    int r = x;
    modify_sum(1, l, r, -1);
  } else {
    int l = x + 1;
    int r = query_right(x + 1, a[x + 1] - 1) - 1;
    modify_sum(1, l, r, -1);
  }
  for (int i = 1; i <= n; i++) log("%lld%c", query_sum(1, i, i), " \n"[i == n]);
  swap(a[x], a[x + 1]);
  modify_max(1, x, a[x]);
  modify_max(1, x + 1, a[x + 1]);
  if (a[x] < a[x + 1]) {
    int l = query_left(x, a[x] - 1) + 1;
    int r = x;
    modify_sum(1, l, r, 1);
  } else {
    int l = x + 1;
    int r = query_right(x + 1, a[x + 1] - 1) - 1;
    modify_sum(1, l, r, 1);
  }
  update_same_pos(x, 1);
  update_same_pos(x + 1, 1);
  for (int i = 1; i <= n; i++) log("%lld%c", query_sum(1, i, i), " \n"[i == n]);
  resolve(a[x] < a[x + 1] ? x + 1 : x);
  resolve(a[x] < a[x + 1] ? x : x + 1);
  for (int i = 1; i <= n; i++) log("%lld%c", query_sum(1, i, i), " \n"[i == n]);
}

void init() {
  vector<int> val;
  for (int i = 1; i <= n; i++) {
    val.push_back(a[i]);
  }
  sort(all(val));
  val.erase(unique(all(val)), val.end());
  m = val.size();
  a[0] = a[n + 1] = m + 1;
  for (int i = 1; i <= n; i++) {
    a[i] = lower_bound(all(val), a[i]) - val.begin() + 1;
    same[a[i]].push_back(i);
  }
  build(1, 0, n + 1);
  // for (int i = 1; i <= m; i++) {
  //   for (int j = 0; j + 1 < (int)same[i].size(); j++) {
  //     update_same(same[i][j], same[i][j + 1], 1);
  //   }
  // }
  f[0] = f[n + 1] = -1;
  for (int v = m; v >= 1; v--)
    for (int k : same[v]) {
      int l = query_left(k, a[k]);
      int r = query_right(k, a[k]);
      log("solve %d >> l=%d r=%d >> p=%d f=%d\n", k, l, r, a[l] < a[r] ? l : r, f[a[l] < a[r] ? l : r]);
      f[k] = f[a[l] < a[r] ? l : r] + 1;
    }
  build_sum(1);
  for (int i = 1; i <= n; i++) log("%lld%c", query_sum(1, i, i), " \n"[i == n]);
}

void initialize(int N, int K, int *R) {
  n = N, k = K;
  // cerr << "n=" << n << " k=" << k << endl;
  for (int i = 1; i <= n; i++) a[i] = R[i - 1];

  init();
}