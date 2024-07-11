struct Bitset {
  vector<ull> bit;
  int len;
  Bitset(int x) {
    bit.resize(x);
    len = x;
  }
  void set(int x) { bit[x >> 6] |= (1ull << (x & 63)); }
  bool operator[](int x) { return (bit[x >> 6] >> (x & 63)) & 1; }
  void operator|=(const Bitset &b) { For(i, 0, len - 1) bit[i] |= b.bit[i]; }
  Bitset operator<<(const int t) const {
    Bitset res(len);
    int h = t >> 6, l = t & 63;
    ull lst = 0;
    For(i, 0, len - h - 1) {
      res.bit[i + h] = lst | (bit[i] << l);
      if (l) lst = bit[i] >> (64 - l);
    }
    return res;
  }
}