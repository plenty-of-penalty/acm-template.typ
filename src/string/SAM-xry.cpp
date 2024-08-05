#include <bits/stdc++.h>
using namespace std;
namespace stdlib {
const int N = 1e5 + 9;
struct SAM {
  int lk[N << 1], len[N << 1], nw, cnt;
  unordered_map<int, int> e[N << 1];
  void init() {
    lk[cnt = nw = 1] = 0;
    len[nw] = 0;
  }
  void ins(char c) {
    int cur = ++cnt;
    len[cur] = len[nw] + 1;
    while (nw && !e[nw][c]) e[nw][c] = cur, nw = lk[nw];
    if (!nw) lk[cur] = 1;
    else {
      int p = nw, q = e[nw][c];
      if (len[q] == len[p] + 1) lk[cur] = q;
      else {
        int cl = ++cnt;
        lk[cl] = lk[q], len[cl] = len[p] + 1, e[cl] = e[q];
        lk[q] = lk[cur] = cl;
        while (nw && e[nw][c] == q) e[nw][c] = cl, nw = lk[nw];
      }
    }
    nw = cur;
  }
};
} // namespace stdlib