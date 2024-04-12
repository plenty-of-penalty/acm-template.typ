const int N = 5e5;
struct Line {
  int k, b;
  bool F(int x) { return x * k + b; }
} L[N + 10];
bool Cov(Line l1, Line l2, Line l3) { // Insert l1,l1&l2 cover l3
  return 1ll * (l2.b - l1.b) * (l1.k - l3.k) >= 1ll * (l3.b - l1.b) * (l1.k - l2.k);
}
int sz;
void Ins(Line l) {
  if (sz && L[sz].k == l.k) {
    // L[sz].b=max(L[sz].b,l.b);
    return;
  }
  while (sz > 1 && Cov(l, L[sz], L[sz - 1])) --sz;
  L[++sz] = l;
}