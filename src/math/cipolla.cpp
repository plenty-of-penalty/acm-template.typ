int t, sqr_w;
typedef std::pair<int, int> pair;
inline pair operator*(const pair &a, const pair &b) { return std::make_pair(((ll)a.first * b.first + (ll)a.second * b.second % mod * sqr_w) % mod, ((ll)a.first * b.second + (ll)a.second * b.first) % mod); }
int cipolla(int x) {
  do t = rand() % mod;
  while (fpow(sqr_w = dec((ll)t * t % mod, x), (mod - 1) >> 1) != mod - 1);
  // printf(">> t = %d sqr_w %d\n", t, sqr_w);
  pair s = std::make_pair(1, 0), a = std::make_pair(t, 1);
  for (int b = (mod + 1) >> 1; b; b >>= 1, a = a * a)
    if (b & 1) s = s * a;
  // printf(">> %d %d\n", s.first, s.second);
  return std::min(s.first, mod - s.first);
}