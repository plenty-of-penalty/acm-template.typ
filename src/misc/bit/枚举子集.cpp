for (int x = 0; x < (1 << n); x++) {
  for (int y = x & (x - 1); y != x; (y -= 1) &= x) {
    // 枚举y是x的所有子集
  }
}