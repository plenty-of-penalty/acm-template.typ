#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
namespace my_bitset {
struct Bitset {
  vector<ull> bit;
  Bitset(int x) { bit.resize(x); }
  void resize(int x) { bit.resize((x >> 6) + 1); }
  void set(int x) { bit[x >> 6] |= (1ull << (x & 63)); }
  void reset(int x) { bit[x >> 6] &= (~(1ull << (x & 63))); }
  void flip(int x) { bit[x >> 6] ^= (1ull << (x & 63)); }
  bool operator[](int x) { return (bit[x >> 6] >> (x & 63)) & 1; }
  bool any() {
    for (ull &x : bit)
      if (x) return 1;
    return 0;
  }
  Bitset operator~() const {
    Bitset res(bit.size());
    for (size_t i = 0; i < bit.size(); i++) res.bit[i] = ~bit[i];
    return res;
  }
  Bitset &operator&=(const Bitset &rhs) {
    if (rhs.bit.size() > bit.size()) bit.resize(rhs.bit.size());
    for (size_t i = 0; i < rhs.bit.size(); i++) bit[i] &= rhs.bit[i];
    return *this;
  }
  Bitset &operator|=(const Bitset &rhs) {
    if (rhs.bit.size() > bit.size()) bit.resize(rhs.bit.size());
    for (size_t i = 0; i < rhs.bit.size(); i++) bit[i] |= rhs.bit[i];
    return *this;
  }
  Bitset &operator^=(const Bitset &rhs) {
    if (rhs.bit.size() > bit.size()) bit.resize(rhs.bit.size());
    for (size_t i = 0; i < rhs.bit.size(); i++) bit[i] ^= rhs.bit[i];
    return *this;
  }
  Bitset operator&(const Bitset &rhs) const {
    Bitset res = *this;
    return res &= rhs;
  }
  Bitset operator|(const Bitset &rhs) const {
    Bitset res = *this;
    return res |= rhs;
  }
  Bitset operator^(const Bitset &rhs) const {
    Bitset res = *this;
    return res ^= rhs;
  }
  Bitset operator<<(const int t) const {
    Bitset res(bit.size());
    int high = t >> 6, low = t & 63;
    ull lst = 0;
    for (int i = 0; i + high < bit.size(); i++) {
      res.bit[i + high] = (lst | (bit[i] << low));
      if (low) lst = (bit[i] >> (64 - low));
    }
    return res;
  }
  Bitset operator>>(const int t) const {
    Bitset res(bit.size());
    int high = t >> 6, low = t & 63;
    ull lst = 0;
    for (int i = (int)bit.size() - 1; i >= high; i--) {
      res.bit[i - high] = (lst | (bit[i] >> low));
      if (low) lst = (bit[i] << (64 - low));
    }
    return res;
  }
  void operator<<=(const int t) {
    int high = t >> 6, low = t & 63;
    for (int i = (int)bit.size() - high - 1; ~i; i--) {
      bit[i + high] = (bit[i] << low);
      if (low && i) bit[i + high] |= (bit[i - 1] >> (64 - low));
    }
    for (int i = 0; i < min(high, (int)bit.size() - 1); i++) bit[i] = 0;
  }
  void operator>>=(const int t) {
    int high = t >> 6, low = t & 63;
    for (int i = high; i < (int)bit.size(); i++) {
      bit[i - high] = (bit[i] >> low);
      if (low && i != (int)bit.size()) bit[i - high] |= (bit[i + 1] << (64 - low));
    }
    for (int i = max((int)bit.size() - high, 0); i < (int)bit.size(); i++) bit[i] = 0;
  }
  int _Find_next(int t) {
    int high = t >> 6, low = t & 63;
    ull tmp = bit[high] & ~((1ull << (low + 1)) - 1);
    if (low != 63 && tmp) return (high << 6) + __builtin_ctzll(tmp);
    for (int i = high + 1; i < (int)bit.size(); i++)
      if (bit[i]) return (i << 6) + __builtin_ctzll(bit[i]);
    return INT_MAX;
  }
  int _Find_last(int t) {
    int high = t >> 6, low = t & 63;
    ull tmp = bit[high] & ((1ull << low) - 1);
    if (tmp) return (high << 6) + 63 - __builtin_clzll(tmp);
    for (int i = high - 1; i >= 0; i--)
      if (bit[i]) return (i << 6) + 63 - __builtin_clzll(bit[i]);
    return INT_MIN;
  }
};
} // namespace my_bitset